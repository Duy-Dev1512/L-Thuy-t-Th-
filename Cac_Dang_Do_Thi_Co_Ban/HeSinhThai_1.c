#include <stdio.h>

#define MAX_Vertices 30
typedef struct
{
    int A[MAX_Vertices][MAX_Vertices];
    int n;
} Graph;

void init_graph(Graph *G, int n)
{
    G->n = n;
    for (int i = 1; i <= G->n; i++)
    {
        for (int j = 1; j <= G->n; j++)
        {
            G->A[i][j] = 0;
        }
    }
}

void add_edge(Graph *G, int x, int y)
{
    G->A[x][y] = 1;
    G->A[y][x] = 1;
}

int adjacent(Graph *G, int x, int y)
{
    return G->A[x][y] != 0;
}



void neighbors(Graph *G, int x, int y)
{
    for (int e = 1; e <= G->n; e++)
    {
        if (x != e)
        {
            if (adjacent(G, x, e) == 1 && adjacent(G, y, e) == 1)
            {
                printf("%d ", e);
            }
        }
    }
}

int main()
{
    Graph G;
    int n, e, x, y;
    int count = 0;
    freopen("HeSinhThaiRung.txt", "r", stdin);
    scanf("%d", &n);
    init_graph(&G, n);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &e);
            if (e == 1)
            {
                add_edge(&G, i, j);
            }
        }
    }
    scanf("%d%d", &x, &y);
    for (int i = 1; i <= n; i++)
    {
        if (adjacent(&G, x, i) != 0 && adjacent(&G, y, i) != 0)
        {
            count++;
        }
    }
    if (count != 0)
    {
        neighbors(&G, x, y);
    }
    else
        printf("KHONG CHUNG DOI THU");
    return 0;
}