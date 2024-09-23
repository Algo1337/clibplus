#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "thread.h"

Thread *new_thread(void *fn, void **args, void **ret_var) {
    Thread *t = (Thread *)malloc(sizeof(Thread));
    *t = (Thread){
        .id         = (rand() % (1000000 - 0 + 1)) + 1000000,
        .Execute    = ExecuteMethod,
        .Exit       = ExitThread,
        .running    = 0,
        .return_var = ret_var,
        .fn         = fn,
        .args       = args
    };

    return t;
}

void ExecuteMethod(Thread *t) {
    t->running = 1;
    pthread_create(&t->ptid, NULL, (void *)t->fn, (void *)t->args);
}

void WaitThread(Thread *t) {
    t->running = 0;
    (void)(t->return_var == NULL ? pthread_join(t->ptid, NULL) : pthread_join(t->ptid, t->return_var));
}

void ExitThread(Thread *t) {
    t->running = 0;
    pthread_cancel(t->ptid);
}
