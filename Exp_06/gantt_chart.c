#include<stdio.h>

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    
    // Input arrays
    int pid[20], at[20], bt[20], pri[20];
    for(int i=0; i<n; i++) {
        pid[i] = i+1;
        printf("P%d Arrival: ", pid[i]);
        scanf("%d", &at[i]);
        printf("P%d Burst: ", pid[i]);
        scanf("%d", &bt[i]);
        printf("P%d Priority: ", pid[i]);
        scanf("%d", &pri[i]);
    }
    
    int choice;
    while(1) {
        printf("\n1.FCFS 2.SJF 3.Priority 4.RR 5.Exit\nChoice: ");
        scanf("%d", &choice);
        if(choice == 5) break;
        
        // Local variables for each algo
        int wt[20] = {0}, tat[20] = {0}, ct[20] = {0};
        float avg_wt = 0, avg_tat = 0;
        int time = 0;
        int order[20]; // Store execution order for Gantt
        int order_count = 0;
        
        if(choice == 1) { // ===== FCFS =====
            for(int i=0; i<n; i++) {
                if(time < at[i]) time = at[i];
                order[order_count++] = i;
                time += bt[i];
                ct[i] = time;
                tat[i] = ct[i] - at[i];
                wt[i] = tat[i] - bt[i];
                avg_wt += wt[i];
                avg_tat += tat[i];
            }
        }
        
        else if(choice == 2) { // ===== SJF =====
            int complete = 0;
            while(complete < n) {
                int shortest = 999, pos = -1;
                for(int i=0; i<n; i++) {
                    if(at[i] <= time && wt[i] == 0 && bt[i] < shortest) {
                        shortest = bt[i];
                        pos = i;
                    }
                }
                if(pos == -1) time++;
                else {
                    order[order_count++] = pos;
                    time += bt[pos];
                    ct[pos] = time;
                    tat[pos] = ct[pos] - at[pos];
                    wt[pos] = tat[pos] - bt[pos];
                    avg_wt += wt[pos];
                    avg_tat += tat[pos];
                    complete++;
                }
            }
        }
        
        else if(choice == 3) { // ===== PRIORITY =====
            int complete = 0;
            while(complete < n) {
                int highest = 999, pos = -1;
                for(int i=0; i<n; i++) {
                    if(at[i] <= time && wt[i] == 0 && pri[i] < highest) {
                        highest = pri[i];
                        pos = i;
                    }
                }
                if(pos == -1) time++;
                else {
                    order[order_count++] = pos;
                    time += bt[pos];
                    ct[pos] = time;
                    tat[pos] = ct[pos] - at[pos];
                    wt[pos] = tat[pos] - bt[pos];
                    avg_wt += wt[pos];
                    avg_tat += tat[pos];
                    complete++;
                }
            }
        }
        
        else if(choice == 4) { // ===== ROUND ROBIN =====
            int qt, remain = n;
            printf("Enter quantum: ");
            scanf("%d", &qt);
            int rt[20];
            for(int i=0; i<n; i++) rt[i] = bt[i];
            
            time = 0;
            while(remain > 0) {
                int flag = 0;
                for(int i=0; i<n; i++) {
                    if(rt[i] > 0 && at[i] <= time) {
                        flag = 1;
                        if(rt[i] <= qt) {
                            order[order_count++] = i;
                            time += rt[i];
                            ct[i] = time;
                            tat[i] = ct[i] - at[i];
                            wt[i] = tat[i] - bt[i];
                            avg_wt += wt[i];
                            avg_tat += tat[i];
                            rt[i] = 0;
                            remain--;
                        } else {
                            order[order_count++] = i;
                            time += qt;
                            rt[i] -= qt;
                        }
                        break;
                    }
                }
                if(!flag) time++;
            }
        }
        
        // ===== PRINT TABLE =====
        avg_wt /= n;
        avg_tat /= n;
        
        printf("\nPID\tAT\tBT\tCT\tWT\tTAT\n");
        for(int i=0; i<n; i++) {
            printf("P%d\t%d\t%d\t%d\t%d\t%d\n", 
                   pid[i], at[i], bt[i], ct[i], wt[i], tat[i]);
        }
        printf("Avg WT=%.2f  Avg TAT=%.2f\n", avg_wt, avg_tat);
        
        // ===== SIMPLE GANTT CHART =====
        printf("\n=== GANTT CHART ===\n");
        printf("Time: ");
        int current_time = 0;
        
        for(int i = 0; i < order_count; i++) {
            int p = order[i];
            int duration = (i+1 < order_count) ? 
                          (ct[order[i+1]] - ct[order[i]]) : 
                          (ct[order[i]] - current_time);
            
            for(int j = 0; j < duration; j++) {
                printf("|");
                if(j == 0) printf("P%d", pid[p]);
            }
            current_time = ct[order[i]];
        }
        printf("\n");
        
        // Print timeline numbers (simplified)
        printf("     ");
        for(int i = 0; i < order_count; i++) {
            printf("%d", ct[order[i]]);
            if(i < order_count-1) printf("  ");
        }
        printf("\n");
    }
    return 0;
}
