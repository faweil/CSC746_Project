#include <iostream>
#include <omp.h>
/*------- This is the parallel quick sort implementation with openMP-----------*/
// Array = array which has to get sorted in ascending order
// lb = lower bound, first index of Array
// ub = upper bound, last index of Array
// pivot = last element in the Array



int partition_openMP(int64_t lb, int64_t ub, uint64_t* Array){
    int64_t pivot = Array[ub];
    int64_t i = lb - 1;
    

    for(int64_t j = lb; j < ub; ++j){
        if(Array[j] < pivot){
	        //swap arr[i+1] and arr[j
            i++;
	        int64_t help = Array[i];
            Array[i] = Array[j];
            Array[j] = help;
	    }
    }

    //swap arr[i+1] and arr[ub] (pivot)
    i++;
    Array[ub] = Array[i];
    Array[i] = pivot;
    return i;
}


//int nthreads = omp_get_num_threads();
//int thread_id = omp_get_thread_num();
//printf("my_dgemv(): For actual timing runs, please comment out these printf() and omp_get_*() statements. \n");
//printf("my_dgemv(): Hello world: thread %d of %d checking in. \n", thread_id, nthreads);

void quickSort_openMP(int64_t lb, int64_t ub, uint64_t* Array){

    if(lb < ub)
    {
        //std::cout << "-------------LEETS GOO-----------------" << std::endl;
        #pragma omp parallel
        {
            //nt nthreads = omp_get_num_threads();
            //int thread_id = omp_get_thread_num();
            
            //printf("quickSort_openMP: Hello world: thread %d of %d checking in. \n", thread_id, nthreads);

            int64_t pivot_index = partition_openMP(lb, ub, Array);

            #pragma omp task shared(Array)
            { 
                //int thread_id = omp_get_thread_num();
                //printf("quickSort_openMP: Hello world: thread %d of %d checking in. \n", thread_id, nthreads);
                //printf("in first section\n");
                quickSort_openMP(lb, pivot_index - 1, Array);            // left part of array
            }    
            #pragma omp task shared(Array)
            {
                //int thread_id = omp_get_thread_num();
                //printf("quickSort_openMP: Hello world: thread %d of %d checking in. \n", thread_id, nthreads);
                //printf("in second section\n");
                quickSort_openMP(pivot_index + 1, ub, Array);            // right part of array
            }
        }
    }

}