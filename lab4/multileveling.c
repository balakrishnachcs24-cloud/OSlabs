#include <stdio.h>

int main()
{
    int n, i, j;

    int pid[20], at[20], bt[20], type[20];
    int ct[20], tat[20], wt[20], start[20];

    int sys[20], user[20];
    int sysCount = 0, userCount = 0;

    int time = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for(i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i + 1);

        printf("PID: ");
        scanf("%d", &pid[i]);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Type (0 = System, 1 = User): ");
        scanf("%d", &type[i]);
    }

    // Step 1: Separate into queues
    for(i = 0; i < n; i++)
    {
        if(type[i] == 0)
            sys[sysCount++] = i;
        else
            user[userCount++] = i;
    }

    // Step 2: Sort System Queue by Arrival Time
    for(i = 0; i < sysCount - 1; i++)
    {
        for(j = i + 1; j < sysCount; j++)
        {
            if(at[sys[i]] > at[sys[j]])
            {
                int temp = sys[i];
                sys[i] = sys[j];
                sys[j] = temp;
            }
        }
    }

    // Sort User Queue by Arrival Time
    for(i = 0; i < userCount - 1; i++)
    {
        for(j = i + 1; j < userCount; j++)
        {
            if(at[user[i]] > at[user[j]])
            {
                int temp = user[i];
                user[i] = user[j];
                user[j] = temp;
            }
        }
    }

    // Step 3: Execute System Queue (FCFS)
    for(i = 0; i < sysCount; i++)
    {
        int p = sys[i];

        if(time < at[p])
            time = at[p];

        start[p] = time;
        time += bt[p];
        ct[p] = time;

        tat[p] = ct[p] - at[p];
        wt[p] = tat[p] - bt[p];
    }

    // Step 4: Execute User Queue (after system)
    for(i = 0; i < userCount; i++)
    {
        int p = user[i];

        if(time < at[p])
            time = at[p];

        start[p] = time;
        time += bt[p];
        ct[p] = time;

        tat[p] = ct[p] - at[p];
        wt[p] = tat[p] - bt[p];
    }

    // Step 5: Display Results
    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");

    for(i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], type[i],
               ct[i], tat[i], wt[i]);
    }

    return 0;
}
