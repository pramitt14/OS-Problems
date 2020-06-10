#include <stdio.h>
#include "process.h"
 
struct Process{
    int pid,at,bt,tat,ct,rt,wt,scheduled;
};
void main()
{
    struct Process p[10];
    int ctt = 0, ttat = 0, twt = 0, trt = 0, idle = 0;
 
    int n;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
 
    printf("\nEnter Details of the processes - ");
 
    for (int i = 0; i < n; i++)
    {
        printf("\n\nProcess %d:", i + 1);
        printf("\n PID: ");
        scanf("%d", &p[i].pid);
        printf("\n Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("\n Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].scheduled = 0;
    }
 
    // Sorting
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
 
    printf("Process are Scheduled as Follows: \n");
    printf("\nPID \tAT \tBT \tCT \tTAT \tWT \tRT");
    int temp = n;
    if(p[0].at > ctt){
        idle += p[0].at - ctt;
        ctt = p[0].at;
    }
    while (temp > 0)
    {
        int minID = 0;
        for (int i = 0; p[i].at <= ctt && i<n; i++)
        {
            // printf("min - %d   i - %d\n", minID, i);
            if (p[minID].bt > p[i].bt || p[minID].scheduled==1)
            {
                if(p[i].scheduled!=1){
                    minID = i;
                }
            }
        }
 
        int i = minID;
        if(p[i].at > ctt){
            idle = idle + p[i].at - ctt;
            ctt = p[i].at;
        }
       
        
        p[i].ct = ctt + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = ctt - p[i].at;
        p[i].scheduled = 1;
        printf("\n%d \t%d \t%d \t%d \t%d \t%d \t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
        ctt = ctt + p[i].bt;
        temp--;
    }
 
    printf("\nCPU Utilization: %.2f\n", ((float)(ctt-idle)/(float)ctt));
}