#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>


typedef struct {
	int x,  // Coordenada x de la submatriz
		y, // Coordenada y de la submatriz
		t; // Tamaño de la submatriz
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
c
c     mseconds - returns elapsed milliseconds since Jan 1st, 1970.
c
*/
long long mseconds(){
  struct timeval t;
  gettimeofday(&t, NULL);
  return t.tv_sec*1000 + t.tv_usec/1000;
}

int ObtenerParametros(int argc, char *argv[], int *debug) {
	int i;
	*debug=0;
	if (argc<2)
		return 0;
	for (i=2; i<argc;) {
		if (strcmp(argv[i], "-d")==0) {
			*debug=1;
			i++;
		}
		else
			return 0;
	}
	return 1;
}

// **************************************************************************
// ***************************** IMPLEMENTACIÓN *****************************
// **************************************************************************
/*
N -> Tamaño de la matriz N
A -> Matriz
ternas -> Vector de ternas con los tamaños y las coordenadas de las submatrices
num_sb -> Número de submatrices
*/
void sec(int N,double *A,terna_t *ternas, int num_sb) {
    
    double B[N*N]; 
    
    
    for(int z= 0; z < N*N; z++){
        B[z] =A[z];    
        
    }
    for(int t=0; t<num_sb; t++){
        
        int c=ternas[t].x;
        int f=ternas[t].y;
        int tam=ternas[t].t;
        
        int colB, filB,colA1, colA2, filA1, filA2;
        
        colB=c;
        filB=f;
        
        colA1=c;
        filA1=f;
        
        colA2=c;
        filA2=f;
        
        for(int p=0; p<tam; p++){
            
            for(int k=0; k<tam; k++){
                
                for(int h=0; h<tam; h++){
                    
                    B[filB*N+colB]=B[filB*N+colB]+A[filA1*N+colA1]*A[filA2*N+colA2];
                    
                    if(colA1==N-1)
                        colA1=0;
                    else
                        colA1++;
                    
                    if(filA2==N-1)
                        filA2=0;
                    else
                        filA2++;
                }
                
                // primer bucle 
                
                // colB++
                if(colB==N-1)
                    colB=0;
                else
                    colB++;
                
                // colA2++;
                if(colA2==N-1)
                    colA2=0;
                else
                    colA2++;
                
                // colA1=c
                colA1=c;
                // filA2=f
                filA2=f;
                
            }
            
            // segundo bucle
            
            // filB++
            if(filB==N-1)
                filB=0;
            else
                filB++;
            // colB=c
            colB=c;
            // colA2=c
            colA2=c;
            
            // filA1++
            if(filA1==N-1)
                filA1=0;
            else
                filA1++;
            
        }
        
    }
    
    for(int z= 0; z < N*N; z++){
        A[z] = B[z];
    }  
    
}
// **************************************************************************
// *************************** FIN IMPLEMENTACIÓN ***************************
// **************************************************************************

/*
Recibirá los siguientes parámetros (los parámetros entre corchetes son opcionales): fichEntrada [-d]
fichEntrada -> Obligatorio. Fichero de entrada con los parámetros de lanzamiento de los experimentos
-d -> Opcional. Si se indica, se mostrarán por pantalla los valores iniciales, finales y tiempo de cada experimento
*/
int main(int argc,char *argv[]) {
	int i,
		debug=0,		  // Indica si se desean mostrar los tiempos y resultados parciales de los experimentos
		num_problems, 	  // Número de experimentos
		matrix_size, 	  // Tamaño de la matriz
		seed, 		  // Semilla  
		num_random; 	  // Número de submatrices
	double *A; 		  // Matriz de datos. Se representa en forma de vector. Para acceder a la fila f y la columna c: A[f*N+c]
	terna_t *ternas;	  // Vector de ternas con los tamaños y las coordenadas de las submatrices
	long long ti,		  // Tiempo inicial
			tf,		  // Tiempo final
			tt=0; 	  // Tiempo acumulado de los tiempos parciales de todos los experimentos realizados
	FILE *f;			  // Fichero con los datos de entrada

	if (!ObtenerParametros(argc, argv, &debug)) {
		printf("Ejecución incorrecta\nEl formato correcto es %s fichEntrada [-d]\n", argv[0]);
		return 0;
	}
	
	// Se leen el número de experimentos a realizar
	f=fopen(argv[1],"r");
	fscanf(f, "%d",&num_problems);
	
	for(i=0;i<num_problems;i++) {
		//Por cada experimento se leen
		fscanf(f, "%d",&matrix_size);	//Tamaño de la matriz (cuadrada)
		fscanf(f, "%d",&seed);		//Semilla para la inicialización de números aleatorios
		fscanf(f, "%d",&num_random);	//Número de submatrices a generar
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
		sec(matrix_size, A, ternas, num_random);
		tf=mseconds(); 
		tt+=tf-ti;
		
		if (debug) {
			printf("Tiempo del experimento %d: %Ld ms\n", i, tf-ti);
			printf("Matriz resultado del experimento %d:\n", i); escribir(matrix_size, A);
		}
		free(A);
		free(ternas);
	}
  
	printf("Tiempo total de %d experimentos: %Ld ms\n", num_problems, tt);
	fclose(f);
	return 0;
}
