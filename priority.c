#include <stdio.h>

typedef struct
{
    int pid;
    int burst;
    int priority;
} process;

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    process p[n];

    // Input burst time and priority
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("Enter burst time for P%d: ", p[i].pid);
        scanf("%d", &p[i].burst);

        printf("Enter priority for P%d: ", p[i].pid);
        scanf("%d", &p[i].priority);
    }

    // Sort processes according to priority
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].priority > p[j + 1].priority)
            {
                process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int waiting[n];
    int turnaround[n];

    waiting[0] = 0;

    for (int i = 1; i < n; i++)
    {
        waiting[i] = waiting[i - 1] + p[i - 1].burst;
    }

    for (int i = 0; i < n; i++)
    {
        turnaround[i] = waiting[i] + p[i].burst;
    }

    float totalWaiting = 0;
    float totalTurnaround = 0;

    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++)
    {
        totalWaiting += waiting[i];
        totalTurnaround += turnaround[i];

        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n",
               p[i].pid,
               p[i].burst,
               p[i].priority,
               waiting[i],
               turnaround[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n",
           totalWaiting / n);

    printf("Average Turnaround Time = %.2f\n",
           totalTurnaround / n);

    return 0;
}