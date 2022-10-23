#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

#define size 8
#define N_THREADS 2
double A[size * size];
double B[size * size];
double C[size * size];
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
            A[i + j * size] = rand() % 10;
            B[i + j * size] = rand() % 10;
        }
    }
}

void *calc_ij_matrix(void *arg)
{
    ptr_thread_arg arg_thread = (ptr_thread_arg)arg;
    double cij = C[arg_thread->i + arg_thread->j * size];
    for(int k = 0; k < size; k++) 
	{
        cij += A[arg_thread->i+k*size] * B[k+arg_thread->j*size];
    }
    C[arg_thread->i+arg_thread->j*size] = cij;
}

void dgemm2t()
{
   thread_arg arguments[N_THREADS];
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; j+=N_THREADS) {
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
			printf("%g ", C[i + j]);
		}
		printf("\n");
	}
}

int main(void)
{
init();

clock_t t;
t = clock();
dgemm2t();
t = clock() - t;
double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
printf("dgemm took %f seconds to execute \n", time_taken);
print();
return 0;
}