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

int main(){
    Graph G;
	int n, m, e, u, v, x,y;
    int count =0;
	freopen("HeSinhThaiRung.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for(e=1; e<=m; e++){
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
    scanf("%d%d", &x, &y);

    for(int i=1; i<=G.n; i++){
        if(adjacent(&G,x,i)!=0 && adjacent(&G, y, i)!=0)
            count ++;
    }

    printf("%d", count);


    return 0;
}