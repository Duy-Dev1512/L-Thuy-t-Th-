/*chương trình này làm về thuật toán DFS sử dụng đệ quy
bên cạnh đó sẽ ghi lại nút cha của các nút trong quá trình duyệt phục vụ cho việc dựng cây
và đảm bảo tất cả các đỉnh đều được duyệt trong trường hợp đồ thị không liên thông*/

#include <stdio.h>

#define MAX_Vertices 20
#define MAX_Length 20

typedef struct
{
    int A[MAX_Vertices][MAX_Vertices];
    int n; // so luong dinh
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

int mark[MAX_Vertices];
//mảng parent[] lưu trữ nút cha
int parent[MAX_Vertices];
//thuật toán DFS sử dụng đệ quy
void DFS_recursion(Graph *G, int u, int p)
{
    if (mark[u] == 1)
    {
        return;
    }
    printf("%d\n",u);
    parent[u]=p;
    mark[u] = 1;
    List L = neighbors(G, u);
    for (int i = 1; i <= L.size; i++)
    {
        int v = element_at(&L, i);
        DFS_recursion(G, v, u);
    }
}

int main()
{
    Graph G;
    freopen("name", "r", stdin);
    int soDinh, soCung;
    scanf("%d%d", &soDinh, &soCung);
    init_Graph(&G, soDinh);

    int u, v;
    for (int i = 1; i <= soCung; i++)
    {
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    //khởi tạo các đỉnh đều trong trạng thái chưa duyệt mark[i]=0
    //khởi tạo tất cả các nút đều không có nút cha
    for(int i =1; i<=soDinh; i++){
        mark[i]=0;
        parent[i]=-1;
    }

    //duyệt qua tất cả các đỉnh
    for(int i=1; i<=soDinh; i++){
        if(mark[i]==0){
            DFS_recursion(&G, i, 0);
        }
    }

    DFS_recursion(&G, 1, 0);

    for(int i=1; i<=soDinh; i++){
        printf("%d %d\n", i, parent[i]);
    } 
    return 0;
}