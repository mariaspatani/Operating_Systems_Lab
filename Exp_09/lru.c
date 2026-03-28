
#include<stdio.h>
void printFrames(int f[],int frames){
    for(int i=0;i<frames;i++){
        f[i]==-1?printf("- \t"):printf("%d \t",f[i]);
    }
 }

 void lru(int pages[],int n,int frames){
    int time[10],f[10],hit=0,fault=0,count=0;
    for (int i=0;i<frames;i++){
        f[i]=-1;
        time[i]=0;
    }
    printf("\nPages\t");
     for(int i = 0; i < frames; i++) printf("F%d\t", i+1);
    printf("Status\n");
    for(int i=0;i<n;i++){
        int found=0;
        for(int j=0;j<frames;j++){
            if(f[j]==pages[i]){
                found=1;
                count++;
                time[j]=count;
                break;
            }
        }
        printf("%d\t", pages[i]);
        if(found){
            hit++;
            printFrames(f,frames);
            printf("H\n");
        }else{
            int min=time[0],pos=0;
            for(int j=1;j<frames;j++){
                if(time[j]<min){
                    min=time[j];
                    pos=j;
                }
            }
            f[pos]=pages[i];
            count++;
            time[pos]=count;
            fault++;
            printFrames(f,frames);
            printf("F\n");
        }
    }
         printf("Total Hits: %d\n",hit);
        printf("Total Faults: %d\n",fault);
 }
 int main(){
    int n,frames,pages[100];
    printf("Enter the number of reference length: ");
    scanf("%d", &n);

    printf("Enter the no of frames:");
    scanf("%d", &frames);

    printf("Enter the reference string:");
    for(int i=0;i<n;i++){
        scanf("%d", &pages[i]);
    }
    lru(pages,n,frames);
    return 0;


}
