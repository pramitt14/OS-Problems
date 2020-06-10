#include<stdlib.h>
#include<stdio.h>

int m,n;

int need_work( int need[][n], int work[],int k)
{

    int i, f=0;
    for (i=0; i<n;i++)
    {
        if (need[k][i] <= work[i])
            f++;
    }
    if (f==n)
        return 1;
    else
        return 0;
}

void safereq ( int alloc[][n], int need[][n], int finish[],int work[])
{
    int i,c=0, flag, k,ss[n];
    while(1)
    {
        flag =0;
        for (k=0;k<m; k++)
        {
            if (finish[k]==0)
            {
                if (need_work(need,work,k))
                {
                    finish[k]=1;
                    // releasing the resources
                    for (i=0;i<n;i++)
                        work[i]+=alloc[k][i];
                    flag=1;
                    ss[c]=k;
                    c++;
                }
            }
        }
        if (flag==0)
        {
            printf("Not a safe sequence\n");
            printf("Request not granted");
            exit(1);
        }
        else if (c==m)
        {
            printf("Safe Sequence");
            for ( i=0; i<m; i++)
                printf("%d",ss[i+1]);
            printf("\n Request Granted");
            exit(1);
        }
    }
}

int check( int need[][n], int avl[], int p, int req[])
{
     int j, f=0;
     for (j=0; j<n; j++)
     {
         if ( req[j] <= need[p][j])
            f++;
     }
     if ( f==n)
     {
         f=0;
         for (j=0; j<n; j++)
         {
             if (req[j] <=avl[j])
                f++;
         }
         if (f==n)
            return 1;
         else
            return 0;
     }
     else
        return 0;
}
int main()
{
    int i,j,p;
    printf("Enter no of process and no of resource type");
    scanf("%d %d",&m,&n);
    int max[m][n], alloc[m][n],sysmax[n], need[m][n], finish[m], work[n], avl[n],req[n];
    printf("Enter max resource to each process\n");
    for (i=0; i<m; i++)
    {
        for (j=0;j<n; j++){
            printf("for process %d, resource %d\n",i+1,j+1);
            scanf("%d",&max[i][j]);
        }
    }
    printf("Enter allocated resource to each process\n");
    for (i=0;i<m;i++)
    {
        for (j=0;j<n; j++){
            printf("for process %d, resource %d\n",i+1,j+1);
            scanf("%d",&alloc[i][j]);
        }
    }
        printf("Enter the system max resource types\n");
        for (i=0;i<n;i++){
            printf("For resource %d:\n",i+1);
            scanf("%d",&sysmax[i]);
        }
        // calculting the need
        for (i=0;i<m; i++)
        {
            for (j=0;j<n;j++)
                need[i][j]= max[i][j]-alloc[i][j];
        }
        // calculating available
        int sum;
        for (j=0;j<n;j++)
        {
            sum=0;
            for (i=0;i<m; i++)
                sum = sum + alloc[i][j];
            avl[j]=sysmax[j]-sum;
        }
        // finish
        for (i=0;i<m;i++)
            finish[i]=0;
        printf("Enter the process no");
        scanf("%d",&p);
        printf("Enter its request");
        for (i=0;i<n;i++)
            scanf("%d",&req[i]);
        // checking request condition
        if (check (need,avl,p,req))
           {
               for (i=0;i<n;i++)
               {
                   avl[i]-=req[i];
                   alloc[p][i]+= req[i];
                   need[p][i]-=req[i];
               }
           }
           else
           {
               printf("Request not granted");
               exit(1);
           }
    for(i=0;i<n;i++)
        work[i]=avl[i];
    safereq(alloc,need,finish,work);
}
