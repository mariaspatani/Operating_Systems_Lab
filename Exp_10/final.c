#include<stdio.h>
#define MAX 50

// Simple bubble sort
void sort(int arr[], int n){
    for(int i=0; i<n-1; i++)
        for(int j=0; j<n-i-1; j++)
            if(arr[j] > arr[j+1]){
                int t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
}

// Print movement path (SAME as original)
void graph(int start, int seq[], int n){
    int cur = start;
    printf("\nDisk Arm Movement Path:\n");
    printf("Step | Movement\n");
    printf("--------------------------------------\n");
    for(int i=0; i<n; i++){
        printf("%2d   | (%3d) -----> [%3d]\n", i+1, cur, seq[i]);
        cur = seq[i];
    }
    printf("--------------------------------------\n");
}

// SSTF - Shortest Seek Time First
void SSTF(int req[], int n, int head){
    int visited[MAX] = {0}, seek = 0;
    int seq[MAX], k = 0;
    
    for(int i=0; i<n; i++){
        int min_dist = 9999, next = -1;
        
        // Find closest unvisited request
        for(int j=0; j<n; j++){
            if(!visited[j]){
                int dist = (req[j] > head) ? (req[j]-head) : (head-req[j]);
                if(dist < min_dist){
                    min_dist = dist;
                    next = j;
                }
            }
        }
        
        seek += min_dist;
        head = req[next];
        seq[k++] = head;
        visited[next] = 1;
    }
    
    printf("\n--- SSTF ---\n");
    printf("Seek Time = %d\n", seek);
    graph(head, seq, k);  // head is now final position
}

// LOOK Algorithm
void LOOK(int req[], int n, int head){
    sort(req, n);
    int seek = 0, seq[MAX], k = 0;
    
    // Find first request >= head
    int pos = 0;
    while(pos < n && req[pos] < head) pos++;
    
    // Right sweep
    for(int i=pos; i<n; i++){
        seek += (req[i] > head) ? (req[i]-head) : (head-req[i]);
        seq[k++] = req[i];
        head = req[i];
    }
    
    // Left sweep
    for(int i=pos-1; i>=0; i--){
        seek += (req[i] > head) ? (req[i]-head) : (head-req[i]);
        seq[k++] = req[i];
        head = req[i];
    }
    
    printf("\n--- LOOK ---\n");
    printf("Seek Time = %d\n", seek);
    graph(head, seq, k);
}

// C-SCAN Algorithm
void CSCAN(int req[], int n, int head, int size){
    sort(req, n);
    int seek = 0, seq[MAX], k = 0;
    
    // Find first request >= head
    int pos = 0;
    while(pos < n && req[pos] < head) pos++;
    
    // Right to end
    for(int i=pos; i<n; i++){
        seek += (req[i] > head) ? (req[i]-head) : (head-req[i]);
        seq[k++] = req[i];
        head = req[i];
    }
    
    // Jump to end, then cylinder 0
    seek += (size-1 - head);
    seq[k++] = size-1;
    seek += (size-1);
    head = 0;
    seq[k++] = 0;
    
    // Left side
    for(int i=0; i<pos; i++){
        seek += (req[i] > head) ? (req[i]-head) : (head-req[i]);
        seq[k++] = req[i];
        head = req[i];
    }
    
    printf("\n--- C-SCAN ---\n");
    printf("Seek Time = %d\n", seek);
    graph(head, seq, k);
}

int main(){
    int n, head, size, choice;
    int req[MAX];
    
    printf("Enter number of requests: ");
    scanf("%d", &n);
    
    printf("Enter requests:\n");
    for(int i=0; i<n; i++)
        scanf("%d", &req[i]);
    
    printf("Enter initial head position: ");
    scanf("%d", &head);
    
    printf("Enter disk size: ");
    scanf("%d", &size);
    
    do{
        printf("\n1.SSTF\n2.LOOK\n3.C-SCAN\n4.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1: SSTF(req, n, head); break;
            case 2: LOOK(req, n, head); break;
            case 3: CSCAN(req, n, head, size); break;
            case 4: printf("Exit\n"); break;
            default: printf("Invalid choice\n");
        }
    }while(choice != 4);
    
    return 0;
}
