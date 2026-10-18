#include <stdio.h>
#include <stdlib.h>

int main() {
    int request[50];
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

    printf("\nDisk Scheduling Order:\n");

    for (int i = 0; i < n; i++) {
        printf("%d -> ", request[i]);

        totalMovement += abs(current - request[i]);

        current = request[i];
    }

    printf("\n\nTotal Head Movement = %d\n", totalMovement);

    printf("Average Head Movement = %.2f\n",
           (float)totalMovement / n);

    return 0;
}