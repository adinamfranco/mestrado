/*
    Autor: Prof. Andrei Rimsa Alves, DECOM/CEFET-MG
    http://rimsa.com.br/page/classes/decom009/
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int g = 10;

void* inc_by3(void *arg) {
    g += 3;
    return 0;
}

void mul_by2(){
    g *= 2;
}

int main(int argc, char* argv[]) {
    pthread_t tid;

    pthread_create(&tid, NULL, inc_by3, NULL);

    mul_by2();
    pthread_join(tid, NULL);
    printf("%d\n", g);
    return 0;
}




