/*kiểm tra đồ thị (vô hướng) chứa chu trình dựa trên thuật toán duyệt đồ thị theo chiều sâu (sử dụng đệ quy)
Kết hợp với tô màu các đỉnh như bên dưới.
Thuật toán này khác với thuật toán kiểm tra chu trình trên đồ thị có hướng một chút
ở chỗ bổ sung thêm kiểm tra v có phải là cha của u không (tránh trường hợp u gọi duyệt và và gọi duyệt).*/

// TÔ MÀU
/*Giả sử:
- Đỉnh chưa duyệt có màu WHITE (TRẮNG)
- Đỉnh đang duyệt có màu GRAY (XÁM)
- Đỉnh duyệt xong có màu BLACK (ĐEN).
Trong quá trình duyệt, nếu ta gặp 1 đỉnh v có màu GRAY có nghĩa là ta đã đi 1 vòng từ v rồi trở về chính nó.*/

#include <stdio.h>

#define MAX_N 20
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

#define WHITE 0
#define GRAY 1
#define BLACK 2

int color[MAX_N];
int has_circle = 0;

void DFS(Graph *pG, int u, int p)
{
    color[u] = GRAY;
    int v;
    for (v = 1; v <= pG->n; v++)
    {
        if (adjacent(pG, u, v))
        {
            if (v == p)
            {
                continue;
            }
            if (color[v] == WHITE)
            {
                DFS(pG, v, u);
            }
            else if (color[v] == GRAY)
            {
                has_circle = 1;
            }
        }
    }
    color[u] = BLACK;
}

int main()
{
    Graph G;
    int soDinh, soCung, e;
    scanf("%d%d", &soDinh, &soCung);

    init_Graph(&G, soDinh);
    int U, V;
    for (e = 0; e < soCung; e++)
    {
        scanf("%d%d", &U, &V);
        add_edge(&G, U, V);
    }

    int u;
    for (u = 1; u <= G.n; u++)
    {
        color[u] = WHITE;
    }

    for (u = 1; u <= G.n; u++)
    {
        if (color[u] == WHITE)
            DFS(&G, u, -1);
    }

    if (has_circle == 1)
    {
        printf("YES");
    }
    else
        printf("NO");

    return 0;
}
