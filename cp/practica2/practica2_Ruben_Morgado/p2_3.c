
#include <stdio.h> 
#include <string.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>
#include "MersenneTwister.h"
#include "mramd.h" 

//nodo 4
//g++ p2_4.c mramd.cpp -o p2_4 -fopenmp -lm

int main(int argc, char *argv[]) {
    
    double start= omp_get_wtime();
    int iteraciones= atoi(argv[1]);
    int numHilos = atoi(argv[2]);
    int random = atoi(argv[3]);
    
    //contador=0
    int contador=0;
    MTRand r (time(NULL));
    
    switch (random)
    {
        case 1:
            srand(time(NULL));
            break;
            
        case 2:
            sramd(time(NULL));
            break;
    }
    
    //establecer numero de hilos
    #pragma omp parallel num_threads (numHilos) private(r)
    
    //para i desde 1 hasta NumIteraciones
    #pragma omp for reduction(+:contador)
    for (int i=0; i<iteraciones;i++){
        
        //x=generar número aleatorio
        //y=generar número aleatorio
        
        float x;
        float y;
        
        switch (random)
        {
            case 1:
                x=(float)rand()/RAND_MAX;
                y=(float)rand()/RAND_MAX;
                break;
                
            case 2:
                x=(float)UniformRand(1, 0);
                y=(float)UniformRand(1, 0);
                break;
                
            case 3:
                x=(float)r.rand();
                y=(float)r.rand();
                break;
        }
        
        
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