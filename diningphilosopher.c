#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t chopstick[N];
sem_t room;

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    printf("Philosopher %d is thinking.\n", id + 1);
    sleep(1);

    sem_wait(&room);

    sem_wait(&chopstick[id]);
    printf("Philosopher %d picked up the left chopstick.\n", id + 1);

    sem_wait(&chopstick[(id + 1) % N]);
    printf("Philosopher %d picked up the right chopstick.\n", id + 1);

    printf("Philosopher %d is eating.\n", id + 1);
    sleep(2);

    sem_post(&chopstick[(id + 1) % N]);
    printf("Philosopher %d put down the right chopstick.\n", id + 1);

    sem_post(&chopstick[id]);
    printf("Philosopher %d put down the left chopstick.\n", id + 1);

    sem_post(&room);

    printf("Philosopher %d finished eating and is thinking again.\n", id + 1);

    return NULL;
}

int main()
{
    pthread_t philosopherThreads[N];
    int id[N];

    for (int i = 0; i < N; i++)
    {
        sem_init(&chopstick[i], 0, 1);
    }

    sem_init(&room, 0, N - 1);

    for (int i = 0; i < N; i++)
    {
        id[i] = i;

        if (pthread_create(
                &philosopherThreads[i],
                NULL,
                philosopher,
                &id[i]) != 0)
        {
            printf("Error creating philosopher thread.\n");
            exit(1);
        }
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(philosopherThreads[i], NULL);
    }

    for (int i = 0; i < N; i++)
    {
        sem_destroy(&chopstick[i]);
    }

    sem_destroy(&room);

    printf("All philosophers have finished their activities.\n");

    return 0;
}