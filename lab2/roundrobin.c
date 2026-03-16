#include <stdio.h>

struct Process {
    int id, at, bt, rt, ct, tat, wt;
    int inQueue; // Flag to check if process is already in ready queue
};

void sortByArrival(struct Process p[], int n) {
    struct Process temp;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(p[j].at > p[j+1].at) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main() {
    int n, tq, time = 0, completed = 0;
    int queue[100], front = 0, rear = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].id);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].inQueue = 0;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    sortByArrival(p, n);

    // Initial check: find processes arriving at time 0 or the earliest time
    time = p[0].at;
    for(int i = 0; i < n; i++) {
        if(p[i].at <= time) {
            queue[rear++] = i;
            p[i].inQueue = 1;
        }
    }

    printf("\nGantt Chart Execution Sequence: ");

    while(completed < n) {
        if(front == rear) { // If queue is empty, jump to next arrival
            time++;
            for(int i = 0; i < n; i++) {
                if(p[i].at <= time && !p[i].inQueue && p[i].rt > 0) {
                    queue[rear++] = i;
                    p[i].inQueue = 1;
                }
            }
            continue;
        }

        int i = queue[front++];
        printf("P%d ", p[i].id);

        if(p[i].rt <= tq) {
            time += p[i].rt;
            p[i].rt = 0;
            p[i].ct = time;
            completed++;
        } else {
            time += tq;
            p[i].rt -= tq;
        }

        // 1. Add processes that arrived while the current process was running
        for(int j = 0; j < n; j++) {
            if(p[j].at <= time && p[j].rt > 0 && !p[j].inQueue) {
                queue[rear++] = j;
                p[j].inQueue = 1;
            }
        }

        // 2. Add the preempted process back to the end of the queue
        if(p[i].rt > 0) {
            queue[rear++] = i;
        } else {
            p[i].inQueue = 0; // Finished
        }
    }

    printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    float avgTAT = 0, avgWT = 0;
    for(int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        avgTAT += p[i].tat;
        avgWT += p[i].wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", avgTAT/n);
    printf("\nAverage Waiting Time: %.2f\n", avgWT/n);

    return 0;
}
