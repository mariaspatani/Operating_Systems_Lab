#include<stdio.h>

int main(){
    int i,n,time=0,remain,flag=0,quantum;
    int at[20],bt[20],rt[20],wt[20],tat[20],ct[20];
    float avg_wt=0,avg_tat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    remain = n;

    printf("\nEnter Arrival Time and Burst Time:\n");
    for(i=0;i<n;i++){
        printf("P%d Arrival Time: ",i+1);
        scanf("%d",&at[i]);

        printf("P%d Burst Time: ",i+1);
        scanf("%d",&bt[i]);

        rt[i] = bt[i];   // Remaining time initially = Burst time
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d",&quantum);

    while(remain != 0){
        flag = 0;

        for(i=0;i<n;i++){
            if(rt[i] > 0 && at[i] <= time){

                if(rt[i] > quantum){
                    time += quantum;
                    rt[i] -= quantum;
                }
                else{
                    time += rt[i];
                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];

                    avg_wt += wt[i];
                    avg_tat += tat[i];

                    rt[i] = 0;
                    remain--;
                }
                flag = 1;
            }
        }

        if(flag == 0){
            time++;  // If no process is ready
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1,at[i],bt[i],ct[i],wt[i],tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f",avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n",avg_tat/n);

    return 0;
}
