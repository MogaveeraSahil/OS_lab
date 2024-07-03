#include<stdio.h>
#include<stdbool.h>
#define nr 10
#define np 10

int allocation[np][nr];
int request[np][nr];
int available[nr];

bool deadlock_det(int nproc, int nres){
    bool finish[np] = {false}; // Initialize all processes as not finished
    
    int work[nr];
    for(int i = 0; i < nres; i++){
        work[i] = available[i];
    }
    
    int count = 0;
    while(count < nproc){
        bool found = false;
        for(int i = 0; i < nproc; i++){
            if(!finish[i]){
                bool can_proceed = true;
                for(int j = 0; j < nres; j++){
                    if(request[i][j] > work[j]){
                        can_proceed = false;
                        break;
                    }
                }
                if(can_proceed){
                    // Resource allocation
                    for(int j = 0; j < nres; j++){
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    count++;
                    printf("Process %d visited\n", i);
                }
            }
        }
        if(!found){
            break; // No more processes can proceed
        }
    }
    
    return count < nproc; // If count < nproc, deadlock detected
}

int main(){
    int n1, n2;
    printf("Enter number of processes: ");
    scanf("%d", &n1);
    printf("Enter number of resources: ");
    scanf("%d", &n2);
    
    printf("Enter allocation matrix\n");
    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            scanf("%d", &allocation[i][j]);
        }
    }
    
    printf("Enter request matrix\n");
    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            scanf("%d", &request[i][j]);
        }
    }
    
    printf("Enter available resources\n");
    for(int i = 0; i < n2; i++){
        scanf("%d", &available[i]);
    }
    
    if(deadlock_det(n1, n2)){
        printf("Deadlock detected\n");
    }
    else{
        printf("Deadlock not detected\n");
    }
    
    return 0;
}