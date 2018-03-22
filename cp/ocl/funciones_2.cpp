#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>


void CodigoError(cl_int err) {
    switch (err) {
        case CL_SUCCESS: printf("Ejecucion correcta\n"); break;
        case CL_BUILD_PROGRAM_FAILURE: printf("CL_BUILD_PROGRAM_FAILURE\n"); break;
        case CL_COMPILER_NOT_AVAILABLE: printf("CL_COMPILER_NOT_AVAILABLE\n"); break;
        case CL_DEVICE_NOT_AVAILABLE: printf("CL_DEVICE_NOT_AVAILABLE \n"); break;
        case CL_DEVICE_NOT_FOUND: printf("CL_DEVICE_NOT_FOUND\n"); break;
        case CL_INVALID_ARG_INDEX : printf("CL_INVALID_ARG_INDEX \n"); break;
        case CL_INVALID_ARG_SIZE : printf("CL_INVALID_ARG_SIZE \n"); break;
        case CL_INVALID_ARG_VALUE: printf("CL_INVALID_ARG_VALUE\n"); break;
        case CL_INVALID_BUFFER_SIZE : printf("CL_INVALID_BUFFER_SIZE \n"); break;
        case CL_INVALID_BUILD_OPTIONS: printf("CL_INVALID_BUILD_OPTIONS\n"); break;
        case CL_INVALID_COMMAND_QUEUE : printf("CL_INVALID_COMMAND_QUEUE \n"); break;
        case CL_INVALID_CONTEXT: printf("CL_INVALID_CONTEXT\n"); break;
        case CL_INVALID_DEVICE_TYPE: printf("CL_INVALID_DEVICE_TYPE\n"); break;
        case CL_INVALID_EVENT: printf("CL_INVALID_EVENT\n"); break;
        case CL_INVALID_EVENT_WAIT_LIST : printf("CL_INVALID_EVENT_WAIT_LIST \n"); break;
        case CL_INVALID_GLOBAL_WORK_SIZE : printf("CL_INVALID_GLOBAL_WORK_SIZE \n"); break;
        case CL_INVALID_HOST_PTR : printf("CL_INVALID_HOST_PTR \n"); break;
        case CL_INVALID_KERNEL: printf("CL_INVALID_KERNEL \n"); break;
        case CL_INVALID_KERNEL_ARGS : printf("CL_INVALID_KERNEL_ARGS \n"); break;
        case CL_INVALID_KERNEL_NAME: printf("CL_INVALID_KERNEL_NAME\n"); break;
        case CL_INVALID_MEM_OBJECT : printf("CL_INVALID_MEM_OBJECT \n"); break;
        case CL_INVALID_OPERATION : printf("\n"); break;
        case CL_INVALID_PLATFORM: printf("CL_INVALID_PLATFORM\n"); break;
        case CL_INVALID_PROGRAM : printf("CL_INVALID_PROGRAM \n"); break;
        case CL_INVALID_PROGRAM_EXECUTABLE : printf("CL_INVALID_PROGRAM_EXECUTABLE\n"); break;
        case CL_INVALID_QUEUE_PROPERTIES: printf("CL_INVALID_QUEUE_PROPERTIES\n"); break;
        case CL_INVALID_VALUE: printf("CL_INVALID_VALUE\n"); break;
        case CL_INVALID_WORK_DIMENSION : printf("CL_INVALID_WORK_DIMENSION \n"); break;
        case CL_INVALID_WORK_GROUP_SIZE : printf("CL_INVALID_WORK_GROUP_SIZE \n"); break;
        case CL_INVALID_WORK_ITEM_SIZE : printf("CL_INVALID_WORK_ITEM_SIZE \n"); break;
        case CL_MEM_OBJECT_ALLOCATION_FAILURE : printf("CL_MEM_OBJECT_ALLOCATION_FAILURE \n"); break;
        case CL_OUT_OF_HOST_MEMORY: printf("CL_OUT_OF_HOST_MEMORY\n"); break;
        case CL_OUT_OF_RESOURCES: printf("CL_OUT_OF_RESOURCES\n"); break;
        case CL_PROFILING_INFO_NOT_AVAILABLE : printf("CL_PROFILING_INFO_NOT_AVAILABLE \n"); break;
        default: printf("Codigo de error no contemplado\n"); break;
    }
}

