#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define size 512
#define N_THREADS 4
double A[size][size];
double B[size][size];
double C[size][size];
int n;
pthread_t threads[N_THREADS];

typedef struct
{
	int i, j;
} thread_arg, *ptr_thread_arg;


void init() 
{
	srand(time(NULL));
    for(int i = 0; i < size; i++) 
	{
        for(int j = 0; j < size; j++) 
		{
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
			C[i][j] = 0;
        }
    }
}

void *calc_ij_matrix(void *arg)
{
    ptr_thread_arg arg_thread = (ptr_thread_arg)arg;
    double cij = *C[arg_thread->i+arg_thread->j*n];
    for(int k = 0; k < n; k++) 
	{
        cij += *A[arg_thread->i+k*n] * *B[k+arg_thread->j*n];
    }
    *C[arg_thread->i+arg_thread->j*n] = cij;
}

void dgemm2t()
{
   thread_arg arguments[N_THREADS];
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; j+=N_THREADS) {
            for(int t=0; t<N_THREADS; t++) {
                arguments[t].i = i;
                arguments[t].j = j+t;
                pthread_create(&(threads[t]), NULL, calc_ij_matrix, &(arguments[t]));
            }
        }
    }
}

void print()
{
	for(int i = 0; i < size; i++) 
	{
		for(int j = 0; j < size; j++) 
		{
			printf("%g ", C[i][j]);
		}
		printf("\n");
	}
}

int main(void)
{
init();

clock_t t;
t = clock();
dgemm2t(512, *A, *B, *C);
t = clock() - t;
double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
printf("dgemm took %f seconds to execute \n", time_taken);

return 0;
}