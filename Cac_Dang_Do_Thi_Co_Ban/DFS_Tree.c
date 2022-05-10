/*sử dụng thuật toán DFS để duyệt đồ thị và lưu lại thứ tự duyệt thông qua việc lưu trữ nút cha*/

#include <stdio.h>

#define MAX_Vertices 20
#define MAX_Length 20
#define MAX_Element 40

typedef struct
{
    int A[MAX_Vertices][MAX_Vertices];
    int n;
} Graph;

void init_Graph(Graph *G, int n)
{
    int i, j;
    G->n = n;
    for (i = 1; i <= G->n; i++)
    {
        for (j = 1; j <= G->n; j++)
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

// kiem tra 2 dinh co phai la lang gieng hay khong
int adjacent(Graph *G, int x, int y)
{
    return G->A[x][y] != 0;
}

int degree(Graph *G, int x)
{
    int deg = 0;
    int i;
    for (i = 1; i <= G->n; i++)
    {
        if (G->A[i][x] == 1)
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

    for (int i = 1; i <= G->n; i++)
    {
        if (G->A[i][x] == 1)
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

List depthFirstSearch(Graph *G, int x, int parent[])
{
    Stack S;
    makenullStack(&S);
    pushStack(&S, x);

    parent[x] = 0;

    List list_dfs;
    make_null(&list_dfs);

    int mark[MAX_Vertices];
    for (int i = 1; i <= G->n; i++)
    {
        mark[i] = 0;
    }
    while (!emptyStack(&S))
    {
        int u = getElementStack(&S);
        popStack(&S);
        if (mark[u] == 1)
            continue;
        push_back(&list_dfs, u);
        mark[u] = 1;
        List L = neighbors(G, u);

        for (int i = 1; i <= L.size; i++)
        {
            int v = element_at(&L, i);
            if (mark[v] == 0){
                pushStack(&S, v);
                parent[v]=u;
            }
        }
    }
    return list_dfs;
}

int main()
{
    Graph G;
    freopen("name", "r", stdin);
    int soDinh, soCung;
    scanf("%d%d", &soDinh, &soCung);

    init_Graph(&G, soDinh);
    int U, V;
    for (int e = 1; e <= soCung; e++)
    {
        scanf("%d%d", &U, &V);
        add_edge(&G, U, V);
    }

    int parent[MAX_Vertices];
    for (int i = 1; i <= G.n; i++)
    {
        parent[i] = -1;
    }
    int markDFS[MAX_Vertices];
    for (int i = 1; i <= G.n; i++)
    {
        markDFS[i] = 0;
    }
    for (int i = 1; i <= G.n; i++)
    {
        if (markDFS[i] == 0)
        {

            List dfs = depthFirstSearch(&G, i, parent);
            for (int i = 1; i <= dfs.size; i++)
            {
                printf("%d\n", element_at(&dfs, i));
                markDFS[element_at(&dfs, i)] = 1;
            }
        }
    }
    for(int u=1; u<=G.n; u++){
        printf("%d %d\n", u, parent[u]);
    }
    return 0;
}