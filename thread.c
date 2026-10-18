#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *printNumbers(void *arg)
{
    int i;
    for(i=0;i<5;i++)
    {
        printf("Thread 1:%d\n",i);
        sleep(1);
    }
    pthread_exit(NULL);
}
void *printLetters(void *arg)
{
    int i;
    char letters[]={'A','B','C','D','E'};
    for(i=0;i<5;i++)
    {
        printf("Thread 2:%c\n",letters[i]);
        sleep(1);
    }
    pthread_exit(NULL);
}
int main()
{
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, printNumbers, NULL);
    pthread_create(&thread2, NULL, printLetters, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}