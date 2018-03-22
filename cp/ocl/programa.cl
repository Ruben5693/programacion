__kernel void mult_vec(__global float *input, __global float *output) {
    size_t id = get_global_id(0);
    output[id] = input[id]*input[id];
}

__kernel void mult_vec2(__global float *input, __global float *output, int N) {
    size_t id = get_global_id(0), num_wi = get_global_size(0);
    int ini, fin, i;
    ini=id*N/num_wi;
    fin=(id+1)*N/num_wi;
    
    for(i=ini; i<fin; i++)
        output[i] = input[i]*input[i];
}