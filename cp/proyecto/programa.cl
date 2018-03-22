__kernel void sec(__global int N,__global double *A,__global terna_t *ternas, __global int num_sb,__global double *B) {
  int nn=N*N;
    double B[nn]; 
    int cb, fb,c,f,tam,fN,pN,s2,fbn,n;
    n=N-1;
    
    size_t id = get_global_id(0), num_wi = get_global_size(0);
    int ini, fin, i;
    
    
    for(int t=0; t<num_sb; t++){
        
        c=ternas[t].x;
        f=ternas[t].y;
        tam=ternas[t].t;
        
        cb=c;
        fb=f;
        
        double S[tam*tam]; 
        for(int p=0; p<tam; p++){
            fN=f*N;
            pN=p*tam;
            for(int k=0; k<tam; k++){
                
                S[pN+k]=A[fN+c];
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
        
        c=cb;
        f=fb;
        
        ini=id;
        fin=(id+1);
        s2=0;
         for(int h=0; h<tam; h++){
             fbn=fb*N;
            for(int p=ini; p<fin; p++){
                for(int k=0; k<tam; k++){
                    B[fbn+cb]=B[fbn+cb]+S[p]*S[s2];
                    s2++;
                    if(cb==n){
                        cb=0;
                    }
                    else{
                        cb++;
                    }
                   
                }
                cb=c;
                
            }
            s2=0;
            if(fb==n)
                fb=0;
            else
                fb++;
         }
        
    }
    }  
    
}
