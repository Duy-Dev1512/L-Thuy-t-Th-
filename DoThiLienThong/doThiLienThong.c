/*Bài này ứng dụng thuật toán DFS đệ quy để tìm bộ phận liên thông
Khái niệm về bộ phần liên thông (BPLT) nếu quên thì coi lại
Có vài bài tập sử dụng thuật toán này như: Qua đảo, Tôn Ngộ Không,...
Đề bài nằm trong tệp tin quadao.png và TonNgoKhong.png đính kèm*/
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
	int i;
    for (i = 1; i <= G->n; i++)
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

int mark[MAX_Vertices];
void DFS_recursion(Graph *G, int u)
{
    if (mark[u] == 1)
    {
        return;
    }
    mark[u] = 1;
    List L = neighbors(G, u);
    int i;
    for (i = 1; i <= L.size; i++)
    {
        int v = element_at(&L, i);
        DFS_recursion(G, v);
    }
}

//tìm bộ phận liên thông mạnh
int connected(Graph *G){
	int i;
	for(i=1; i<=G->n;i++){
		mark[i]=0;
	}
	DFS_recursion(G,1);
	for(i=1; i<=G->n ;i++){
		if(mark[i]==0)
			return 0;
	}
	return 1;
}

int main()
{
    Graph G;
    int soDinh, soCung, e;
    scanf("%d%d", &soDinh, &soCung);

    init_Graph(&G, soDinh);
    int U, V;
    for (e = 1; e <= soCung; e++)
    {
        scanf("%d%d", &U, &V);
        add_edge(&G, U, V);
    }

    if(connected(&G)==1)
    	printf("YES");
    else printf("NO");

    return 0;
}