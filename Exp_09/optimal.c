
#include<stdio.h>
void printFrames(int f[],int frames){
    for(int i=0;i<frames;i++){
        f[i]==-1?printf("- \t") : printf("%d\t",f[i]);
    }
}
void optimal(int pages[],int n,int frames){
    int f[10],hit=0,fault=0;
    for(int i=0;i<frames;i++){
        f[i]=-1;
    }
    printf("\nPages\t");
    for(int i=0;i<frames;i++)printf("F%d\t",i+1);
    printf("Status\n");
    for(int i=0;i<n;i++){
        int found=0;
        for(int j=0;j<frames;j++){
            if(f[j]==pages[i]){
                found=1;
                break;
            }
        }
        printf("%d\t",pages[i]);
        if(found){
            hit++;
            printFrames(f,frames);
            printf("H\n");
        }else{
            int pos=-1,far=-1;
            for(int j=0;j<frames;j++){
                int next=-1;
                for(int k=i+1;k<n;k++){
                    if(f[j]==pages[k]){
                        next=k;
                        break;
                    }
                }
                if(next==-1){
                    pos=j;
                    break;
                }
                if(next>far){
                    far=next;
                    pos=j;
                }
            }
                f[pos]=pages[i];
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
    optimal(pages,n,frames);
    return 0;


}
