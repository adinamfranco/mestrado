#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>



#ifndef SIZE
#define SIZE 128
#endif

struct thread_args{
	int start;
	int end;
};

void* dgemm(const int n,
	  double *A, double *B, double *C)
{
    for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
	    	double cij = C[i + j * n];	/* cij = C[i][j] */
	    	for (int k = 0; k < n; ++k) {
				cij += A[i + k * n] * B[k + j * n];	/* cij+=A[i][k]*B[k][j] */
	    	}
	    	C[i + j * n] = cij;	/* C[i][j] = cij */
		}
	}
}

int main()
{
const int N = SIZE;
	double *A = NULL, *B = NULL, *C = NULL;
	A = calloc(N*N, sizeof(double));
	B = calloc(N*N, sizeof(double));
	C = calloc(N*N, sizeof(double));
	assert(A!=NULL && B!=NULL && C!=NULL);
	for (int i=0; i<N*N; ++i) {
			A[i] = (double)rand()/RAND_MAX;
			B[i] = (double)rand()/RAND_MAX;
			
	}
pthread_t tid[NUM_THREADS];
struct thread_args work_ranges[NUM_THREADS];
int current_start, range;
current_start = 0;
range = SIZE / NUM_THREADS;
for(int i = 0; i < NUM_THREADS; i++) {
	work_ranges[i].start = current_start;
	work_ranges[i].end = current_start + range;
	current_start += range;
}
work_ranges[NUM_THREADS-1].end = 2;
init();
for(int i = 0; i < NUM_THREADS; i++) {
	pthread_create(&tid[i], NULL, multiply, &work_ranges[i]);
}
for(int i = 0; i < NUM_THREADS; i++) {
	pthread_join(tid[i], NULL);
}
t = clock();
pthread_create(&tid1, NULL, dgemm, NULL);
t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
    printf("dgemm took %f seconds to execute \n", time_taken);
	pthread_join(tid1, NULL);
    return 0;
pthread_exit(0);
}	
