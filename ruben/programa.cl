__kernel void sec( int N,__global double *A,__global double *S,  int c,int f,int tam,__global double *B) {

    size_t id = get_global_id(0), num_wi = get_global_size(0);
    int ini =id, fin=(id+1),Sfila=0,cb=c,fb=f,fbn,n=N-1;

            fbn=(fb+id)*N;
            for(int Scasilla=ini*tam; Scasilla<(ini*tam)+tam; Scasilla++){
                for(int col=0; col<tam; col++){
                    B[fbn+cb]=B[fbn+cb]+S[Scasilla]*S[Sfila];

                    Sfila++;
                    if(cb==n){
                        cb=0;
                    }
                    else{
                        cb++;
                    }
                }
                cb=c;
            }

       }
