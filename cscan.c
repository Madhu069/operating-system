#include <stdio.h>
#include <stdlib.h>

int main()
{
    int headPosition, n, i, j;
    int maxRange = 199;
    int difference, temp;
    int temp1 = 0, temp2 = 0;
    int seek = 0;

    printf("Enter the number of queue requests: ");
    scanf("%d", &n);

    int queue[n + 2];
    int queue1[n];
    int queue2[n];

    printf("Enter the head position: ");
    scanf("%d", &headPosition);

    printf("Enter the disk positions to be read from queue:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &temp);

        if (temp > headPosition)
        {
            queue1[temp1] = temp;
            temp1++;
        }
        else
        {
            queue2[temp2] = temp;
            temp2++;
        }
    }

    // Sort queue1 in ascending order
    for (i = 0; i < temp1 - 1; i++)
    {
        for (j = i + 1; j < temp1; j++)
        {
            if (queue1[i] > queue1[j])
            {
                temp = queue1[i];
                queue1[i] = queue1[j];
                queue1[j] = temp;
            }
        }
    }

    // Sort queue2 in ascending order
    for (i = 0; i < temp2 - 1; i++)
    {
        for (j = i + 1; j < temp2; j++)
        {
            if (queue2[i] > queue2[j])
            {
                temp = queue2[i];
                queue2[i] = queue2[j];
                queue2[j] = temp;
            }
        }
    }

    // First service requests greater than head position
    for (i = 0; i < temp1; i++)
    {
        queue[i] = queue1[i];
    }

    // Move to the end of disk
    queue[temp1] = maxRange;

    // Circular movement to beginning
    queue[temp1 + 1] = 0;

    // Then service remaining requests
    for (i = temp1 + 2, j = 0; j < temp2; i++, j++)
    {
        queue[i] = queue2[j];
    }

    printf("\nC-SCAN Disk Scheduling Order:\n");

    printf("%d", headPosition);

    // Calculate seek time
    for (i = 0; i < n + 2; i++)
    {
        difference = abs(queue[i] - headPosition);
        seek = seek + difference;
        headPosition = queue[i];

        printf(" -> %d", queue[i]);
    }

    printf("\n\nTotal Seek Time: %d", seek);

    float averageSeekTime = (float)seek / n;

    printf("\nAverage Seek Time: %.2f\n", averageSeekTime);

    return 0;
}