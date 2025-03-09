#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

struct Node 
{
    int u, v, w;
};

struct DisjointSet 
{
    int parent, rank;
};

int findParent(struct DisjointSet *ds, int i)
 {
    if (ds[i].parent!= i) 
    {
        ds[i].parent = findParent(ds, ds[i].parent);
    }
    return ds[i].parent;
}

void unionSets(struct DisjointSet *ds, int i, int j) 
{
    int pi = findParent(ds, i);
    int pj = findParent(ds, j);
    if (ds[pi].rank < ds[pj].rank) 
    {
        ds[pi].parent = pj;
    } 
    else if (ds[pi].rank > ds[pj].rank) 
    {
        ds[pj].parent = pi;
    } 
    else 
    {
        ds[pi].parent = pj;
        ds[pj].rank++;
    }
}

void sortEdges(struct Node *edges, int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (edges[i].w > edges[j].w) 
            {
                struct Node temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

int findMST(struct Node *edges, int n) 
{
    struct DisjointSet ds[MAX_NODES];
    int mstCost = 0;
    for (int i = 0; i < n; i++) 
    {
        ds[i].parent = i;
        ds[i].rank = 0;
    }
    sortEdges(edges, n);
    int mstEdges = 0;
    for (int i = 0; i < n - 1 && mstEdges < n - 1; i++) 
    {
        struct Node e = edges[i];
        int u = findParent(ds, e.u);
        int v = findParent(ds, e.v);
        if (u!= v) 
        {
            unionSets(ds, u, v);
            mstCost += e.w;
            mstEdges++;
        }
    }
    return mstCost;
}

int main() 
{
    int n, m;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the number of edges: ");
    scanf("%d", &m);

    struct Node edges[m];

    printf("Enter the edges with their weights:\n");
    for (int i = 0; i < m; i++) 
    {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    int mstCost = findMST(edges, m);
    printf("The minimum spanning tree has a cost of %d.\n", mstCost);
    return 0;
}
