#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <CL/cl.h>
#include "funciones.h"

typedef struct {
    int x,  // Coordenada x de la submatriz
    y, // Coordenada y de la submatriz
    t; // Tama�o de la submatriz
} terna_t;

void initializedouble(int t,double *a,double lv,double uv)
{
    int i;

    for(i=0;i<t;i++)
        //Valores generados entre lv y uv con 2 decimales
        a[i]=((int) ((((1.*rand())/RAND_MAX)*(uv-lv)+lv)*100.))/100.;
}

void initialize(int t,double *a,terna_t *ternas,int r)
{
    int i;

    initializedouble(t*t,a,-10.,10.);

    for(i=0;i<r;i++)
    {
        ternas[i].x=(int) (((1.*rand())/RAND_MAX)*t);
        ternas[i].y=(int) (((1.*rand())/RAND_MAX)*t);
        ternas[i].t=(int) (((1.*rand())/RAND_MAX)*(t-2)+2);
    }
}

void escribir(int t,double *a){
    int i, j;

    for (i = 0; i < t; i++)
    {
        for (j = 0; j < t; j++)
        {
            printf("%.2f ",a[i*t+j]);
        }
        printf("\n");
    }
    printf("\n");
}

void escribirt(terna_t *a,int t)
{
    int i;

    for(i=0;i<t;i++)
        printf("%d ",a[i].x);
    printf("\n");
    for(i=0;i<t;i++)
        printf("%d ",a[i].y);
    printf("\n");
    for(i=0;i<t;i++)
        printf("%d ",a[i].t);
    printf("\n");
}

/*
 * c
 * c     mseconds - returns elapsed milliseconds since Jan 1st, 1970.
 * c
 */
long long mseconds(){
    struct timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec*1000 + t.tv_usec/1000;
}

int ObtenerParametros(int argc, char *argv[], int *debug, int *num_workitems, int *workitems_por_workgroups) {
    int i;
    *debug=0;
    *num_workitems=0;
    *workitems_por_workgroups=0;
    if (argc<2)
        return 0;
    for (i=2; i<argc;) {
        if (strcmp(argv[i], "-d")==0) {
            *debug=1;
            i++;
        }
        else if (strcmp(argv[i], "-wi")==0) {
            i++;
            if (i==argc)
                return 0;
            *num_workitems=atoi(argv[i]);
            i++;
            if (*num_workitems<=0)
                return 0;
        }
        else if (strcmp(argv[i], "-wi_wg")==0) {
            i++;
            if (i==argc)
                return 0;
            *workitems_por_workgroups=atoi(argv[i]);
            i++;
            if (*workitems_por_workgroups<=0)
                return 0;
        }
        else
            return 0;
    }
    return 1;
}

typedef struct {
    cl_platform_id *plataformas;
    cl_device_id *dispositivos;
    cl_context contexto;
    cl_command_queue cola;
    cl_program programa;
    cl_kernel kernel;
} EntornoOCL_t;

// **************************************************************************
// ***************************** IMPLEMENTACI�N *****************************
// **************************************************************************
cl_int InicializarEntornoOCL(EntornoOCL_t *entorno) {

    cl_uint num_platforms, num_dispositivos;

    ObtenerPlataformas(entorno->plataformas, num_platforms);

    for(int i=0;i<num_platforms;i++){
        ObtenerDispositivos(entorno->plataformas[i],CL_DEVICE_TYPE_ALL, entorno->dispositivos,num_dispositivos);
    }

    CrearContexto(entorno->plataformas[0], entorno->dispositivos, num_dispositivos, entorno->contexto);
    CrearCola(entorno->contexto,entorno->dispositivos[0],CL_QUEUE_PROFILING_ENABLE,entorno->cola);
    CrearPrograma(entorno->programa, entorno->contexto,num_dispositivos, entorno->dispositivos, "", "programa.cl");
    CrearKernel(entorno->kernel,entorno->programa,"sec");

}

cl_int LiberarEntornoOCL(EntornoOCL_t *entorno) {
clReleaseContext(entorno->contexto);
clReleaseCommandQueue(entorno->cola);
clReleaseProgram(entorno->programa);
clReleaseKernel(entorno->kernel);

clReleaseDevice(entorno->dispositivos[0]);
}

