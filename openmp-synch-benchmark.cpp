#include <iostream>
#include <chrono>
#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <numeric>
#include <chrono>
#include "parallel_helpers.hpp"

using namespace std;

int main(int argc, char *argv[]) {

	std::cout << std::fixed << std::setprecision(9) << std::left;
	double time=0.0;
	chrono::high_resolution_clock::time_point start, end;

	// get number of processors
	size_t num_processors = omp_get_num_procs();
	std::cout << "Number of processors: " << num_processors << std::endl;

	// parallel computation changing number of threads till 2*number of threads
	for(size_t p = 2; p <= num_processors; p++){

//		cout << "Starting parallel CPU computation with " << i << " of " << num_processors <<" threads" << endl;

		#pragma omp parallel num_threads(p)
		{
			//each thread gets its id//
			size_t tid = omp_get_thread_num();

			#pragma omp critical
			{
				cadmium::dynamic::hpc_engine::pin_thread_to_core(tid);
			}

			for(size_t i=0; i<1000000; i++){
				#pragma omp master
				{
					start = std::chrono::high_resolution_clock::now();
				}

				#pragma omp barrier

				#pragma omp master
				{
					end = std::chrono::high_resolution_clock::now();
					std::chrono::duration<double> diff = end - start;
					time += std::chrono::duration<double>(diff).count();
				}
			}
		}
		//calculate average
		time = time/1000000;

		cout << "Barrier with " << p << " threads " << "takes: " << time << " seconds" << endl;

		// reset time variable
		time = 0.0;
	}

	return 0;
}
