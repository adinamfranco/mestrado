#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define size 2048

double A[size][size];
double B[size][size];
double C[size][size];
int i;
int j;
int n;
int k;

void init() 
{
	srand(time(NULL));
    for(i = 0; i < size; i++) 
	{
        for(j = 0; j < size; j++) 
		{
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
			C[i][j] = 0;
        }
    }
}

void dgemm(int n, double *A, double *B, double *C)
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

void print()
{
	for(i = 0; i < size; i++) 
	{
		for(j = 0; j < size; j++) 
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
dgemm(2048, *A, *B, *C);
t = clock() - t;
double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
printf("dgemm took %f seconds to execute \n", time_taken);

return 0;
}