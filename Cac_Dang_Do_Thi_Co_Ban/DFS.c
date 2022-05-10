/*file chương trình này làm về thuật toán duyệt đồ thị theo chiều sâu(DFS)
duyệt trên đồ thị ma trận đỉnh đỉnh*/

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

//bậc
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

//cấu trúc danh sách đặc và các hàm bổ trợ
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

//hàm có chức năng tìm láng giềng của 1 đỉnh
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

//cấu trúc dữ liệu ngăn xếp
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

//thuật toán DFS
void depthFirstSearch(Graph *G, int x)
{
    Stack S;
    makenullStack(&S);
    pushStack(&S, x);
    int mark[MAX_Vertices];
    for (int i = 1; i <= G->n; i++)
    {
        mark[i] = 0;
    }
    while (!emptyStack(&S))
    {
        int u = getElementStack(&S);//lấy đỉnh trên đầu ngăn xếp
        popStack(&S);//xóa đỉnh đó đi
        if (mark[u] == 1)
            continue;
        printf("Duyet: %d\n", u);
        mark[u] = 1;//đánh dấu nó đã duyệt
        List L = neighbors(G, u);

        for (int i = 1; i <= L.size; i++)
        {
            int v = element_at(&L, i);
            if (mark[v] == 0)
                pushStack(&S, v);
        }
    }
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

    depthFirstSearch(&G, 1);

    return 0;
}