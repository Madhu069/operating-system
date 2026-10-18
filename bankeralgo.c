#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m;
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int maximum[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int safeSequence[MAX_PROCESSES];

    int i, j, count = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the available instances of each resource:\n");

    for (i = 0; i < m; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &available[i]);
    }

    printf("\nEnter the maximum demand for each process:\n");

    for (i = 0; i < n; i++) {
        printf("Process %d:\n", i);

        for (j = 0; j < m; j++) {
            printf("Resource %d: ", j);
            scanf("%d", &maximum[i][j]);
        }
    }

    printf("\nEnter the allocation for each process:\n");

    for (i = 0; i < n; i++) {
        printf("Process %d:\n", i);

        for (j = 0; j < m; j++) {
            printf("Resource %d: ", j);
            scanf("%d", &allocation[i][j]);

            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    while (count < n) {
        int found = 0;

        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int canExecute = 1;

                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        canExecute = 0;
                        break;
                    }
                }

                if (canExecute) {
                    for (j = 0; j < m; j++) {
                        available[j] += allocation[i][j];
                    }

                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("\nSystem is not in a safe state.\n");
            return 0;
        }
    }

    printf("\nSystem is in a safe state.\n");
    printf("Safe sequence: ");

    for (i = 0; i < n; i++) {
        printf("P%d", safeSequence[i]);

        if (i != n - 1)
            printf(" -> ");
    }

    printf("\n");

    return 0;
}