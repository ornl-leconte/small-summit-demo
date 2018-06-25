
#ifndef __ENGINE_CUDA_H__
#define __ENGINE_CUDA_H__


#include "fr.h"

// give this so we know what to use
void engine_cuda_init(fractal_params_t _fr_p);

void engine_cuda_compute(workload_t workload, unsigned char * output, int * output_iters);


#endif

