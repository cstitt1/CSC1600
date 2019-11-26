#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "voidQueue.h"

Queue* queue;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
/*These are the condition variables that the boss and  workers wait on */
pthread_cond_t boss_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t work_cond = PTHREAD_COND_INITIALIZER;

//function run by the worker threads
void* worker(void* arg)
{
    char* item;
    while(1) {
        //acquire the lock to check if queue is empty
        pthread_mutex_lock(&m);
        //if queue is empty release the lock and wait for a signal from the boss that
        //it is no longer empty
        while(isEmpty(queue)) {
            pthread_cond_wait(&work_cond, &m);
        }        
        //queue is not empty so dequeue
        item = dequeue(queue);
        //release the loc
        pthread_mutex_unlock(&m);
        //signal to boss that the queue is not full so if it's waiting wake up
        pthread_cond_signal(&boss_cond);
        printf("dequeued %s\n",item);
    }
}

int main(int argc, char const *argv[])
{
    pthread_t workerThread[10];
    queue = createQueue(5);

    //create a pool of threads
    int i;
    for(i=0;i<10;i++) {
        pthread_create(&workerThread[i],NULL,worker,NULL);
    }

    char* item = malloc(50*sizeof(char));
    strcpy(item,"workdetails");

    while(1) {
        //acquire lock to check if queue is full
        pthread_mutex_lock(&m);
        //if full wait for signal from worker when it's no longer full
        while(isFull(queue)) {
            pthread_cond_wait(&boss_cond,&m);
        }        
        //queue not full so enqueu
        enqueue(queue,item);
        //unlock mutex
        pthread_mutex_unlock(&m);
        //signal to worker that queue is not empty so if it's waiting wake up           
        pthread_cond_signal(&work_cond);
        printf("boss put %s in queue\n",item);
    }
    return 0;
}
