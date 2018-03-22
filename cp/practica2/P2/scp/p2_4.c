
#include <stdio.h> 
#include <string.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>
#include "MersenneTwister.h"
#include "mramd.h" 
#include <mpi.h>

//nodo 4
//mpic++ p2_4.c mramd.cpp -o p2_4 -fopenmp -lm

int main(int argc, char *argv[]) {
    
    
    int iteraciones= atoi(argv[1]);
    int numHilos = atoi(argv[2]);
    int size,rank;
    
    //Inicializa el entorno MPI del padre
    MPI_Init(NULL, NULL);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    iteraciones=iteraciones/size;
    
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    
    
    double start= omp_get_wtime();
    //contador=0
    int contador=0;
    
    sramd(time(NULL));
    
    //establecer numero de hilos
    #pragma omp parallel num_threads (numHilos)
    
    //para i desde 1 hasta NumIteraciones
    #pragma omp for reduction(+:contador)
    for (int i=0; i<iteraciones;i++){
        
        //x=generar número aleatorio
        //y=generar número aleatorio
        float x=(float)UniformRand(1, 0);
        float y=(float)UniformRand(1, 0);
        
        //d=distancia_a_0_0(x, y)
        float d=sqrt((pow (x, 2)+pow (y, 2)));
        
        //si d<=1 entonces contador=contador+1
        if( d<=1)
            contador++;
        //fin para
    }
    
    int cont;
    MPI_Reduce(&contador,&cont, 1, MPI_INT, MPI_SUM, 0,MPI_COMM_WORLD);
    
    if(rank==0){
        
        //pi=contador*4/NumIteraciones
        float pi=(float)cont*4.0/(iteraciones*size);
        
        double end = omp_get_wtime();
        end= end-start;
        printf("----------------------\n");
        printf("PI: %f \n",pi);
        printf("----------------------\n");
        printf("Tiempo de ejecucion: %f \n",end);
        printf("----------------------\n");
    }
    
    MPI_Finalize();
    
}