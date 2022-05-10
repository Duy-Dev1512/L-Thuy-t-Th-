/*duyệt đồ thị theo chiều rộng sử dụng hàng đợi và lưu cha của các đỉnh để đảm bảo duyệt hết 
tất cả các đỉnh*/

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

// cai dat su dung cau truc hang doi
typedef struct
{
    int data[MAX_Element];
    int front, rear;
} Queue;

void make_null_Queue(Queue *Q)
{
    Q->front = 0;
    Q->rear = -1;
}

int empty_Queue(Queue *Q)
{
    return Q->front > Q->rear;
}

void push_Queue(Queue *Q, int x)
{
    Q->rear++;
    Q->data[Q->rear] = x;
}

int top(Queue *Q)
{
    return Q->data[Q->front];
}

void pop(Queue *Q)
{
    Q->front++;
}

List breadthFirstSearch(Graph *G, int x, int parent[])
{
    Queue Q;
    make_null_Queue(&Q);
    int mark[MAX_Vertices];
    for (int i = 1; i <= G->n; i++)
    {
        mark[i] = 0;
    }
    push_Queue(&Q, x);

    parent[x] = 0;

    List L_bfs;
    make_null(&L_bfs);
    while (!empty_Queue(&Q))
    {
        int u = top(&Q);
        pop(&Q);
        if (mark[u] == 1)
            continue;
        push_back(&L_bfs, u);

        mark[u] = 1;
        List L;
        make_null(&L);
        L = neighbors(G, u);
        int v;
        for (int i = 1; i <= L.size; i++)
        {
            v = element_at(&L, i);
            if (mark[v] == 0)
            {
                push_Queue(&Q, v);
                if (parent[v] == -1)
                {
                    parent[v] = u;
                }
            }
        }
    }
    return L_bfs;
}

int main()
{
    Graph G;
    freopen("name", "r", stdin);
    int soDinh, soCung, x, y;
    scanf("%d%d", &soDinh, &soCung);
    init_Graph(&G, soDinh);
    for (int i = 1; i <= soCung; i++)
    {
        scanf("%d%d", &x, &y);
        add_edge(&G, x, y);
    }

    int mark_bfs[MAX_Vertices], parent[MAX_Vertices];
    for (int u = 1; u <= G.n; u++)
    {
        mark_bfs[u] = 0;
        parent[u] = -1;
    }

    for (int u = 1; u <= G.n; u++)
    {
        if (mark_bfs[u] == 0)
        {
            List L = breadthFirstSearch(&G, u, parent);
            for (int i = 1; i <= L.size; i++)
            {
                printf("%d\n", element_at(&L, i));
                mark_bfs[element_at(&L, i)] = 1;
            }
        }
    }

    for (int u = 1; u <= G.n; u++)
    {
        printf("Parent[%d]= %d\n", u, parent[u]);
    }
    return 0;
}