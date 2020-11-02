#include <stdio.h>

/* typedef enum
{
    false,
    true
} bool; */
// 这里是原题目
#define MaxVertexNum 10 /* 最大顶点数设为10 */
#define INFINITY 65535  /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;     /* 用顶点下标表示顶点,为整型 */
typedef int WeightType; /* 边的权值设为整型 */

typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;                                   /* 顶点数 */
    int Ne;                                   /* 边数   */
    WeightType G[MaxVertexNum][MaxVertexNum]; /* 邻接矩阵 */
};
typedef PtrToGNode MGraph;  /* 以邻接矩阵存储的图类型 */
bool Visited[MaxVertexNum]; /* 顶点的访问标记 */

MGraph CreateGraph(); /* 创建图并且将Visited初始化为false；裁判实现，细节不表 */

void Visit(Vertex V)
{
    printf(" %d", V);
}

void DFS(MGraph Graph, Vertex V, void (*Visit)(Vertex));

int main()
{
    MGraph G;
    Vertex V;

    G = CreateGraph();
    scanf("%d", &V);
    printf("DFS from %d:", V);
    DFS(G, V, Visit);

    return 0;
}

// 深度优先遍历（图指针类型，遍历起点结点，访问方法）
void DFS(MGraph Graph, Vertex V, void (*Visit)(Vertex))
{
    MGraph tg = Graph;
    int v_num = tg->Nv, e_num = tg->Ne; // 获取结点和边的数目
    Visit(V);                           // 访问结点，并做标记
    Visited[V] = 1;

    for (int i = 0; i < v_num; i++)
    {
        if (((tg->G)[V][i]) == 1 && Visited[i] == 0)    // 不能写：((tg->G)[V][i]) != 0
        {
            DFS(tg, i, Visit);
        }
    }
}
