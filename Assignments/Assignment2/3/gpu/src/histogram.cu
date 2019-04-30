#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>

#include <getopt.h>
#include <stdint.h>

#include "timer.h"

using namespace std;

#define THREAD_BLOCK_SIZE 512

/* Utility function, use to do error checking.

   Use this function like this:

   checkCudaCall(cudaMalloc((void **) &deviceRGB, imgS * sizeof(color_t)));

   And to check the result of a kernel invocation:

   checkCudaCall(cudaGetLastError());
*/
static void checkCudaCall(cudaError_t result) {
    if (result != cudaSuccess) {
        cerr << "cuda error: " << cudaGetErrorString(result) << endl;
        exit(1);
    }
}


__global__ void histogramKernel(const unsigned char* __restrict__ image, const uint64_t img_size, unsigned int* __restrict__ histogram) {

    const  uint64_t img_index = blockDim.x * blockIdx.x + threadIdx.x;
    __shared__ uint32_t block_hist[256];
    uint32_t thread_block_index = threadIdx.x;

    if (thread_block_index < 256) {
        block_hist[thread_block_index] = 0;
    }
    __syncthreads();

    if(img_index < img_size){
        atomicAdd(&block_hist[image[img_index]], 1);
    }

    __syncthreads();
    if (thread_block_index < 256) {
        uint32_t hist_block_index = blockIdx.x * 256 + threadIdx.x;
        histogram[hist_block_index] = block_hist[thread_block_index];
    }
}

__global__ void mergeKernel(uint32_t * __restrict__ block_histo, const uint32_t amout_of_blocks, uint32_t * __restrict__ histo) {
    uint32_t sum = 0;
    for (uint32_t idx = 0; idx < amout_of_blocks; ++idx) {
        uint32_t index = threadIdx.x + idx * 256;
        sum += block_histo[index];
    }

    histo[threadIdx.x] = sum;
}

void histogramCuda(const unsigned char* image, const uint64_t img_size, unsigned int* histogram, const int hist_size) {
    uint32_t blocks = img_size / THREAD_BLOCK_SIZE;
    uint32_t remainding = img_size % THREAD_BLOCK_SIZE;

    if(remainding) {
        ++blocks;
    }

    // allocate the vectors on the GPU
    unsigned char* deviceImage = NULL;
    checkCudaCall(cudaMalloc((void **) &deviceImage, img_size * sizeof(unsigned char)));
    if (deviceImage == NULL) {
        cout << "could not allocate memory!" << endl;
        return;
    }
    unsigned int* deviceHisto = NULL;
    checkCudaCall(cudaMalloc((void **) &deviceHisto, hist_size * sizeof(unsigned int)));
    if (deviceHisto == NULL) {
        checkCudaCall(cudaFree(deviceImage));
        cout << "could not allocate memory!" << endl;
        return;
    }

    uint32_t *deviceBlockHisto = NULL;
    checkCudaCall(cudaMalloc((void **) &deviceBlockHisto, blocks * hist_size * sizeof(uint32_t)));
    if (deviceBlockHisto == NULL) {
        checkCudaCall(cudaFree(deviceImage));
        checkCudaCall(cudaFree(deviceHisto));
        cout << "could not allocate memory!" << endl;
        return;
    }

    // cudaMemset(deviceHisto, 0, hist_size * sizeof(unsigned int));
    cudaMemset(deviceBlockHisto, 0, blocks * hist_size * sizeof(uint32_t));

    timer kernelTime1 = timer("kernelTime1");
    timer memoryTime = timer("memoryTime");

    uint32_t local_hist[hist_size];
    memset(local_hist, 0, hist_size * sizeof(uint32_t));

    // copy the original vectors to the GPU
    memoryTime.start();
    checkCudaCall(cudaMemcpy(deviceImage, image, img_size*sizeof(unsigned char), cudaMemcpyHostToDevice));
    memoryTime.stop();

    // execute kernel
    kernelTime1.start();
    histogramKernel<<<blocks, THREAD_BLOCK_SIZE>>>(deviceImage, img_size, deviceBlockHisto);
    cudaDeviceSynchronize();
    checkCudaCall(cudaGetLastError());

    mergeKernel<<<1, hist_size>>>(deviceBlockHisto, blocks, deviceHisto);
    cudaDeviceSynchronize();

    kernelTime1.stop();

    // check whether the kernel invocation was successful
    checkCudaCall(cudaGetLastError());

    // copy result back
    memoryTime.start();
    checkCudaCall(cudaMemcpy(histogram, deviceHisto, hist_size * sizeof(unsigned int), cudaMemcpyDeviceToHost));
    memoryTime.stop();

    checkCudaCall(cudaFree(deviceImage));
    checkCudaCall(cudaFree(deviceHisto));
    checkCudaCall(cudaFree(deviceBlockHisto));

    cout << "histogram (kernel): \t\t" << kernelTime1 << endl;
    cout << "histogram (memory): \t\t" << memoryTime << endl;
}

