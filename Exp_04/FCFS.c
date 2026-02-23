#include<stdio.h>
int main(){
  int i,n,j,at[20],bt[20],wt[20],tat[20],temp,p[20],ct[20],avg_wt=0,avg_tat=0;
  printf("Enter the number of processes: \n");
scanf("%d", &n);
  printf("\n Enter the Arrival Time and Burst Time :\n");
  for(i=0;i<n;i++){
  printf("P%d Arrival Time :", i+1);
  scanf("%d", &at[i]);
 
  printf("P%d Burst Time : ", i+1);
  scanf("%d", &bt[i]);
  }
  for (i=0;i<n-1;i++){
  for(j=0;j<n-i-1;j++){
  if(at[j]>at[j+1]){
  temp=at[j];
  at[j]=at[j+1];
  at[j+1]=temp;
 
  temp =bt[j];
  bt[j]=bt[j+1];
  bt[j+1]=temp;
 
  temp =p[j];
  p[j]=p[j+1];
  p[j+1]=temp;
 
  }
  }
  }
  int time=0;
  for(i=0;i<n;i++){
  if(time <at[i]) {
  time=at[i];
  }
  time+=bt[i];
  ct[i]=time;
  tat[i]=ct[i]-at[i];
  wt[i]=tat[i]-bt[i];
  avg_wt+=wt[i];
  avg_tat+=tat[i];
  }
  printf("\nProcess\tAT\tBT\tCT\tWT\tTAT\n");
  for(i=0;i<n;i++){
  printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],ct[i],wt[i],tat[i]);
  }
  printf("\nAverage waiting Time =%.2f",(float) avg_wt/n);
  printf("\nAverage Turn Around Time =%.2f",(float) avg_tat/n);
 

  return 0;
 
 }