/*
 * N -> Tama�o de la matriz (NxN)
 * A -> Matriz
 * ternas -> Vector de ternas con los tama�os y las coordenadas de las submatrices
 * num_sb -> N�mero de submatrices
 */
void ocl(int N,double *A,terna_t *ternas, int num_sb, EntornoOCL_t entorno) {

    double *vector_out;

    cl_mem buf_in, buf_out,buf_in2;


    int *vec_terna;
    int   n=N-1;
    vec_terna= (int *)malloc(sizeof(int)*3);
    double *H;
     H = (double *) malloc(sizeof(double)*N*N);
     for(int z= 0; z <N*N; z++){
         H[z]=z;
       }

       printf("------------------------------\n");
       printf("    MATRIZ \n");
       printf("------------------------------\n");
         for(int z= 0; z < N*N; z++){
           if(z%N==0&&z!=0)
             printf("\n");
           printf("%.2f ",H[z]);
           }
           printf("\n");
           printf("------------------------------\n");
        for(int t=0; t<num_sb; t++){
          vector_out= (double *)malloc(sizeof(double)*N*N);
          for(int z= 0; z <N*N; z++){
              vector_out[z] =0;
            }
          int c=ternas[t].x;
          int f=ternas[t].y;
          int tam=ternas[t].t;

          int cb=c;
          double S[tam*tam];
            for(int p=0; p<tam; p++){
                int fN=f*N;
                int pN=p*tam;
                for(int k=0; k<tam; k++){

                    S[pN+k]=H[fN+c];
                    if(c==n)
                        c=0;
                    else
                        c++;

                }
                c=cb;

                if(f==n)
                    f=0;
                else
                    f++;

            }
            printf("------------------------------\n");
            printf("        SUBMATRIZ\n");
              printf("Submatriz %d--Tam:%d--Fil:%d--Col:%d--NumSub:%d\n",t,tam,ternas[t].y,ternas[t].x,num_sb);
            printf("------------------------------\n");
              for(int z= 0; z < tam*tam; z++){
                if(z%tam==0&&z!=0)
                  printf("\n");
                printf("%.2f ",S[z]);
                }
                printf("\n");
                printf("------------------------------\n");


            size_t wi=tam;
              cl_event exec, recb, env;
          CrearBuffer(entorno.contexto, CL_MEM_USE_HOST_PTR, (size_t) N*N*sizeof(double),H, buf_in);
          CrearBuffer(entorno.contexto, CL_MEM_USE_HOST_PTR, (size_t) N*N*sizeof(double),vector_out, buf_out);
          CrearBuffer(entorno.contexto, CL_MEM_USE_HOST_PTR, (size_t) tam*sizeof(double),S, buf_in2);

          AsignarParametro(entorno.kernel, 0, sizeof(int), &N);
          AsignarParametro(entorno.kernel, 1, sizeof(cl_mem), &buf_in);
          AsignarParametro(entorno.kernel, 2, sizeof(cl_mem), &buf_in2);
          AsignarParametro(entorno.kernel, 3, sizeof(int), &ternas[t].x);
          AsignarParametro(entorno.kernel, 4, sizeof(int), &ternas[t].y);
          AsignarParametro(entorno.kernel, 5, sizeof(int), &ternas[t].t);
          AsignarParametro(entorno.kernel, 6, sizeof(cl_mem), &buf_out);

          EnviarBuffer(entorno.cola, buf_in, false ,0, N*N*sizeof(double), H,0,NULL, env);
          EnviarBuffer(entorno.cola, buf_in2, false ,0, tam*sizeof(double), S,0,NULL, env);

          EjecutarKernel(entorno.cola ,entorno.kernel, 1,NULL ,&wi,NULL, 0,NULL, exec);
          RecibirBuffer(entorno.cola, buf_out, false ,0 , N*N*sizeof(double), vector_out, 0, NULL, recb);
          clFinish(entorno.cola);

          printf("------------------------------\n");
          printf("    MATRIZ RESULTADO\n");
          printf("------------------------------\n");
            for(int z= 0; z < N*N; z++){
              if(z%N==0&&z!=0)
                printf("\n");
              printf("%.2f ",vector_out[z]);
                A[z] = A[z]+vector_out[z];
              }
              printf("\n");
              printf("------------------------------\n");


   }







}
// **************************************************************************
// *************************** FIN IMPLEMENTACI�N ***************************
// **************************************************************************

