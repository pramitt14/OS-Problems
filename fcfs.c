#include<stdio.h>
#include<malloc.h>
struct process{
    int pid,at,bt,tat,ct,rt,wt;
};

int main(){
    struct process p[10],temp;
    int i,j,ctt=0,ttat=0,tat=0,trt=0,n,ideal;
    printf("Enter Number of elements:  ");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("Enter process id:\n");
        scanf("%d",&p[i].pid);
        printf("Enter process at:\n");
        scanf("%d",&p[i].at);
        printf("Enter process bt:\n");
        scanf("%d",&p[i].bt);
    }
    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(p[i].at>p[j].at){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT");
    for(i=0;i<n;i++){
        if(p[i].at>ctt){
            ideal=p[i].at-ctt;
            ctt=p[i].at;
        }
        p[i].ct=ctt+p[i].bt;
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        p[i].rt=ctt-p[i].at;
        printf("\n%d \t%d \t%d \t%d \t%d \t%d \t%d \t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt,p[i].rt);
        ctt=ctt+p[i].bt;
    }
        float x;
        x=ctt-ideal;
        x=((float)x/(float)ctt);
        printf("CPU UTILIZATION: %f",x*100);

}