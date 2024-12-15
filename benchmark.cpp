#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>
#include <string.h>
#include <omp.h>

extern void quickSort(int64_t lb, int64_t ub, uint64_t* A);
extern void mergeSort(uint64_t* A, int64_t n, uint64_t* t);


extern void quickSort_openMP(int64_t lb, int64_t ub, uint64_t* A);
extern void mergeSort_openMP(uint64_t* A, int64_t n, uint64_t* t);

extern void setup(int64_t N, uint64_t* A);


void testRun(){
   int N = 20;   // problem size
   std::vector<uint64_t> exampleArray(N);
   std::vector<uint64_t> t(N);  // for merge Sort

   // invoke user code to set up the problem
   setup(N, &exampleArray[0]);
   std::cout << "Test run with small N size of " << N << std::endl;

   std::cout << "\n" << "----bevore sorting----" << std::endl;

   for (const auto& a : exampleArray){
      std::cout << a << " ";
   }
   std::cout << std::endl;

   /** choose (uncomment) one of the following sorting algorithms **/

   //mergeSort(&exampleArray[0], exampleArray.size(), &t[0]);
   //mergeSort_openMP(&exampleArray[0], exampleArray.size(), &t[0]);

   //quickSort(0, exampleArray.size()-1, &exampleArray[0]);
   //quickSort_openMP(0, exampleArray.size()-1, &exampleArray[0]);


   std::cout << "\n" << "----after sorting----" << std::endl;

   for(const auto& a : exampleArray){
      std::cout << a << " ";
   }
   std::cout << std::endl;
   std::cout << std::endl;
}



int main(int argc, char** argv) 
{
   int numThreads = 1;

   if(argc < 2) {
      printf("no concurrency level from command line\n");
      printf("in this case concurrency level 1 is used\n");
   }else{
      // Convert command-line argument to integer
      numThreads = std::atoi(argv[1]);
   }

   // Set the number of threads for OpenMP
   omp_set_num_threads(numThreads);
   std::cout << "Number of threads set to: " << numThreads << std::endl;


   //testRun();      // with small size of N, to check if sorting is correct


   std::cout << std::fixed << std::setprecision(8);

   #define MAX_PROBLEM_SIZE 1 << 28  //  256M
   //#define MAX_PROBLEM_SIZE 400

   // 16, 32, 64, 128, 256 -million.
    std::vector<int64_t> problem_sizes{
      MAX_PROBLEM_SIZE >> 4, 
      MAX_PROBLEM_SIZE >> 3, 
      MAX_PROBLEM_SIZE >> 2, 
      MAX_PROBLEM_SIZE >> 1, 
      MAX_PROBLEM_SIZE
   };
   
   int n_problems = problem_sizes.size();

   for (int64_t n : problem_sizes) 
   {
      printf("Working on problem size N=%lld \n", n);

      std::vector<uint64_t> A(n);
      std::vector<uint64_t> t(n);      // for mergeSort algo

      // invoke user code to set up the problem
      setup(n, &A[0]);

      // insert your timer code here
      std::chrono::time_point<std::chrono::high_resolution_clock> start_time = std::chrono::high_resolution_clock::now();


      /** choose (uncomment) one of the following sorting algorithms **/

      //mergeSort(&A[0], n, &t[0]);
      mergeSort_openMP(&A[0], n, &t[0]);

      //quickSort(0, n-1, &A[0]);
      //quickSort_openMP(0, n-1, &A[0]);


      // insert your end timer code here, and print out elapsed time for this problem size
      std::chrono::time_point<std::chrono::high_resolution_clock> end_time = std::chrono::high_resolution_clock::now();

      std::chrono::duration<double> elapsed = end_time - start_time;

      printf(" Sorting is done\n");
      printf(" elapsed time = %f \n", elapsed);

   } // end loop over problem sizes
    
}

// EOF