/*
 * Recibir� los siguientes par�metros (los par�metros entre corchetes son opcionales): fichEntrada [-d]
 * fichEntrada -> Obligatorio. Fichero de entrada con los par�metros de lanzamiento de los experimentos
 * -d -> Opcional. Si se indica, se mostrar�n por pantalla los valores iniciales, finales y tiempo de cada experimento
 * -wi work_items -> Opcional. Si se indica, se lanzar�n tantos work items como se indique en work_items (para OpenCL)
 * -wi_wg workitems_por_workgroup -> Opcional. Si se indica, se lanzar�n tantos work items en cada work group como se indique en WorkItems_por_WorkGroup (para OpenCL)
 */
int main(int argc,char *argv[]) {
    int i,
    debug=0,				   // Indica si se desean mostrar los tiempos y resultados parciales de los experimentos
    num_workitems=0, 		   // N�mero de work items que se utilizar�n
    workitems_por_workgroups=0, // N�mero de work items por cada work group que se utilizar�n
    num_problems, 		 	   // N�mero de experimentos
    matrix_size, 		 	   // Tama�o de la matriz
    seed, 			 	   // Semilla
    num_random;		 	   // N�mero de submatrices
    double *A; 			 	   // Matriz de datos. Se representa en forma de vector. Para acceder a la fila f y la columna c: A[f*N+c]
    terna_t *ternas;			   // Vector de ternas con los tama�os y las coordenadas de las submatrices
    long long ti,			 	   // Tiempo inicial
    tf,			 	   // Tiempo final
    tt=0; 		 	   // Tiempo acumulado de los tiempos parciales de todos los experimentos realizados
    FILE *f;				 	   // Fichero con los datos de entrada
    EntornoOCL_t entorno; 	 	   //Entorno para el control de OpenCL

    if (!ObtenerParametros(argc, argv, &debug, &num_workitems, &workitems_por_workgroups)) {
        printf("Ejecuci�n incorrecta\nEl formato correcto es %s fichEntrada [-d] [-wi work_items] [-wi_wg workitems_por_workgroup]\n", argv[0]);
        return 0;
    }

    InicializarEntornoOCL(&entorno);

    // Se leen el n�mero de experimentos a realizar
    f=fopen(argv[1],"r");
    fscanf(f, "%d",&num_problems);

    for(i=0;i<num_problems;i++) {
        //Por cada experimento se leen
        fscanf(f, "%d",&matrix_size);	//Tama�o de la matriz (cuadrada)
        fscanf(f, "%d",&seed);		//Semilla para la inicializaci�n de n�meros aleatorios
        fscanf(f, "%d",&num_random);	//N�mero de submatrices a generar
        //Reserva de memoria para la matriz de datos y las ternas de las submatrices
        A = (double *) malloc(sizeof(double)*matrix_size*matrix_size);
        ternas = (terna_t *) malloc(sizeof(terna_t)*num_random);

        srand(seed);
        initialize(matrix_size,A,ternas,num_random);

        if (debug) {
            printf("Matriz original del experimento %d:\n", i); escribir(matrix_size, A);
            printf("Submatrices del experimento %d:\n", i); escribirt(ternas, num_random);
        }

        ti=mseconds();
        ocl(matrix_size, A, ternas, num_random, entorno);
        tf=mseconds();
        tt+=tf-ti;

        if (debug) {
            printf("Tiempo del experimento %d: %Ld ms\n", i, tf-ti);
            printf("Matriz resultado del experimento %d:\n", i); escribir(matrix_size, A);
        }
        free(A);
        free(ternas);
    }

    LiberarEntornoOCL(&entorno);
    printf("Tiempo total de %d experimentos: %Ld ms\n", num_problems, tt);
    fclose(f);
    return 0;
}
