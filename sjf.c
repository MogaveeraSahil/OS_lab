#include<stdio.h>
void swap(int *a,int *b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}
void sort(int *pid, int *at, int *bt, int s,int n){
    for(int i=s;i<n;i++){
        for(int j=s;j<n;j++){
            if(at[i]<at[j]){
                swap(&at[i],&at[j]);
                swap(&bt[i],&bt[j]);
                swap(&pid[i],&pid[j]);
            }
        }
    }
}
void sortb(int *pid, int *at, int *bt, int s,int n){
    for(int i=s;i<n;i++){
        for(int j=s;j<n;j++){
            if(bt[i]<bt[j]){
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
    sort(pid,at,bt,0,n);
    int c = at[0]+bt[0];
    ct[0] = c;
    for(int i=1;i<n;i++){
        int t=i;
        int x=i;
        while(at[i]<c){
            t+=1;
            i+=1;
        }
        sortb(pid,at,bt,x,t);
        if(at[x]>c)
            c = at[x];
        for(x;x<t;x++){
            ct[x]=c+bt[x];
            c=ct[x];
        }
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
