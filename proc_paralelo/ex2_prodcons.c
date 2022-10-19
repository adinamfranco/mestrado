/*
    Autor: Prof. Andrei Rimsa Alves, DECOM/CEFET-MG
    http://rimsa.com.br/page/classes/decom009/
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


#define N 100

int buffer[N];
int i = 0;
int f = 0;
int c = 0;

int produz() {
    static int x = 0;

    return x++;
}

void consome(int x) {
    printf("%d\n", x);

}

void* produtor(void* arg){
    while(1) {
        while (c == N);

        buffer[f] = produz();
        f = (f + 1) % N;
        c++;
    }
}

void* consumidor(void* arg){
    while (1){
        while(c == 0);
    
        consome(buffer[i]);
        i = (i + 1) % N;
        c--;
    }
}

int main(int argc, char* argv[]) {
    pthread_t tid1;
    pthread_t tid2;

    pthread_create(&tid1, NULL, produtor, NULL);
    pthread_create(&tid2, NULL, consumidor, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}