void histogramSeq(unsigned char* image, long img_size, unsigned int* histogram, int hist_size) {
  int i; 

  timer sequentialTime = timer("Sequential");
  
  for (i=0; i<hist_size; i++) histogram[i]=0;

  sequentialTime.start();
  for (i=0; i<img_size; i++) {
	histogram[image[i]]++;
  }
  sequentialTime.stop();
  
  cout << "histogram (sequential): \t\t" << sequentialTime << endl;

}

int main(int argc, char* argv[]) {
    uint64_t img_size = 655360;
    uint64_t hist_size = 256;

    int32_t c;

    char *file_name = NULL;
    
    while((c = getopt(argc, argv, "s:f:")) != -1) {
        switch (c)
        {    
            case 's':
                img_size = strtoul(optarg, 0, 10);
                break;
            
            case 'f':
                file_name = optarg;
                break;

            default:
                break;
        }
    }

    //Need to use __constant__ for image;

    uint8_t *image = NULL;
    unsigned int *histogramS = (unsigned int *)malloc(hist_size * sizeof(unsigned int));     
    unsigned int *histogram = (unsigned int *)malloc(hist_size * sizeof(unsigned int));

    memset(histogramS, 0, hist_size * sizeof(unsigned int));
    memset(histogram, 0, hist_size * sizeof(unsigned int));

    if (file_name != NULL){
        FILE *f;
        if (!(f = fopen(file_name, "r"))) {
            printf("unalbe to open %s", file_name);
            exit(1);
        }

        char format[2];
        unsigned imgw, imgh, maxv;

        if (fscanf(f, "%2s", format) != 1) exit(1); 
        if (format[0] != 'P' || format[1] != '2') {
            printf("only ASCII PGM input is supported");
            exit(1);
        }

        if (fscanf(f, "%u", &imgw) != 1 ||
        fscanf(f, "%u", &imgh) != 1 ||
        fscanf(f, "%u", &maxv) != 1) exit(1);
    
        img_size = imgw * imgh;
        image = (uint8_t *)malloc(img_size * sizeof(uint8_t));

        uint64_t idx;
        for (idx = 0; idx < img_size; ++idx) {
            if (fscanf(f, "%hhu", &image[idx]) != 1) {
                printf("invalid data\n");
                exit(1);
            }
        } 
    }
    else 
    {
        image = (uint8_t *)malloc(img_size * sizeof(uint8_t));
        for(long i=0; i<img_size; i++) {
            image[i] = (uint8_t) (i % hist_size);
        }
    }

    cout << "Compute the histogram of a gray image with " << img_size << " pixels." << endl;

    histogramSeq(image, img_size, histogramS, hist_size);
    histogramCuda(image, img_size, histogram, hist_size);
    
    // verify the resuls
    for(int i=0; i<hist_size; i++) {
	  if (histogram[i]!=histogramS[i]) {
            cout << "error in results! Bin " << i << " is "<< histogram[i] << ", but should be " << histogramS[i] << endl; 
            free(image);
            free(histogram);
            free(histogramS); 
            exit(1);
        }
    }
    cout << "results OK!" << endl;
     
    free(image);
    free(histogram);
    free(histogramS);         
    
    return 0;
}
