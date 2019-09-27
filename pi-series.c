#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#define number_of_iterations 9000000000

//David H Bailey reference article: https://www.davidhbailey.com/dhbpapers/pi-formulas.pdf

void calculate_pi();
void method_1();
void method_2();

int main() {
	
	int i, method_counter, number_of_threads[] = {1, 2, 4, 8, 16};
	int sets_of_threads = sizeof(number_of_threads) / sizeof(number_of_threads[0]);
	int number_of_methods = 2;
	
	clock_t start_cycle, end_cycle;
	double cpu_time_used;
	
	double pi = 0;
	
	for (method_counter = 0; method_counter < number_of_methods; method_counter) {
		for (i = 0; i < sets_of_threads; i++) { //TODO:
			
			start_cycle = clock();
			pi = calculate_pi(number_of_threads[i], method_counter);
			end_cycle = clock();
			
			cpu_time_used = (end_cycle - start_cycle)/CLOCKS_PER_SEC;
			
			printf("\nFor %d threads, elapsed time was: %fs", i, cpu_time_used);
		}
	
		printf("Value of PI using method %d: %f", method_counter, pi);
	}
}

void calculate_pi(int number_of_threads, int method) {
	
	int thread_counter, rc;
	double partial[threads], pi;
	double initial_term, final_term, slice_size;
	
	pthread_t threads[number_of_threads];
	
	slice_size = number_of_iterations/number_of_threads;
	
	for (thread_counter = 0; thread_counter <= number_of_threads; thread_counter++) {
		
		initial_term = thread_counter * slice_size;
		final_term = (thread_counter + 1) * slice_size;
		
		if (method == 0) { // #13 series from David H. Bailey reference article
			rc = pthread_create(&threads[thread_counter], NULL, method_1(initial_term, final_term, *partial[thread_counter]), NULL);
			if (rc) {
				printf("/nFailed to create thread!");
			}
		} else if (method == 1) { // #15 series from David H. Bailey reference article
			rc = pthread_create(&threads[thread_counter], NULL, method_2(initial_term, final_term, *partial[thread_counter]), NULL);
			if (rc) {
				printf("/nFailed to create thread!");
			}
		}
	}
	
	for (thread_counter = 0; thread_counter <= number_of_threads; thread_counter++) { //suspend until all threads finish
		pthread_join(threads[thread_counter], (void**)&(NULL));
	}
	
	for (thread_counter = 0; thread_counter <= number_of_threads; thread_counter++) { //sum all partials of pi
		pi = pi + partial[thread_counter];
	}
	
}

void method_1(double initial_term, double final_term, double *result) { // #13 series from David H. Bailey reference article
	//TODO Implement #13 formula
}

void method_2(double initial_term, double final_term, double *result) { // #15 series from David H. Bailey reference article
	//TODO Implement #15 formula
}
