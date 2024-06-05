#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct {
    int T; // Period
    int C; // Execution time
    int D; // Deadline
    int R; // Remaining time
    int id; // Task identifier
} Task;

void input(Task tasks[], int *n) {
    printf("Enter number of tasks: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        tasks[i].id = i + 1;
        printf("Enter period (T) of task %d: ", i + 1);
        scanf("%d", &tasks[i].T);
        printf("Enter execution time (C) of task %d: ", i + 1);
        scanf("%d", &tasks[i].C);
        tasks[i].D = tasks[i].T;
        tasks[i].R = tasks[i].C;
    }
}

int compare_by_period(const void *a, const void *b) {
    return ((Task*)a)->T - ((Task*)b)->T;
}                                                                                                                                                                              

void rms(Task tasks[], int n, int tf) {
    qsort(tasks, n, sizeof(Task), compare_by_period);

    printf("\nRate-Monotonic Scheduling:\n");
    for (int t = 0; t < tf; t++) {
        int st = -1;
        for (int i = 0; i < n; i++) {
            if (t % tasks[i].T == 0) {
                tasks[i].R = tasks[i].C;
            }
            if (tasks[i].R > 0 && (st == -1 || tasks[i].T < tasks[st].T)) {
                st = i;
            }
        }

        if (st != -1) {
            printf("Time %d: Task %d\n", t, tasks[st].id);
            tasks[st].R--;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }
}

int main() {
    Task tasks[MAX_TASKS];
    int n, tf;

    input(tasks, &n);

    printf("Enter time frame for simulation: ");
    scanf("%d", &tf);

    rms(tasks, n, tf);

    return 0;
}