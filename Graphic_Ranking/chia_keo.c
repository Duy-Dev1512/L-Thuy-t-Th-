#include <stdio.h>

#define MAX_Vertices 100
#define Max_Element 100
int rank[MAX_Vertices];
int d[MAX_Vertices];
typedef int ElementType;

typedef struct
{
    int A[MAX_Vertices][MAX_Vertices];
    int n, m;
} Graph;

typedef struct
{
    ElementType data[Max_Element];
    int size;
} List;

void make_null(List *L)
{
    L->size = 0;
}

void push_back(List *L, ElementType x)
{
    L->data[L->size] = x;
    L->size++;
}

ElementType element_at(List *L, int i)
{
    return L->data[i - 1];
}

int count_list(List *L)
{
    return L->size;
}

void init_Graph(Graph *pG, int n)
{
    pG->n = n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            pG->A[i][j] = 0;
        }
    }
}

void add_edge(Graph *pG, int x, int y)
{
    pG->A[y][x] = 1;
}

int adjacent(Graph *pG, int x, int y)
{
    return pG->A[x][y] != 0;
}

int degree(Graph *pG, int x)
{
    int deg = 0;
    for (int i = 1; i <= pG->n; i++)
    {
        deg += pG->A[x][i];
    }
    return deg;
}

List neighbors(Graph *G, int x)
{
    List list;
    make_null(&list);
    for (int i = 1; i <= G->n; i++)
    {
        if (adjacent(G, x, i))
            push_back(&list, i);
    }
    return list;
}

void copy_list(List *L1, List *L2)
{
    make_null(L1);
    int x;
    for (int i = 1; i <= L2->size; i++)
    {
        x = element_at(L2, i);
        push_back(L1, x);
    }
}
List L1, L2;
int k = 1;

void ranking(Graph *G)
{
    int u, x;

    for (u = 1; u <= G->n; u++)
    {
        d[u] = 0;
    }
    for (x = 1; x <= G->n; x++)
    {
        for (u = 1; u <= G->n; u++)
        {
            if (G->A[x][u] != 0)
            {
                d[u]++;
            }
        }
    }

    make_null(&L1);
    for (u = 1; u <= G->n; u++)
    {
        if (d[u] == 0)
            push_back(&L1, u);
    }
    int i;
    while (L1.size > 0)
    {
        make_null(&L2);
        for (i = 1; i <= L1.size; i++)
        {
            int u = element_at(&L1, i);
            rank[u] = k;
            int v;
            for (v = 1; v <= G->n; v++)
            {
                if (G->A[u][v] != 0)
                {
                    d[v]--;
                    if (d[v] == 0)
                        push_back(&L2, v);
                }
            }
        }
        copy_list(&L1, &L2);
        k++;
    }
}
int main()
{

    Graph G;
    int n, m, a, b;
    scanf("%d%d", &n, &m);
    init_Graph(&G, n);
    for (int i = 0; i < m; i++)
    {
        scanf("%d%d", &a, &b);
        add_edge(&G, a, b);
    }

    int sum = 0;
    ranking(&G);
    for (a = 1; a <= n; a++)
    {
        printf("%d\n", rank[a]);
        sum += rank[a];
    }
    printf("%d", sum);
    return 0;
}
