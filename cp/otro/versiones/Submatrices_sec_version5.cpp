#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>


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
// ***************************** IMPLEMENTACI�N *****************************
// **************************************************************************
/*
N -> Tama�o de la matriz N
A -> Matriz
ternas -> Vector de ternas con los tama�os y las coordenadas de las submatrices
num_sb -> N�mero de submatrices
*/
void sec(int N,double *A,terna_t *ternas, int num_sb) {
    int nn=N*N;
    double B[nn]; 
    int colBA2, filBA1,c,f,tam,save,fN,pN;
    
    for(int z= 0; z <nn; z++)
        B[z] =A[z];    
    
    for(int t=0; t<num_sb; t++){
        
        c=ternas[t].x;
        f=ternas[t].y;
        tam=ternas[t].t;
        colBA2=c;
        filBA1=f;
        
        double S[tam*tam]; 
        for(int p=0; p<tam; p++){
            fN=f*N;
            pN=p*N;
            for(int k=0; k<tam; k++){ 
                S[pN+k]=A[fN+c];
                
                if(c==N-1)
                    c=0;
                else
                    c++;
                
            }
            
            if(f==N-1)
                f=0;
            else
                f++;
            
        }
        
        c=colBA2;
        f=filBA1;
        
        

        
        for(int p=0; p<tam; p++){
           
            pN=p*N;
            for(int k=0; k<tam; k++){
                
                save=filBA1*N+colBA2;
                for(int h=0; h<tam; h++)
                    B[save]=B[save]+S[pN+h]*S[h*N+k];
                
                
                if(colBA2==N-1)
                    colBA2=0;
                else
                    colBA2++;
            }
            
            if(filBA1==N-1)
                filBA1=0;
            else
                filBA1++;

            colBA2=c;
        }
        
    }
    
    for(int z= 0; z < nn; z++){
        A[z] = B[z];
    }  
    
}
// **************************************************************************
// *************************** FIN IMPLEMENTACI�N ***************************
// **************************************************************************

/*
Recibir� los siguientes par�metros (los par�metros entre corchetes son opcionales): fichEntrada [-d]
fichEntrada -> Obligatorio. Fichero de entrada con los par�metros de lanzamiento de los experimentos
-d -> Opcional. Si se indica, se mostrar�n por pantalla los valores iniciales, finales y tiempo de cada experimento
*/
int main(int argc,char *argv[]) {
	int i,
		debug=0,		  // Indica si se desean mostrar los tiempos y resultados parciales de los experimentos
		num_problems, 	  // N�mero de experimentos
		matrix_size, 	  // Tama�o de la matriz
		seed, 		  // Semilla  
		num_random; 	  // N�mero de submatrices
	double *A; 		  // Matriz de datos. Se representa en forma de vector. Para acceder a la fila f y la columna c: A[f*N+c]
	terna_t *ternas;	  // Vector de ternas con los tama�os y las coordenadas de las submatrices
	long long ti,		  // Tiempo inicial
			tf,		  // Tiempo final
			tt=0; 	  // Tiempo acumulado de los tiempos parciales de todos los experimentos realizados
	FILE *f;			  // Fichero con los datos de entrada

	if (!ObtenerParametros(argc, argv, &debug)) {
		printf("Ejecuci�n incorrecta\nEl formato correcto es %s fichEntrada [-d]\n", argv[0]);
		return 0;
	}
	
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