#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#define number_of_iterations 9000000000 //target
//#define number_of_iterations 176 //=16*11 max of iterations where all 16 slices have a non zero value for method 1
//#define number_of_iterations 368 //max of iterations where all 16 slices have a non zero value for method 2

//David H Bailey reference article: https://www.davidhbailey.com/dhbpapers/pi-formulas.pdf

long double calculate_pi();
void* method_1();
void* method_2();

int number_of_threads[] = {1, 2, 4, 8, 16};
double slice_size;
long double partials[16]; //TODO leght of partial must be max of number_of_threads[]


int main() {
	
	int i, method_counter, number_of_methods = 2;
	
	clock_t start_cycle, end_cycle;
	double cpu_time_used;
	
	long double pi = 0;
	
	int sets_of_threads = sizeof(number_of_threads) / sizeof(number_of_threads[0]); //number of elements in number_of_threads
	
	for (method_counter = 1; method_counter <= number_of_methods; method_counter++) {
		for (i = 0; i < sets_of_threads; i++) {
			
			start_cycle = clock();
			pi = calculate_pi(number_of_threads[i], method_counter);
			end_cycle = clock();
			
			cpu_time_used = (double)(end_cycle - start_cycle)/CLOCKS_PER_SEC;
			
			printf("\nFor %d threads, method %d, elapsed time was: %fs", number_of_threads[i], method_counter, cpu_time_used);
			printf("\nValue of PI using method %d and %d threads: %.*Lf", method_counter, number_of_threads[i], 63, pi);
		}
	}
	printf("\n");
}

long double calculate_pi(int number_of_threads, int method) {
	
	long thread_counter;
	int rc, thread_exit_code = 0;
	long double pi = 0;
	double initial_term, final_term;
	
	pthread_t threads[number_of_threads];
	
	slice_size = number_of_iterations/number_of_threads;
	
	for (thread_counter = 0; thread_counter < number_of_threads; thread_counter++) {
		
		initial_term = thread_counter * slice_size;
		final_term = (thread_counter + 1) * slice_size;
		
		if (method == 1) { // #13 series from David H. Bailey reference article
			rc = pthread_create(&threads[thread_counter], NULL, method_1, (void*)thread_counter);
			if (rc) {
				printf("\nFailed to create thread!");
			}
		} else if (method == 2) { // #15 series from David H. Bailey reference article
			rc = pthread_create(&threads[thread_counter], NULL, method_2, (void*)thread_counter);
			if (rc) {
				printf("\nFailed to create thread!");
			}
		}
	}
	
	for (thread_counter = 0; thread_counter < number_of_threads; thread_counter++) { //suspend until all threads finish
		rc = pthread_join(threads[thread_counter], (void**)&thread_exit_code);
		if (rc) {
			printf("\nFailed to join thread %ld", thread_counter);
		}
	}
	for (thread_counter = 0; thread_counter < number_of_threads; thread_counter++) { //sum all partials of pi
		//printf("\nSumming up partial of slice %ld: %.*Lf", thread_counter, 200, partials[thread_counter]);
		pi += partials[thread_counter];
	}
	//printf("\nValue of Pi using %d threads: %.*Lf", number_of_threads, 50, pi);
	return(pi);
	
}

void* method_1(void* void_slice) { // #13 series from David H. Bailey reference article
	long slice;
	slice = (long)void_slice;
	double initial_term = slice * slice_size;
	double final_term = ((slice + 1) * slice_size) - 1;
	//printf("\nSlice: %ld, slice size: %f, initial term: %f, final term: %f", slice, slice_size, initial_term, final_term);
	double n;
	long double partial = 0;
	for (n = initial_term; n < final_term; n++) {
		partial += (1/pow(16,n))*(4/(8*n + 1) - 2/(8*n + 4) - 1/(8*n + 5) - 1/(8*n + 6));
	}
	partials[slice] = partial;
	//printf("\nPartial of slice %ld: %.*Lf", slice, 50, partial);
	pthread_exit(NULL);
}

void* method_2(void* void_slice) { // #15 series from David H. Bailey reference article
	long slice;
	slice = (long)void_slice;
	double initial_term = slice * slice_size;
	double final_term = ((slice + 1) * slice_size) - 1;
	//printf("\nSlice: %ld, slice size: %f, initial term: %f, final term: %f", slice, slice_size, initial_term, final_term);
	double n;
	long double partial = 0;
	for (n = initial_term; n < final_term; n++) {
		partial += (pow((-1),n)/pow(4,n))*(2/(4*n + 1) + 2/(4*n + 2) + 1/(4*n + 3));
	}
	partials[slice] = partial;
	//printf("\nPartial of slice %ld: %.*Lf", slice, 50, partial);
	pthread_exit(NULL);
}
