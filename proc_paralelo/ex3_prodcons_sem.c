/*
    Autor: Prof. Andrei Rimsa Alves, DECOM/CEFET-MG
    http://rimsa.com.br/page/classes/decom009/
*/


#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>


#define N 100

int buffer[N];
int i = 0;
int f = 0;
int c = 0;

sem_t mutex;

int get_c(){
    int tmp;
    sem_wait(&mutex);
    tmp = c;
    sem_post(&mutex);

    return c;
}


void inc_c(){
    sem_wait(&mutex);
    c++;
    sem_post(&mutex);
}

void dec_c(){
    sem_wait(&mutex);
    c--;
    sem_post(&mutex);
}

int produz() {
    static int x = 0;

    return x++;
}

void consome(int x) {
    printf("%d\n", x);

}

void* produtor(void* arg){
    while(1) {
        while (get_c() == N);

        buffer[f] = produz();
        f = (f + 1) % N;
        inc_c();
    }
}

void* consumidor(void* arg){
    while (1){
        while(get_c() == 0);
    
        consome(buffer[i]);
        i = (i + 1) % N;
        dec_c();
    }
}

int main(int argc, char* argv[]) {
    pthread_t tid1;
    pthread_t tid2;

    sem_init(&mutex, 0, 1);

    pthread_create(&tid1, NULL, produtor, NULL);
    pthread_create(&tid2, NULL, consumidor, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&mutex);    

    return 0;
}