char leerFuentes(char *&src, const char *fileName)
{
    FILE *file = fopen(fileName, "rb");
    if (!file) {
        printf("Error al abrir el fichero '%s'\n", fileName);
        return 0;
    }
    
    if (fseek(file, 0, SEEK_END))  {
        printf("Error de posicionamiento en el '%s'\n", fileName);
        fclose(file);
        return 0;
    }
    
    long size = ftell(file);
    if (size == 0)  {
        printf("Error al calcular el tama�o del fichero '%s'\n", fileName);
        fclose(file);
        return 0;
    }
    
    rewind(file);
    src = (char *)malloc(sizeof(char) * size + 1);
    size_t res = fread(src, 1, sizeof(char) * size, file);
    if (res != sizeof(char) * size)   {
        printf("Error de lectura del fichero '%s'\n", fileName);
        fclose(file);
        free(src);
        return 0;
    }
    src[size] = '\0';
    fclose(file);
    return 1;
}


cl_int ObtenerPlataformas(cl_platform_id *&platforms, cl_uint &num_platforms){
    cl_int err;
    char cadena[1000];
    err= clGetPlatformIDs(0, NULL, &num_platforms);
    //control de error
    platforms=(cl_platform_id*)malloc(sizeof(cl_platform_id)*num_platforms);
    err=clGetPlatformIDs(num_platforms, platforms,NULL);
    
    for(int i=0; i<num_platforms;i++){
        err=clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 1000, cadena, NULL);
        //codigo error
        if(err!=CL_SUCCESS){
            CodigoError(err);
            return 0;
        }
        printf("platform %d: %s\n",i,cadena);
    }
    
    
}

cl_int CrearContexto(cl_platform_id platform, cl_device_id *devices,cl_uint num_devices, cl_context &contexto){
    cl_int err;
    cl_context_properties prop[3];
    prop[0]=CL_CONTEXT_PLATFORM;
    prop[1]=(cl_context_properties) platform;
    prop[2]=0;
    
    contexto= clCreateContext(prop,num_devices, devices, NULL, NULL, &err);
    
    if(err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }
}


cl_int CrearCola(cl_context contexto, cl_device_id device_id,cl_command_queue_properties prop, cl_command_queue &cola){
    cl_int err;
    
    cola= clCreateCommandQueue(contexto, device_id, prop, &err);
    
    if(err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }
}

cl_int ObtenerDispositivos(cl_platform_id platform ,  cl_device_type device_type, cl_device_id *&devices, cl_uint &num_devices){
    cl_int err;
    int i;
    char cadena[1000];
    err=clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,0 , NULL,&num_devices);
    //CodigoError
    devices=(cl_device_id*)malloc(sizeof(cl_device_id)*num_devices);
    err=clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);
    for(i=0;i<num_devices;i++){
        err=clGetDeviceInfo(devices[i], CL_DEVICE_NAME,1000, cadena, NULL);
        
        
        printf("Dispositivos %d: %s\n",i,cadena);
    }
}

cl_int CrearPrograma(cl_program &program, cl_context context,cl_uint num_devices, const cl_device_id *device_list, const char*options, const char *fichero){
    char *codigo, errores[10000];  
    cl_int err;
    leerFuentes(codigo, fichero);
    
    program=clCreateProgramWithSource(context,1,(const char **)&codigo, NULL,&err);
    
    if(err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }
    
    err= clBuildProgram(program, num_devices,  device_list, options, NULL, NULL);
    
    if(err==CL_BUILD_PROGRAM_FAILURE){
        
        err=clGetProgramBuildInfo (program,device_list[0], CL_PROGRAM_BUILD_LOG,9999, errores, NULL);
        
        if (err!=CL_SUCCESS){
            CodigoError(err);
            return err;
        }
        printf("---------------Errores de compilacion---------------- \n %s \n",errores);
        return CL_BUILD_PROGRAM_FAILURE;
    }
    
    if (err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }
}


cl_int CrearKernel(cl_kernel &kernel, cl_program program, const char *kernel_name){
    cl_int err;
    
    kernel=clCreateKernel(program,kernel_name,&err);
    
    if (err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }
}



cl_int CrearBuffer(cl_context context, cl_mem_flags flags, size_t size,void *host_ptr,cl_mem &buffer){
    
    cl_int err;
    
    buffer= clCreateBuffer(context, flags,size,host_ptr,&err);
    
    if (err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }
}



cl_int AsignarParametro(cl_kernel kernel, cl_uint arg_index, size_t arg_size,const void *arg_value){
    
    cl_int err;
    
    err= clSetKernelArg(kernel, arg_index,arg_size, arg_value);
    
    if (err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }  
}



cl_int EnviarBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_write,size_t offset, size_t cb, const void *ptr,cl_uint num_events,const cl_event *event_wait_list, cl_event &event){
    
    cl_int err;
    
    err=clEnqueueWriteBuffer(command_queue,  buffer,  blocking_write,offset,  cb, ptr,  num_events,event_wait_list, &event);
    
    if (err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }  
    
}


