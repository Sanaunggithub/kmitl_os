#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int count = 5; // shared variable
sem_t mutex;
void *increment(void *param);
void *decrement(void *param);
int main()
{
    pthread_t tid1, tid2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    sem_init(&mutex, 0, 1); // 0- this semaphore will be shared among threads created by this process only.  1 - initial value for mutex
    pthread_create(&tid1, &attr, increment, NULL);
    pthread_create(&tid2, &attr, decrement, NULL);
    /* now wait for the thread to exit */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("count  = %d\n", count);
    sem_destroy(&mutex);
}

void *increment(void *param)
{
    int temp; // register 1
    // sem_wait(&mutex);
    temp = count;
    sleep(rand() % 5);
    temp++;
    count = temp;
    // sem_post(&mutex); // sem_post is signal
    pthread_exit(0);
}

void *decrement(void *param)
{
    int temp;
    // sem_wait(&mutex);
    temp = count;
    sleep(rand() % 5);
    temp--;
    count = temp;
    // sem_post(&mutex);
    pthread_exit(0);
}