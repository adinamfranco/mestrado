#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define n 8
#define NUM_THREADS 2
double A[n * n];
double B[n * n];
double C[n * n];
pthread_t threads[NUM_THREADS];

typedef struct {
    int i, j;
} thread_arg, *ptr_thread_arg;

void *calc_ij_matrix(void *arg){
    ptr_thread_arg arg_thread = (ptr_thread_arg)arg;
    double cij = C[arg_thread->i+arg_thread->j*n];
    for(int k = 0; k < n; k++) {
        cij += A[arg_thread->i+k*n] * B[k+arg_thread->j*n];
    }
    C[arg_thread->i+arg_thread->j*n] = cij;
}

void dgemm(){
    thread_arg arguments[NUM_THREADS];
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; j+=NUM_THREADS) {
            for(int t=0; t<NUM_THREADS; t++) {
                arguments[t].i = i;
                arguments[t].j = j+t;
                pthread_create(&(threads[t]), NULL, calc_ij_matrix, &(arguments[t]));
            }
        }
    }
}

int main() {

    int i, j;

    for(i = 0; i < n; ++i) {
        for(j = 0; j < n; ++j) {
            A[i + j * n] = (double)rand()/(double)(RAND_MAX);
        }
    }

    for(i = 0; i < n; ++i) {
        for(j = 0; j < n; ++j) {
            B[i + j * n] = (double)rand() / (double)(RAND_MAX);
        }
    }

    dgemm();

    for(i = 0; i < n; ++i) {
        for(j = 0; j < n; ++j) {
            printf("%f ", A[i + j * n]);
        }
        printf("\n");
    }
    printf("\n");

    for(i = 0; i < n; ++i) {
        for(j = 0; j < n; ++j) {
            printf("%f ", B[i + j * n]);
        }
        printf("\n");
    }
    printf("\n");

    for(i = 0; i < n; ++i) {
        for(j = 0; j < n; ++j) {
            printf("%f ", C[i + j * n]);
        }
        printf("\n");
    }
    printf("\n");
}