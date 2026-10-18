
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int headPosition, n, i, j;
    int seek = 0;
    int temp, difference;
    int temp1 = 0, temp2 = 0;
    printf("Enter the number of queue requests: ");
    scanf("%d", &n);
    int queue[n + 1];
    int queue1[n];
    int queue2[n];
    printf("Enter the head position: ");
    scanf("%d", &headPosition);
    printf("Enter the disk positions to be read (queue):\n");
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
    // Copy requests greater than head position
    for (i = 0, j = 0; j < temp1; i++, j++)
    {
        queue[i] = queue1[j];
    }
    // C-LOOK jumps directly to the smallest request
    // without going to the end of the disk
    for (j = 0; j < temp2; i++, j++)
    {
        queue[i] = queue2[j];
    }
    printf("\nC-LOOK Disk Scheduling Order:\n");
    printf("%d", headPosition);
    // Calculate total seek time
    for (j = 0; j < n; j++)
    {
        difference = abs(queue[j] - headPosition);
        seek = seek + difference;
        headPosition = queue[j];
        printf(" -> %d", 
    }
    float averageSeekTime = (float)seek / n;
    printf("\n\nTotal Seek Time = %d", seek);
    printf("\nAverage Seek Time = \n", averageSeekTime);
    return 0;
}