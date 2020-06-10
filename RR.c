#include <stdio.h>
 
typedef struct
{
    int pid;
    int at;
    int bt;
    int rbt;
    int tat;
    int ct;
    int rt;
    int wt;
 
    int scheduled;
} Process;
 
typedef struct
{
    int front, rear;
    Process arr[50];
} Queue;
 
void enqueue(Queue *q, Process p)
{
    if ((q->front == 0 && q->rear == 49) || (q->rear == (q->front - 1)))
    {
        printf("Full Queue");
        return;
    }
    else if (q->front == -1)
    {
        q->front = q->rear = 0;
        q->arr[q->rear] = p;
    }
    else
    {
        q->rear = (q->rear + 1) % 50;
        q->arr[q->rear] = p;
    }
}
 
Process dequeue(Queue *q)
{
    if (q->front == -1)
    {
        printf("Empty Queue");
        return;
    }
 
    Process data = q->arr[q->front];
 
    if (q->front == q->rear)
    {
        q->front = q->rear = -1;
    }
    else
    {
        q->front = (q->front + 1) % 50;
    }
    return data;
}
 
Queue createQueue()
{
    Queue q;
    q.front = q.rear = -1;
    return q;
}
 
int isEmpty(Queue q)
{
    return (q.front == -1);
}
 
void main()
{
    Queue q = createQueue();
    Process p[10];
    int ctt = 0;
 
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
        p[i].rbt = p[i].bt;
        p[i].scheduled = 0;
    }
 
    // Sorting
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
 
    int timeSlice = 1;
    printf("Enter Time Slice: ");
    scanf("%d", &timeSlice);
 
    ctt = p[0].at;
    Process curr = p[0];
 
    int executed = 0;
    int scheduled = 0;
 
    printf("Process are Scheduled as Follows: \n");
    printf("\nTime \tPID \tAT \tBT \tCT \tTAT \tWT \tRT");
    while (executed != n)
    {
        if (isEmpty(q))
        {
            if(ctt < p[scheduled].at)
                ctt = p[scheduled].at;
            for (int i = scheduled; i < n; i++)
            {
                if (p[i].at <= ctt){
                    enqueue(&q, p[i]);
                    scheduled++;
                }
            }
        }
 
        curr = dequeue(&q);
        // printf("\nPID: %d\n", curr.pid);
        curr.rbt -= timeSlice;
        if(curr.rbt <= 0){
            printf("\n%d", ctt);
            ctt += timeSlice + curr.rbt;
            curr.ct = ctt;
            curr.tat = curr.ct - curr.at;
            curr.wt = curr.tat - curr.bt;
            printf("\t%d \t%d \t%d \t%d \t%d \t%d \t%d\n", curr.pid, curr.at, curr.bt, curr.ct, curr.tat, curr.wt, curr.rt);
            executed++;
        }
        else{
            if(curr.scheduled == 0){
                curr.rt = ctt - curr.at;
                curr.scheduled = 1;
            }
            ctt += timeSlice;
        }
 
        for (int i = scheduled; i < n; i++)
        {
            if (p[i].at <= ctt){
                enqueue(&q, p[i]);
                scheduled++;
            }
        }
       
        if(curr.rbt > 0)
            enqueue(&q, curr);
    }
}