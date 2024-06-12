#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n, sOT = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int pid[n];
    int l[n + 1];
    l[0] = 0;

    printf("\nEnter the number of tickets for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("PID%d: ", i + 1);
        scanf("%d", &pid[i]);
        sOT += pid[i];
        l[i + 1] = pid[i];
    }

    int t = 1;
    int sum = sOT;
    for (int i = 0; i < n; i++) {
        printf("Probability of servicing process %d is %d%%\n", i + 1, (pid[i] * 100) / sOT);
    }

    srand(time(NULL));
    while (sum > 0) {
        int x = rand() % sOT;
        int j;
        for (j = 0; j < n; j++) {
            if (x < l[j + 1]) {
                printf("%d ms: Servicing Ticket of process %d\n", t, j + 1);
                //l[j + 1]--;
                pid[j]--;
                sum--;
                t++;
                break;
            }
        }
        // No process found
    }

    for (int i = 0; i < n; i++) {
        if (pid[i] == 0) {
            printf("PID%d has finished executing\n", i + 1);
        }
    }
    return 0;
}
