
#include <stdio.h> 
#include <string.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>
		
//nodo 4
//gcc p2_1.c -o p2_1 -fopenmp -lm

int main(int argc, char *argv[]) {
    
    double start= omp_get_wtime();
    int iteraciones= atoi(argv[1]);
    
    //contador=0
    int contador=0;
    //para i desde 1 hasta NumIteraciones
    srand(time(NULL));
    
    for (int i=0; i<iteraciones;i++){
        
        //x=generar número aleatorio
        //y=generar número aleatorio
        
        float x= (float)rand()/RAND_MAX;
        float y= (float)rand()/RAND_MAX;
        
        //-----mrand-----
        //sramd(semilla);
        //x=UniformRand(1, 0);
        //-----mrand-----
        
        
        //----MersenneTwister----
        //MTRand r(semilla);
        //r.rand()
        //----MersenneTwister----
        
        
        //d=distancia_a_0_0(x, y)
        float d=sqrt((pow (x, 2)+pow (y, 2)));
        
        //si d<=1 entonces contador=contador+1
        if( d<=1)
            contador++;
        //fin para
    }
    
    //pi=contador*4/NumIteraciones
    float pi=(float)contador*4.0/iteraciones;
    double end = omp_get_wtime();
    end= end-start;
    
    printf("----------------------\n");
    printf("PI: %f \n",pi);
    printf("----------------------\n");
    printf("Tiempo de ejecucion: %f \n",end);
    printf("----------------------\n");
    
}