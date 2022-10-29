#include <stdio.h>

#define MAX_N 100
#define MAX_M 500
#define INF 9999999

typedef struct
{
    int u, v, w;
    int link;
} Edge;

typedef struct
{
    int n, m;
    Edge edges[MAX_M];
} Graph;

typedef struct
{
    int n;
    int parent[MAX_N];
    int weight[MAX_N];
    int link[MAX_N];
} Tree;

void init_graph(Graph *G, int n)
{
    G->n = n;
    G->m = 0;
}

void init_Tree(Tree *T, int n)
{
    T->n = n;
    for (int i = 1; i <= n; i++)
    {
        T->parent[i] = -1;
        T->weight[i] = INF;
        T->link[i] = -1;
    }
}

void add_edge(Graph *G, int u, int v, int w, int link)
{
    int m = G->m;
    G->edges[m].u = u;
    G->edges[m].v = v;
    G->edges[m].w = w;
    G->edges[m].link = link;
    G->m++;
}

void buildH(Graph *G, int root, Tree *T)
{
    init_Tree(T, G->n); // khoi tao cay rong
    for (int e = 0; e < G->m; e++)
    {
        int u = G->edges[e].u;
        int v = G->edges[e].v;
        int w = G->edges[e].w;
        int link = G->edges[e].link;
        if (w < T->weight[v])
        {
            T->parent[v] = u;
            T->weight[v] = w;
            T->link[v] = link; // chi den cung cua G(t-1)
        }
    }
    T->parent[root] = -1; // Loai bo cha cua root
    T->weight[root] = 0;  // neu co
}

// Bo sung mang ho tro id luu ten moi cho cac dinh
int id[MAX_N];

int find_cycles(Tree *H, int root)
{
    int no = 0;
    int color[MAX_N];
    // khoi tao id, color
    for (int i = 1; i <= H->n; i++)
    {
        id[i] = -1;
        color[i] = -1;
    }
    // Duyet qua tung dinh va lan theo parent cua no
    for (int j = 1; j <= H->n; j++)
    {
        int u = j;
        while (u != root && id[u] == -1 && color[u] != j)
        {
            color[u] = j;
            u = H->parent[u];
        }
        // Neu gap lai i => tao chu trinh
        if (color[u] == j)
        {
            no++;
            int v = H->parent[u];
            while (v != u)
            {
                id[v] = no;
                v = H->parent[v];
            }
            id[u] = no;
        }
    }
    return no;
}

void contract(Graph *G, Tree *H, int no, Graph *G1)
{
    init_graph(G1, no);
    for (int e = 0; e < G->m; e++)
    {
        int u = G->edges[e].u;
        int v = G->edges[e].v;
        int w = G->edges[e].w;
        if (id[u] != id[v])
        {
            add_edge(G1, id[u], id[v], w - H->weight[v], e);
        }
    }
}

void expand(Tree *H, Tree *H1, Graph *G1)
{
    for (int i = 1; i <= H->n; i++)
    {
        if (H->parent[i] != -1)
        {
            // Lay cung tuong ung trong G(t-1)
            Edge pe = G1->edges[H->link[i]];
            // Doi cha cua pe.v thanh pe.u
            H1->parent[pe.v] = pe.u;
            H1->weight[pe.v] += H->weight[i];
            H1->link[pe.v] = pe.link;
        }
    }
}

#define MAX_IT 10

void ChuLiu(Graph *G0, int s, Tree *T)
{
    Graph G[MAX_IT];
    Tree H[MAX_IT];
    int i, e;

    int t = 0;
    int root = s;
    G[0] = *G0;

    // Pha co
    while (1)
    {
        // Xay dung do thi xap xi
        buildH(&G[t], root, &H[t]);
        int no = find_cycles(&H[t], root);
        if (no == 0)
            break;

        // Dat ten moi cho cac dinh khong nam tron CT
        for (i = 1; i <= H[t].n; i++)
        {
            if (id[i] == -1)
                id[i] = ++no;
        }

        // Co
        contract(&G[t], &H[t], no, &G[t + 1]);
        root = id[root];
        t++;
    }

    // Pha gian~
    for (int k = t; k > 0; k--)
    {
        expand(&H[k], &H[k - 1], &G[k - 1]);
    }

    *T = H[0];
}

int main()
{
    Graph G;
    int n, m, u, v, e, w;
    freopen("Chuliu_Edmonds_data.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init_graph(&G, n);

    for (e = 0; e < m; e++)
    {
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w, -1);
    }

    Tree T;
    ChuLiu(&G, 1, &T);

    for (int i = 1; i <= T.n; i++)
    {
        if (T.parent[i] != -1)
        {
            printf("(%d, %d) %d\n", T.parent[i], i, T.weight[i]);
        }
    }
    int flag = 0;
    for (int i = 1; i <= T.n; i++)
    {
        if (id[i] != 1)
            flag = 1;
    }
    if (flag != 1)
        printf("YES");
    else
        printf("NO");
    return 0;
}