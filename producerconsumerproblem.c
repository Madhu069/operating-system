
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];

int in = 0;
int out = 0;

sem_t empty;
sem_t full;

pthread_mutex_t mutex;

// Producer function
void *producer(void *pnum)
{
    int item;
    int num = *(int *)pnum;

    while (1)
    {
        item = rand() % 100;

        // Wait for an empty space
        sem_wait(&empty);

        // Lock the buffer
        pthread_mutex_lock(&mutex);

        buffer[in] = item;

        printf("Producer %d: Inserted item %d at %d\n",
               num, item, in);

        in = (in + 1) % BUFFER_SIZE;

        // Unlock the buffer
        pthread_mutex_unlock(&mutex);

        // Increase full slots
        sem_post(&full);

        sleep(1);
    }

    return NULL;
}

// Consumer function
void *consumer(void *cnum)
{
    int item;
    int num = *(int *)cnum;

    while (1)
    {
        // Wait for an available item
        sem_wait(&full);

        // Lock the buffer
        pthread_mutex_lock(&mutex);

        item = buffer[out];

        printf("Consumer %d: Removed item %d from %d\n",
               num, item, out);

        out = (out + 1) % BUFFER_SIZE;

        // Unlock the buffer
        pthread_mutex_unlock(&mutex);

        // Increase empty slots
        sem_post(&empty);

        sleep(1);
    }

    return NULL;
}

int main()
{
    pthread_t pro[3], con[3];

    int producer_id[3] = {1, 2, 3};
    int consumer_id[3] = {1, 2, 3};

    int i;

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Initially all buffer spaces are empty
    sem_init(&empty, 0, BUFFER_SIZE);

    // Initially there are no full spaces
    sem_init(&full, 0, 0);

    // Create producer threads
    for (i = 0; i < 3; i++)
    {
        pthread_create(
            &pro[i],
            NULL,
            producer,
            &producer_id[i]
        );
    }

    // Create consumer threads
    for (i = 0; i < 3; i++)
    {
        pthread_create(
            &con[i],
            NULL,
            consumer,
            &consumer_id[i]
        );
    }

    // Join producer threads
    for (i = 0; i < 3; i++)
    {
        pthread_join(pro[i], NULL);
    }

    // Join consumer threads
    for (i = 0; i < 3; i++)
    {
        pthread_join(con[i], NULL);
    }

    // Destroy mutex and semaphores
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
