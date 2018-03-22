#include "mramd.cl"

__kernel void mult_vec(__global int *output, int N) {
    size_t id = get_global_id(0), num_wi = get_global_size(0);
    int ini, fin, i;
    ini=id*N/num_wi;
    fin=(id+1)*N/num_wi;
    int status;
    
    sramd( &status,(int)id);
    
    int contador=0;
    
    for(i=ini; i<fin; i++){
        
        //x=generar número aleatorio
        //y=generar número aleatorio
        //-----mrand-----
        
        float x=(float)ramd(&status)/MRAND_MAX;
        float y=(float)ramd(&status)/MRAND_MAX;
      
        //d=distancia_a_0_0(x, y)
        float d=sqrt((x*x)+(y*y));
        
        //si d<=1 entonces contador=contador+1
        if( d<=1)
            contador++;
        //fin para
    }
    output[id]=contador;
}