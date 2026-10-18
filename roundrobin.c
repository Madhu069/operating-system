#include <stdio.h>

typedef struct
{
    int pid;
    int burst;
    int remaining;
    int waiting;
    int turnaround;
} process;

int main()
{
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    process p[n];

    // Input burst time
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;

        printf("Enter burst time for P%d: ", p[i].pid);
        scanf("%d", &p[i].burst);

        p[i].remaining = p[i].burst;
        p[i].waiting = 0;
        p[i].turnaround = 0;
    }

    // Input time quantum
    printf("\nEnter Time Quantum: ");
    scanf("%d", &quantum);

    int time = 0;
    int completed = 0;

    // Round Robin Scheduling
    while (completed < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (p[i].remaining > 0)
            {
                if (p[i].remaining > quantum)
                {
                    time = time + quantum;
                    p[i].remaining = p[i].remaining - quantum;
                }
                else
                {
                    time = time + p[i].remaining;
                    p[i].remaining = 0;

                    p[i].turnaround = time;
                    p[i].waiting = p[i].turnaround - p[i].burst;

                    completed++;
                }
            }
        }
    }

    float totalWaiting = 0;
    float totalTurnaround = 0;

    printf("\nPID\tBurst Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++)
    {
        totalWaiting = totalWaiting + p[i].waiting;
        totalTurnaround = totalTurnaround + p[i].turnaround;

        printf("P%d\t%d\t\t%d\t\t%d\n",
               p[i].pid,
               p[i].burst,
               p[i].waiting,
               p[i].turnaround);
    }

    printf("\nAverage Waiting Time = %.2f",
           totalWaiting / n);

    printf("\nAverage Turnaround Time = %.2f\n",
           totalTurnaround / n);

    return 0;
}