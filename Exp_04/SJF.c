#include<stdio.h>

int main(){
    int i,n,j;
    int at[20], bt[20], wt[20], tat[20], ct[20];
    int completed[20];
    int avg_wt=0, avg_tat=0;
    
    printf("Enter the number of processes: \n");
    scanf("%d", &n);

    printf("\nEnter the Arrival Time and Burst Time:\n");
    for(i=0;i<n;i++){
        printf("P%d Arrival Time: ", i+1);
        scanf("%d",&at[i]);

        printf("P%d Burst Time: ", i+1);
        scanf("%d",&bt[i]);

        completed[i] = 0;   // initially not completed
    }

    int time = 0, count = 0;

    while(count < n){
        int min = 9999;
        int pos = -1;

        // Find process with minimum burst time among arrived processes
        for(i=0;i<n;i++){
            if(at[i] <= time && completed[i] == 0){
                if(bt[i] < min){
                    min = bt[i];
                    pos = i;
                }
            }
        }

        if(pos == -1){
            time++;   // if no process has arrived
        }
        else{
            time += bt[pos];
            ct[pos] = time;
            tat[pos] = ct[pos] - at[pos];
            wt[pos] = tat[pos] - bt[pos];

            avg_wt += wt[pos];
            avg_tat += tat[pos];

            completed[pos] = 1;
            count++;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f",(float)avg_wt/n);
    printf("\nAverage Turn Around Time = %.2f\n",(float)avg_tat/n);

    return 0;
}
