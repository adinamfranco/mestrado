#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


#ifndef SIZE
#define SIZE 128
#endif

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
clock_t t;
t = clock();
dgemm(128, A, B, C);
t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
 
    printf("dgemm took %f seconds to execute \n", time_taken);
    return 0;
}	
