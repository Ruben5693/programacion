#include <mpi.h>
#include <stdio.h> 
#include <string.h>

int main(int argc, char *argv[]) {
    //Inicializa el entorno MPI del padre
    MPI_Init(NULL, NULL);
    //Inicializa las matrices A y B
    int a[10][10];
    int b[10][10];
    
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            a[i][j]=2;
            b[i][j]=2;
        }
    }
    
    //Lanza N procesos hijos
    MPI_Comm intercomm;
    int numProcSpw=10;
    
    MPI_Comm_spawn(argv[1], MPI_ARGV_NULL, numProcSpw, MPI_INFO_NULL, 0, MPI_COMM_SELF, &intercomm, MPI_ERRCODES_IGNORE);
    
    
    //Crea un tipo derivado para enviar 1 columna
    MPI_Datatype vector_columnas;
    MPI_Type_vector (10, 1, 10, MPI_INT, &vector_columnas);
    MPI_Type_commit(&vector_columnas);
    
    //Para i desde 0 hasta N
    for(int i=0; i<10;i++){
        //Envía la matriz A al proceso i
        MPI_Send(a, 100, MPI_INT, i, 0, intercomm);
        //Envía la columna i de B al proceso i
        MPI_Send(&b[0][i], 1, vector_columnas, i, 0, intercomm);
        
        //Fin para
    }
    
    MPI_Status status_1;
    int result[10][10];
    //Para i desde 0 hasta N
    for(int i=0; i<10;i++){
        //Recibe la columna i de R del proceso i
        MPI_Recv(&result[0][i], 1, vector_columnas,i, 0, intercomm, &status_1);
    }
     
    //Mostrar la matriz resultado
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            printf("%d ",result[i][j]);
        }
        printf("\n");
    }
     
    //Liberar el tipo derivado
    MPI_Type_free(&vector_columnas);
    
    //Finaliza el entorno MPI del padre
    
    MPI_Finalize();
}