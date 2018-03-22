__kernel void sec( int N,__global double *A,__global double *S,  int c,int f,int tam,__global double *B) {
    int nn=N*N;
    int n=N-1;
    size_t id = get_global_id(0), num_wi = get_global_size(0);
    int ini, fin;

        ini=id;
        fin=(id+1);
        int Sfila=0;
        int cb=c;
        int fb=f;
        int fbn;
        int aux=0;

             fbn=(fb+id)*N;

            for(int Scasilla=ini*tam; Scasilla<(ini*tam)+tam; Scasilla++){



                for(int col=0; col<tam; col++){
                    B[fbn+cb]=B[fbn+cb]+S[Scasilla]*S[Sfila];







                    if(id==0){
                      /*
                    printf("id:%d\n",id );
                    printf("Sfila:%d\n",Sfila );
                    printf("Casilla:%d\n",Scasilla );
                    */
                    printf("%.2f *", S[Sfila]);
                    printf(" %.2f ->", S[Scasilla]);
                    printf(" %d \n", fbn+cb);
                  }
                    Sfila++;
                    if(cb==n){
                        cb=0;
                    }
                    else{
                        cb++;
                    }

                }
                cb=c;
                aux++;

            }

       }
