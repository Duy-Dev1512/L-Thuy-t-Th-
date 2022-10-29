#include <stdio.h>
#define MAX_N 100

typedef struct
{
    int u, v;
    int w;
} Edge;

typedef struct
{
    int n, m;
    Edge edge[MAX_N];
} Graph;

void init_Graph(Graph *pG, int n)
{
    pG->n = n;
    pG->m = 0;
}

void add_edge(Graph *pG, int x, int y, int w)
{
    pG->edge[pG->m].u = x;
    pG->edge[pG->m].v = y;
    pG->edge[pG->m].w = w;
    pG->m++;
}

int parent[MAX_N];

int findRoot(int u)
{
    while (parent[u] != u)
        u = parent[u];
    return u;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Kruskal(Graph *pG, Graph *pT)
{
    int i, j;
    Edge temp;
    for (i = 0; i < pG->m; i++)
    {
        for (j = i + 1; j < pG->m; j++)
            if (pG->edge[i].w > pG->edge[j].w)
            {
                temp = pG->edge[i];
                pG->edge[i] = pG->edge[j];
                pG->edge[j] = temp;
            }
    }

    init_Graph(pT, pG->n);
    for (int u = 1; u <= pG->n; u++)
    {
        parent[u] = u;
    }
    int sum_w = 0, e;

    for (e = 0; e < pG->m; e++)
    {
        int u = pG->edge[e].u;
        int v = pG->edge[e].v;
        int w = pG->edge[e].w;
        int root_u = findRoot(u);
        int roor_v = findRoot(v);

        if (root_u != roor_v)
        {
            if (u < v)
            {
                add_edge(pT, u, v, w);
            }
            else
            {
                add_edge(pT, v, u, w);
            }
            parent[roor_v] = root_u;
            sum_w += w;
        }
    }
    return sum_w;
}

int main()
{
    Graph G, T;
    int n, m, u, v, w, e;

    freopen("Kruskal_data.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);

    for (e = 1; e <= m; e++)
    {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    int sum_w = Kruskal(&G, &T);
    printf("%d\n", sum_w);

    for (e = 0; e < T.m; e++)
    {
        printf("%d %d %d\n", T.edge[e].u, T.edge[e].v, T.edge[e].w);
    }
    return 0;
}