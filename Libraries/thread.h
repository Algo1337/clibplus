#pragma once

typedef struct Thread {
    long        id;
    pthread_t   ptid;
    void        **args;
    int         running;
    void        **return_var;
    void        (*Execute)      (struct Thread *t);
    void        (*Wait)         (struct Thread *t);
    void        (*Exit)         (struct Thread *t);
    void        (*fn)           (void **args);
} Thread;

Thread *new_thread(void *fn, void **args, void **ret_var);
void ExecuteMethod(Thread *t);
void WaitThread(Thread *t);
void ExitThread(Thread *t);