#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 100

int graph[MAX_SIZE][MAX_SIZE];
int dist[MAX_SIZE][MAX_SIZE];
int n;

void warshall_algorithm() 
{
    int i, j, k;

    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++) 
        {
            dist[i][j] = (i == j)? 0 : INT_MAX;
        }
    }

    for (k = 0; k < n; k++) 
    {
        for (i = 0; i < n; i++) 
        {
            for (j = 0; j < n; j++) 
            {
                dist[i][j] = (dist[i][j] > dist[i][k] + dist[k][j])? dist[i][k] + dist[k][j] : dist[i][j];
            }
        }
    }

    printf("Shortest distance between all pairs of vertices:\n");
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < n; j++) 
        {
            printf("%d ", dist[i][j]);
        }
        printf("\n");
    }
}

int main() 
{
    int i, j, v1, v2, weight;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the weighted edges:\n");
    for (i = 0; i < n; i++)
     {
        for (j = 0; j < n; j++) 
        {
            scanf("%d", &graph[i][j]);
        }
    }

    warshall_algorithm();

    return 0;
}

