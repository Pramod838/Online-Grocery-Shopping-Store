#include<stdio.h>
#include<stdlib.h>

#define INF 9999999
#define MAX 1000

int G[MAX][MAX], V;

void prims();

int main() 
{
    int i, j;

    scanf("%d", &V);

    for(i = 0; i < V; i++)
        for(j = 0; j < V; j++)
            scanf("%d", &G[i][j]);

    prims();

    return 0;
}

void prims() 
{
    int visided[MAX] = {0};
    int ne, x, y;

    visided[0] = 1;
    ne = 1;

    int min_cost = 0;

    while (ne < V) 
    {
        int min = INF;
        x = 0;
        y = 0;

        for (int i = 0; i < V; i++) 
        {
            if (visided[i]) 
            {
                for (int j = 0; j < V; j++) 
                {
                    if (!visided[j] && G[i][j]) 
                    {
                     if (min > G[i][j]) 
                    {
                            min = G[i][j];
                            x = i;
                            y = j;
                        }
                    }
                }
            }
        }
        min_cost += G[x][y];
        visided[y] = 1;
        ne++;
    }
    printf("Minimum cost = %d\n", min_cost);
}
