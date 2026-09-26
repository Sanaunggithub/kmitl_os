#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define ITEMS 40

int buffer[BUFFER_SIZE];
int in = 0, out = 0, count = 0;
sem_t empty, full, mutex;

void status(void) {
    if (count == BUFFER_SIZE) printf("Buffer Full\n");
    else if (count == 0)      printf("Buffer Empty\n");
    else                      printf("Buffer size = %d\n", count);
}

void *insertbuffer(void *arg) {
    for (int i = 0; i < ITEMS; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = i;
        in = (in + 1) % BUFFER_SIZE;
        count++;
        printf("Producer Entered %d ", i);
        status();

        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *readbuffer(void *arg) {
    for (int i = 0; i < ITEMS; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;
        printf("Consumer consumed %d ", item);
        status();

        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main(void) {
    pthread_t producer, consumer;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&producer, NULL, insertbuffer, NULL);
    pthread_create(&consumer, NULL, readbuffer, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}