#include<stdio.h>
#include<stdlib.h>

void prims(int n, int cost[10][10]);

int main()
{
    int i,j,n,cost[10][10];
    printf("Read no of nodes s : ");

    scanf("%d",&n);

    printf("read cost matrix\n");

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            scanf("%d",&cost[i][j]);

            if (cost[i][j]==0)
         cost[i][j]=999;
        }
    }

    prims(n, cost);

    return 0;
}

void prims(int n, int cost[10][10])
{
    int i,j,u,v,min,mincost=0,visited[10],ne=1;

    for(i=1;i<=n;i++)
    visited[i]=0;

    while(ne<n)
    {
        min=999;

        for(i=1;i<=n;i++)

        for(j=1;j<=n;j++)

        if(cost[i][j]<min)
        {
            if(visited[i]==0)
            continue;

            else
            {
                min = cost[i][j];
                u=i;
                v=j;
            }


        }
 
    }
 printf("Min cost of constructing MST is %d\n",mincost);
}
