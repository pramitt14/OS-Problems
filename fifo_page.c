#include<stdio.h>
int main()
{
    int i,j,n,a[50],f[10],no,k,avail,count=0;
    printf("\nENTER THE NUMBER OF PAGES:\n");
    scanf("%d",&n);
    printf("\nENTER THE PAGE NUMBER :\n");
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    printf("\nENTER THE NUMBER OF FRAMES :");
    scanf("%d",&no);
    for(i=0;i<no;i++)
        f[i]= -1;
    j=0;
    printf("ref\tpage\n");
    for(i=1;i<=n;i++)
    {
        printf("%d\t",a[i]);
        avail=0;
        for(k=0;k<no;k++)
        if(f[k]==a[i]){
            avail=1;
            printf("Page Hit");
        }
        if (avail==0)
        {
            f[j]=a[i];
            j=(j+1)%no;
            count++;
            for(k=0;k<no;k++){
            if(f[k]!=-1)
                printf("%d\t",f[k]);
            else{
                printf("\t");
            }
            }
        }
        printf("\n");
    }
    printf("Page Fault Is %d\n",count);
    return 0;
}