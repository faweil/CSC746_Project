#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string.h>
#include <omp.h>

extern void mergeSort(int64_t lb, int64_t ub, uint64_t* A);
extern void quickSort(int64_t lb, int64_t ub, uint64_t* A);

extern void quickSort_openMP(int64_t lb, int64_t ub, uint64_t* A);
extern void mergeSort_openMP(int64_t lb, int64_t ub, uint64_t* A);

extern void setup(int64_t N, uint64_t* A);


void testRun(){
   int N = 20;
   std::vector<uint64_t> exampleArray(N);

   // invoke user code to set up the problem
   setup(N, &exampleArray[0]);
   std::cout << "Test run with small N size of " << N << std::endl;

   std::cout << "\n" << "----bevore sorting----" << std::endl;

   for (const auto& a : exampleArray){
      std::cout << a << " ";
   }
   std::cout << std::endl;

   mergeSort_openMP(0, exampleArray.size()-1, &exampleArray[0]);
   
   std::cout << "\n" << "----after sorting----" << std::endl;

   for(const auto& a : exampleArray){
      std::cout << a << " ";
   }
   std::cout << std::endl;
}



/* The benchmarking program */
int main(int argc, char** argv) 
{
   //testRun();
   std::cout << std::fixed << std::setprecision(8);

   // #define MAX_PROBLEM_SIZE 1 << 28  //  256M
   #define MAX_PROBLEM_SIZE 200000

   // 16, 32, 64, 128, 256 -million.
    std::vector<int64_t> problem_sizes{
      MAX_PROBLEM_SIZE >> 4, 
      MAX_PROBLEM_SIZE >> 3, 
      MAX_PROBLEM_SIZE >> 2, 
      MAX_PROBLEM_SIZE >> 1, 
      MAX_PROBLEM_SIZE
   };
   
   std::vector<uint64_t> A(MAX_PROBLEM_SIZE);

   int64_t t;
   int n_problems = problem_sizes.size();

   // invoke user code to set up the problem
   setup(A.size(), &A[0]);

   omp_set_num_threads(16);

   // insert your timer code here
   std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();

   mergeSort_openMP(0, A.size()-1, &A[0]);

   // insert your end timer code here, and print out elapsed time for this problem size
   std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();

   std::chrono::duration<double> elapsed = end_time - start_time;
   printf(" elapsed time = %f \n", elapsed);

  // for (const auto& a : A){
  //    std::cout << a << " ";
  // }

  // std::cout << std::endl;

/* 
   // For each test size 
   for (int64_t n : problem_sizes) 
   {
      printf("Working on problem size N=%lld \n", n);

      // invoke user code to set up the problem
      setup(n, &A[0]);

      // insert your timer code here
      std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();


      // invoke method to perform the sum
      t = sum(n, &A[0]);


      // insert your end timer code here, and print out elapsed time for this problem size
      std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();

      std::chrono::duration<double> elapsed = end_time - start_time;

      printf(" Sum result = %lld \n",t);
      printf(" elapsed time = %f \n", elapsed);

   } // end loop over problem sizes
    */
}

// EOF
