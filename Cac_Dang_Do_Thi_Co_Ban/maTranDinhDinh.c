/*file chương trình này bao gồm cấu trúc ma trận đỉnh đỉnh và các hàm thông dụng 
được sử dụng cho đồ thị ma trận đỉnh đỉnh*/

#include <stdio.h>

#define MAX_Vertices 20

typedef struct
{
    int A[MAX_Vertices][MAX_Vertices];
    int n;
} Graph;

//ham khoi tao do thi
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

//ham them cung vao do thi vo huong
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

//ham tinh bac cua mot dinh
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

int main()
{
    /*có thể thêm từng cung đơn lẻ bằng các gọi từng hàm add_edge()
    hoặc đọc đồ thị từ tập tin như sau*/
    Graph G;
    freopen("name","r", stdin);
    int n, m;
    scanf("%d%d",&n,&m);
    init_Graph(&G, n);
    int u,v;
    for(int i=1; i<=m; i++){
        scanf("%d%d", &u,&v);
        add_edge(&G, u, v);
    }
    for(int i=1; i<=G.n; i++){
        for(int j =1; j<=G.n; j++){
            printf("%d ", G.A[i][j]);
        }
        printf("\n");
    }

    //bạn cũng có thể đọc bằng fopen tùy ý
    return 0;
}