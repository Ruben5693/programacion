#include <mpi.h>
#include <stdio.h> 
#include <string.h>

int main(int argc, char *argv[]) {
    
    int myrank;
    MPI_Comm parent;
    
    //inicializa el entorno MPI del hijo
    MPI_Init(&argc, &argv);
    //Obtiene su rank
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    //Obtiene el comunicador con el padre
    MPI_Comm_get_parent(&parent);
    
    if (parent == MPI_COMM_NULL) {
        printf("No existe Padre creado.\n");
        return 0;
    }
    
    //Recibe la matriz A
    int a[10][10];
    MPI_Status status_1;
    
   
    MPI_Recv(a, 100, MPI_INT,0, 0, parent, &status_1);
        
    
    
    //Recibe la columna i-ésima de B (Col)
    int b[10];
    MPI_Status status_2;
    MPI_Recv(b, 10, MPI_INT, 0, 0, parent, &status_2);
    
    
    //Para i desde 0 hasta N
    int ColResult[10];
    for (int i=0;i<10; i++){
        //ColResult[i]=0
        ColResult[i]=0;
    }
    
    //Para j desde 0 hasta N
    for (int i=0;i<10; i++){
        for (int j=0;j<10; j++){
            //ColResult [i]+=MatrizA[i][j]*Col[j]
            ColResult [i]+=a[i][j]*b[j];
        }
    }
    
    //Envía la columna ColResult al padre
    MPI_Send(ColResult, 10, MPI_INT, 0, 0, parent);
    
    //Finaliza el entorno MPI del hijo
    MPI_Finalize();
}