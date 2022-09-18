#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define M 3
#define K 2
#define N 3
#define NUM_THREADS 10

int A [M][K] = { {2,6}, {1,3}, {6,3} };
int B [K][N] = { {7,8,3}, {9,4,6} };
int C [M][N];

struct v {
   int i; /* linha */
   int j; /* coluna */
};

void *runner(void *param); /* trhead */

int main(int argc, char *argv[]) {

   int i,j, count = 0;
   for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         //definindo cada linha e coluna para cada thread
         struct v *data = (struct v *) malloc(sizeof(struct v));
         data->i = i;
         data->j = j;
         pthread_t tid;       //Thread ID
         pthread_attr_t attr; //Define atributo do pthread
         pthread_attr_init(&attr);
         //Criando a trhead
         pthread_create(&tid,&attr,runner,data);
         pthread_join(tid, NULL);
         count++;
      }
   }

   //Matriz multiplicada
   for(i = 0; i < M; i++) {
      for(j = 0; j < N; j++) {
         printf("%d ", C[i][j]);
      }
      printf("\n");
   }
}


void *runner(void *param) {
   struct v *data = param; 
   int n, sum = 0; 

   //i * j
   for(n = 0; n< K; n++){
      sum += A[data->i][n] * B[n][data->j];
   }
   //soma de i por j
   C[data->i][data->j] = sum;

   //finalizando a thread
   pthread_exit(0);
}