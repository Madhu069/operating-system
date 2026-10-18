#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int request[50];
    int visited[50] = {0};

    int n, current;
    int totalMovement = 0;

    printf("Enter the current position: ");
    scanf("%d", &current);

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the request order:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("\nSSTF Disk Scheduling Order:\n");

    for (int i = 0; i < n; i++) {

        int minDistance = INT_MAX;
        int index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j]) {

                int distance = abs(current - request[j]);

                if (distance < minDistance) {
                    minDistance = distance;
                    index = j;
                }
            }
        }

        visited[index] = 1;

        totalMovement += abs(current - request[index]);

        current = request[index];

        printf("%d -> ", current);
    }

    printf("\n\nTotal Head Movement = %d\n", totalMovement);

    printf("Average Head Movement = %.2f\n",
           (float)totalMovement / n);

    return 0;
}