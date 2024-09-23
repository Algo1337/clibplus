#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <clib/thread.h>

void msg_exit(char *msg) { printf("%s\n", msg); exit(0); }

void Counter(void **args) {
    int MAX_COUNT = atoi((char *)args[0]);
    char *Thread_num = (char *)args[1];


    for(int i = 0; i < MAX_COUNT; i++) {
        printf("Thread: %s | Counter: %d\n", Thread_num, i);
        sleep(1);
    }
}

int main() {
    Thread *Threads[2];

    void *args[] = {"100", "1", NULL};
    Threads[0] = new_thread(Counter, (void **)args, NULL);
    printf("Created a new thread: %ld awaiting execution....\n", Threads[0]->id);
    Threads[0]->Execute(Threads[0]);

    void *args1[] = {"200", "2", NULL};
    Threads[1] = new_thread(Counter, (void **)args1, NULL);
    printf("Created a new thread: %ld awaiting execution....\n", Threads[1]->id);
    Threads[1]->Execute(Threads[1]);

    for(int i = 0; i < 15; i++) {
        if(i == 2)
            Threads[0]->Exit(Threads[0]);

        if(i == 7)
            Threads[1]->Exit(Threads[1]);

        if(Threads[0]->running == 0 && Threads[1]->running == 0)
            msg_exit("[ + ] All threads has exit...!");

        printf("[ MAIN PROCESS COUNTER: %d ] Waiting for threads....!\n", i);
        sleep(1);
    }

    return 0;
}