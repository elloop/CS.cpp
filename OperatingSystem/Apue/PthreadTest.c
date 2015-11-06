#include "include/apue.h"
#include <pthread.h>

static pthread_t tid1;

void* tfunc1(void* arg) {
    printf("pid:\t%lx\ttid:\t%lx\treturning\n", getpid(), pthread_self());
    return ((void*)0);
}

void testPthread(void) {
    int err;
    if ((err = pthread_create(&tid1, NULL, tfunc1, NULL)) != 0) {
        err_quit("fail to create thread");
    }
    sleep(2);
    printf("pid:\t%lx\ttid:\t%lx\tmain thread return\n", getpid(), pthread_self());
}

