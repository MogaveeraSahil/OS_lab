#include <stdio.h>
#include <stdlib.h>

#define MAX_TSKS 10

typedef struct {
    int p;
    int c;
    int d;
    int rt;
    int nd;
    int id;
} Task;

void Input(Task tsks[], int *n_tsk) {
    printf("Enter number of tasks (max %d): ", MAX_TSKS);
    scanf("%d", n_tsk);

    if (*n_tsk > MAX_TSKS) {
        printf("Number of tasks exceeds the maximum limit of %d.\n", MAX_TSKS);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *n_tsk; i++) {
        tsks[i].id = i + 1;
        printf("Enter period (p) of task %d: ", i + 1);
        scanf("%d", &tsks[i].p);
        printf("Enter execution time (c) of task %d: ", i + 1);
        scanf("%d", &tsks[i].c);
        printf("Enter deadline (d) of task %d: ", i + 1);
        scanf("%d", &tsks[i].d);

        tsks[i].rt = tsks[i].c;
        tsks[i].nd = tsks[i].d;
    }
}

void EDF(Task tsks[], int n_tsk, int tf) {
    printf("\nEarliest-Deadline First Scheduling:\n");
    for (int t = 0; t < tf; t++) {
        int s_tsk = -1;

        for (int i = 0; i < n_tsk; i++) {
            if (t % tsks[i].p == 0) {
                tsks[i].rt = tsks[i].c;
                tsks[i].nd = t + tsks[i].d;
            }
        }

        for (int i = 0; i < n_tsk; i++) {
            if (tsks[i].rt > 0 && (s_tsk == -1 || tsks[i].nd < tsks[s_tsk].nd)) {
                s_tsk = i;
            }
        }

        if (s_tsk != -1) {
            printf("Time %d: Task %d\n", t, tsks[s_tsk].id);
            tsks[s_tsk].rt--;
        } else {
            printf("Time %d: Idle\n", t);
        }
    }
}

int main() {
    Task tsks[MAX_TSKS];
    int n_tsk;
    int tf;

    Input(tsks, &n_tsk);

    printf("Enter time frame for simulation: ");
    scanf("%d", &tf);

    EDF(tsks, n_tsk, tf);

    return 0;
}