#include<stdio.h>

int main(){
    int i,j,n,temp;
    int at[20],bt[20],pr[20],wt[20],tat[20],ct[20];
    float avg_wt=0,avg_tat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    printf("\nEnter Arrival Time, Burst Time and Priority:\n");
    for(i=0;i<n;i++){
        printf("P%d Arrival Time: ",i+1);
        scanf("%d",&at[i]);

        printf("P%d Burst Time: ",i+1);
        scanf("%d",&bt[i]);

        printf("P%d Priority: ",i+1);
        scanf("%d",&pr[i]);
    }

    // Sort by priority (small number = high priority)
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(pr[j] > pr[j+1]){
                temp=pr[j]; pr[j]=pr[j+1]; pr[j+1]=temp;

                temp=at[j]; at[j]=at[j+1]; at[j+1]=temp;

                temp=bt[j]; bt[j]=bt[j+1]; bt[j+1]=temp;
            }
        }
    }

    int time=0;

    for(i=0;i<n;i++){
        if(time < at[i])
            time = at[i];

        time += bt[i];
        ct[i] = time;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nProcess\tAT\tBT\tPR\tCT\tWT\tTAT\n");
    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1,at[i],bt[i],pr[i],ct[i],wt[i],tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f",avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f\n",avg_tat/n);

    return 0;
}
