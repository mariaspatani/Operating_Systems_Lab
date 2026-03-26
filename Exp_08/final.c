#include<stdio.h>

int main(){
    int np, nr;  // np=processes, nr=resources
    
    printf("Enter Number of Processes : ");
    scanf("%d",&np);
    
    printf("Enter Number of Resources: ");
    scanf("%d",&nr);
    
    // 3 Arrays for Banker's Algorithm
    int alloc[10][10], max[10][10], need[10][10], avail[10];
    
    // Input Allocation Matrix
    printf("Enter Allocation Matrix:\n");
    for(int i=0; i<np; i++)
        for(int j=0; j<nr; j++)
            scanf("%d",&alloc[i][j]);
    
    // Input Maximum Matrix  
    printf("Enter Maximum Matrix:\n");
    for(int i=0; i<np; i++)
        for(int j=0; j<nr; j++)
            scanf("%d",&max[i][j]);
    
    // Input Available Resources
    printf("Enter Available Resources:\n");
    for(int i=0; i<nr; i++)
        scanf("%d",&avail[i]);
    
    // 🔥 CALCULATE NEED MATRIX (max - alloc)
    printf("\nNeed Matrix:\n");
    for(int i=0; i<np; i++){
        for(int j=0; j<nr; j++){
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    
    // 🔥 SAFETY ALGORITHM STARTS HERE
    int finish[10] = {0};        // Process completed? 0=No, 1=Yes
    int safe[10];                // Safe sequence store
    int count = 0;               // Completed processes count
    
    while(count < np){           // Run until all processes done
        int found = 0;           // Any process can run?
        
        for(int p=0; p<np; p++){ // Check each process
            if(finish[p] == 0){  // If not finished
            
                // 🔥 CHECK: Need <= Available?
                int canRun = 1;
                for(int r=0; r<nr; r++){
                    if(need[p][r] > avail[r]){
                        canRun = 0;  // Cannot run
                        break;
                    }
                }
                
                // 🔥 PROCESS CAN RUN! Execute it
                if(canRun){
                    // Return allocated resources to available
                    for(int r=0; r<nr; r++){
                        avail[r] += alloc[p][r];
                    }
                    
                    safe[count] = p;     // Add to safe sequence
                    count++;             // One more process done
                    finish[p] = 1;       // Mark as finished
                    found = 1;
                }
            }
        }
        
        // No process can run = DEADLOCK!
        if(found == 0){
            printf("\nSystem is NOT in safe state\n");
            return 0;
        }
    }
    
    // 🔥 SUCCESS! Print safe sequence
    printf("\nSystem is in safe state\nSafe sequence: ");
    for(int i=0; i<np; i++){
        printf("P%d ", safe[i]);
    }
    printf("\n");
    
    return 0;
}