cl_int RecibirBuffer(cl_command_queue command_queue, cl_mem buffer, cl_bool blocking_read,size_t offset, size_t cb, void *ptr,cl_uint num_events,const cl_event *event_wait_list, cl_event &event){
    
    cl_int err;
    
    err= clEnqueueReadBuffer( command_queue,  buffer,  blocking_read,  offset,  cb, ptr,  num_events,   event_wait_list,  &event);
    
    
    if (err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }
    
}


cl_int EjecutarKernel(cl_command_queue command_queue,cl_kernel kernel, cl_uint work_dim,const size_t *global_work_offset,const size_t *global_work_size,size_t *local_work_size, cl_uint num_events,const cl_event *event_wait_list, cl_event &event){
    
    cl_int err;
    
    err=clEnqueueNDRangeKernel(command_queue,  kernel,  work_dim, global_work_offset, global_work_size, local_work_size,  num_events, event_wait_list, &event);
    
    if (err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }
}



cl_int ObtenerTiempoEjecucionEvento(cl_event event, cl_ulong &tiempo){
    
    cl_int err;
    cl_ulong ini,fin;
    
    err= clGetEventProfilingInfo( event, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &ini,NULL);
    
    
    if (err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }
    
    err= clGetEventProfilingInfo( event, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &fin,NULL);
    
    
    if (err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }
    
    tiempo=fin-ini;
    
}



cl_int ObtenerTiempoEjecucionEntreEventos(cl_event event_ini,cl_event event_fin, cl_ulong &tiempo){
    
    cl_int err;
    cl_ulong ini,fin;
    
    err= clGetEventProfilingInfo( event_ini, CL_PROFILING_COMMAND_START, sizeof(cl_ulong), &ini,NULL);
    
    
    if (err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }
    
    err= clGetEventProfilingInfo( event_fin, CL_PROFILING_COMMAND_END, sizeof(cl_ulong), &fin,NULL);
    
    
    if (err!=CL_SUCCESS){
        CodigoError(err);
        return err;
    }
    
    tiempo=fin-ini;
    
    
}
int main(int argc, char const *argv[]) {
    cl_uint num_platforms, num_dispositivos;
    cl_platform_id *plataforma;
    cl_device_id *Dispositivos;
    cl_context contexto;
    cl_command_queue cola;
    cl_program program;
    cl_kernel kernel;
    int i, N=100000000;
    float *vector_in, *vector_out;
    vector_in= (float *)malloc(sizeof(float)*N);
    vector_out= (float *)malloc(sizeof(float)*N);
    //     vctor_out = new float[N];
    cl_mem buf_in, buf_out;
    cl_event exec, recb, env;
    
    for(int i=0; i<N;i++)
        vector_in[i]=i;   
    
    ObtenerPlataformas(plataforma, num_platforms);
    
    for(i=0;i<num_platforms;i++){
        ObtenerDispositivos(plataforma[i],CL_DEVICE_TYPE_ALL, Dispositivos,num_dispositivos);
    }
    
    CrearContexto(plataforma[0], Dispositivos, num_dispositivos, contexto);
    CrearCola(contexto,Dispositivos[0],CL_QUEUE_PROFILING_ENABLE,cola);
    CrearPrograma(program, contexto,num_dispositivos, Dispositivos, "-g", "programa.cl");
    CrearKernel(kernel,program,"mult_vec");
    //fuincion ocl
    CrearBuffer(contexto, CL_MEM_COPY_HOST_PTR, (size_t) N*sizeof(float),vector_in, buf_in);
    CrearBuffer(contexto, CL_MEM_COPY_HOST_PTR, (size_t) N*sizeof(float),vector_out, buf_out);
    AsignarParametro(kernel, 0, sizeof(cl_mem), &buf_in);
    AsignarParametro(kernel, 1, sizeof(cl_mem), &buf_out);
    EnviarBuffer(cola, buf_in, false ,0, N*sizeof(float), vector_in,0,NULL, env);
    size_t wi=N;
    EjecutarKernel(cola ,kernel, 1,NULL ,&wi,NULL, 0,NULL, exec);
    RecibirBuffer(cola, buf_out, false ,0 , N*sizeof(float), vector_out, 0, NULL, recb);
    clFinish(cola);
    for(int i=0; i<10;i++)
        printf("%f\n",vector_out[i]);  
    
    cl_ulong tiempo;
    ObtenerTiempoEjecucionEvento(env, tiempo);
    printf("%f segundos \n", (float)tiempo/1000000000);
    
    ObtenerTiempoEjecucionEvento(exec, tiempo);
    printf("%f segundos \n", (float)tiempo/1000000000);
    
    ObtenerTiempoEjecucionEvento(recb, tiempo);
    printf("%f segundos \n", (float)tiempo/1000000000);
    
    ObtenerTiempoEjecucionEntreEventos(env, recb, tiempo);
    printf("%f segundos \n", (float)tiempo/1000000000);
    
    return 0;
}
