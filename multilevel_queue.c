#include <stdio.h>
#include <limits.h>

struct Proc {
    int id;   // Process ID
    int bt;   // Burst time
    int at;   // Arrival time
    int qt;   // Queue type (1 for system, 2 for user)
    int wt;   // Waiting time
    int tat;  // Turnaround time
    int rt;   // Response time
    int st;   // Start time
    int et;   // End time
    int vis;  // Visited flag
};

void main() {
    int n, currTime = 0;
    float avgWT = 0, avgTAT = 0, avgRT = 0, tp;

    printf("Queue 1 is system process\nQueue 2 is User Process\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Proc procs[n], tmp;

    for (int i = 0; i < n; i++) {
        procs[i].id = i + 1;
        procs[i].vis = 0;
        printf("Enter Burst Time, Arrival Time and Queue of P%d: ", i + 1);
        scanf("%d %d %d", &procs[i].bt, &procs[i].at, &procs[i].qt);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (procs[i].at > procs[j].at ||
                (procs[i].at == procs[j].at && procs[i].qt > procs[j].qt)) {
                tmp = procs[i];
                procs[i] = procs[j];
                procs[j] = tmp;
            }
        }
    }

    int compTime = procs[0].bt, minQT = INT_MAX, minQI, procCount = 0;
    procs[0].vis = 1;

    while (procCount < n - 1) {
        for (int i = 0; i < n; i++) {
            if (procs[i].at <= compTime && procs[i].vis == 0) {
                if (procs[i].qt < minQT) {
                    minQT = procs[i].qt;
                    minQI = i;
                }
            }
        }

        procs[minQI].vis = 1;
        compTime += procs[minQI].bt;
        minQT = INT_MAX;

        tmp = procs[procCount + 1];
        procs[procCount + 1] = procs[minQI];
        procs[minQI] = tmp;

        procCount++;
    }

    printf("\nProcess\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        if (procs[i].at < currTime) {
            procs[i].st = currTime;
        } else {
            procs[i].st = procs[i].at;
        }
        procs[i].et = procs[i].st + procs[i].bt;
        currTime += procs[i].bt;

        procs[i].tat = procs[i].et - procs[i].at;
        procs[i].wt = procs[i].tat - procs[i].bt;
        procs[i].rt = procs[i].st - procs[i].at;

        printf("%d\t%d\t%d\t%d\n", procs[i].id, procs[i].wt, procs[i].tat, procs[i].rt);

        avgWT += procs[i].wt;
        avgTAT += procs[i].tat;
        avgRT += procs[i].rt;
    }

    tp = (float)procs[n - 1].et / n;
    printf("Average WT: %.2f\n", avgWT / n);
    printf("Average TAT: %.2f\n", avgTAT / n);
    printf("Average RT: %.2f\n", avgRT / n);
    printf("Throughput: %.2f", tp);
}