#include <stdio.h>

#define MAX_Vertices 100
#define MAX_Element 100
#define MAX_Length 100
#define MAXN 100
#define NO_EDGE 0
typedef struct
{
    int n, m;
    int W[MAXN][MAXN];
} Graph;

void init_graph(Graph *G, int n)
{
    int i, j;
    G->n = n;
    G->m=0;
    for (i = 1; i <= G->n; i++)
    {
        for (j = 1; j <= G->n; j++)
        {
            G->W[i][j] = 0;
        }
    }
}

void add_edge(Graph *G, int x, int y, int w)
{
    G->W[x][y] = w;
    G->W[y][x] = w;
}

// kiem tra 2 dinh co phai la lang gieng hay khong
int adjacent(Graph *G, int x, int y)
{
    return G->W[x][y] != 0;
}

int degree(Graph *G, int x)
{
    int deg = 0;
    int i;
    for (i = 1; i <= G->n; i++)
    {
        if (G->W[i][x] == 1)
            deg++;
    }
    return deg;
}

typedef struct
{
    int Data[MAX_Length];
    int size;
} List;

void make_null(List *L)
{
    L->size = 0;
}

void push_back(List *L, int x)
{
    L->Data[L->size] = x;
    L->size++;
}

int element_at(List *L, int i)
{
    return L->Data[i - 1];
}

List neighbors(Graph *G, int x)
{
    List L;
    make_null(&L);
    int i;
    for (i = 1; i <= G->n; i++)
    {
        if (G->W[i][x] == 1)
        {
            push_back(&L, i);
        }
    }
    return L;
}

typedef struct
{
    int data[MAX_Element];
    int size;
} Stack;

void makenullStack(Stack *S)
{
    S->size = 0;
}

int emptyStack(Stack *S)
{
    return S->size == 0;
}

void pushStack(Stack *S, int x)
{
    S->data[S->size] = x;
    S->size++;
}

int getElementStack(Stack *S)
{
    return S->data[S->size - 1];
}

void popStack(Stack *S)
{
    S->size--;
}

#define oo 999999
int mark[MAXN];
int pi[MAXN];
int p[MAXN];

void MooreDijkstra(Graph *G, int s)
{
    int u, v, it;
    for (u = 1; u <= G->n; u++)
    {
        pi[u] = oo;
        mark[u] = 0;
    }
    pi[s] = 0;
    p[s] = -1;
    for (it = 1; it < G->n; it++)
    {
        int j, min_pi = oo;
        for (j = 1; j <= G->n; j++)
        {
            if (mark[j] == 0 && pi[j] < min_pi)
            {
                min_pi = pi[j];
                u = j;
            }
        }

        mark[u] = 1;

        for (v = 1; v <= G->n; v++)
        {
            if (G->W[u][v] != NO_EDGE && mark[v] == 0)
            {
                if (pi[u] + G->W[u][v] < pi[v])
                {
                    pi[v] = pi[u] + G->W[u][v];
                    p[v] = u;
                }
            }
        }
    }
}

int main()
{

    // freopen("dt.txt", "r", stdin);
    Graph G;
    int n, m, u, v, w, e;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (e = 1; e <= m; e++)
    {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }
    MooreDijkstra(&G, 1);
    for (int i = 1; i <= G.n; i++)
    {
        printf("pi[%d] = %d, p[%d] = %d\n", i, pi[i], i, p[i]);
    }
    return 0;
}