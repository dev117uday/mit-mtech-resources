#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty, full, mutex;

void *produce(void *param)
{
    int item = 1;
    while (1)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        printf("Item produced : %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        item++;
        sem_post(&mutex);
        sem_post(&full);
        usleep(100000);
    }
}

void *consumer(void *param)
{
    while (1)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        int value;
        sem_getvalue(&empty, &value);
        if (value > 10)
        {
            printf("producer ahead of consumer\n");
        }
        int item = buffer[out];
        printf("Item consumed : %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&mutex);
        sem_post(&empty);
        usleep(150000);
    }
}

int main()
{

    pthread_t prod_thread, cons_thread;
    /*
        2nd arg: 0 -> semaphore local to thread
        2nd arg: 1 -> semaphore shared to threads
    */
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&prod_thread, NULL, produce, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
}