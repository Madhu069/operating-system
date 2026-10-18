
#include <stdio.h>

typedef struct
{
    int pid;
    int burst;
} process;

void calculateWaitingTime(process p[], int n, int waiting[])
{
    waiting[0] = 0;

    for (int i = 1; i < n; i++)
    {
        waiting[i] = waiting[i - 1] + p[i - 1].burst;
    }
}

void calculateTurnaroundTime(process p[], int n, int waiting[], int turnaround[])
{
    for (int i = 0; i < n; i++)
    {
        turnaround[i] = waiting[i] + p[i].burst;
    }
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    process p[n];

    // Input burst time
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("\nEnter burst time for Process %d: ", p[i].pid);
        scanf("%d", &p[i].burst);
    }

    // Sort processes according to burst time
    // Shortest burst time = Highest priority
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].burst > p[j + 1].burst)
            {
                process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int waiting[n];
    int turnaround[n];

    calculateWaitingTime(p, n, waiting);
    calculateTurnaroundTime(p, n, waiting, turnaround);

    float totalWaiting = 0;
    float totalTurnaround = 0;

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++)
    {
        totalWaiting += waiting[i];
        totalTurnaround += turnaround[i];

        printf("P%d\t%d\t\t%d\t\t%d\n",
               p[i].pid,
               p[i].burst,
               waiting[i],
               turnaround[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n",
           totalWaiting / n);

    printf("Average Turnaround Time = %.2f\n",
           totalTurnaround / n);

    return 0;
}