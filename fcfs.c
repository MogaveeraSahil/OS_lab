#include<stdio.h>
void swap(int *a,int *b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}
void sort(int *pid, int *at, int *bt, int n){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(at[i]<at[j]){
                swap(&at[i],&at[j]);
                swap(&bt[i],&bt[j]);
                swap(&pid[i],&pid[j]);
            }
        }
    }
}
int main(){
    int n;
    printf("Enter the number of processes:");
    scanf("%d",&n);
    int pid[n],at[n],bt[n],ct[n],tat[n],wt[n];
    for(int i=0;i<n;i++){
        printf("Enter arrival time and burst time : ");
        scanf("%d%d",&at[i],&bt[i]);
        pid[i]=i+1;
    }
    sort(pid,at,bt,n);
    int c = at[0]+bt[0];
    ct[0] = c;
    for(int i=1;i<n;i++){
        if(at[i]>c)
            c = at[i];
        ct[i]=c+bt[i];
        c=ct[i];
    }
    for(int i=0;i<n;i++){
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];
    }
    float avg_tat=0;
    float avg_wt=0;
    for(int i=0;i<n;i++){
        avg_tat+=tat[i];
        avg_wt+=wt[i];
    }
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t",pid[i],at[i],bt[i],ct[i],tat[i],wt[i]);
        printf("\n");
    }

    printf("\nAverage Turn around time : %f",avg_tat/n);
    printf("\nAverage waiting time : %f",avg_wt/n);
}
