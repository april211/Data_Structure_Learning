#include <stdio.h>

/* typedef enum {false, true} bool; */
#define MaxVertexNum 10 /* 最大顶点数设为10 */
typedef int Vertex;     /* 用顶点下标表示顶点,为整型 */

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    Vertex AdjV;        /* 邻接点下标 */
    PtrToAdjVNode Next; /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode
{
    PtrToAdjVNode FirstEdge; /* 边表头指针 */
} AdjList[MaxVertexNum];     /* AdjList是邻接表类型 */

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;    /* 顶点数 */
    int Ne;    /* 边数   */
    AdjList G; /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */

bool Visited[MaxVertexNum]; /* 顶点的访问标记 */

LGraph CreateGraph(); /* 创建图并且将Visited初始化为false；裁判实现，细节不表 */

void Visit(Vertex V)
{
    printf(" %d", V);
}

void BFS(LGraph Graph, Vertex S, void (*Visit)(Vertex));

int main()
{
    LGraph G;
    Vertex S;

    G = CreateGraph();
    scanf("%d", &S);
    printf("BFS from %d:", S);
    BFS(G, S, Visit);

    return 0;
}

// 你拥有：访问标记数组、邻接表

// 广度优先遍历（图类型指针、起始节点、访问方法）
void BFS(LGraph Graph, Vertex S, void (*Visit)(Vertex))
{
    LGraph mg = Graph;                  // 拷贝
    int v_num = mg->Nv, e_num = mg->Ne; // 结点与边的个数
    Vertex que[v_num];                  // 存储将要顺序访问的结点
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < v_num; i++) // 初始化整形数组
    {
        que[v_num] = -1;
    }

    // 访问起始节点，并将其入队列
    (*Visit)(S);
    Visited[S] = true;
    que[cnt2++] = S;

    while (cnt1 < cnt2) // 队列不为空
    {
        for (PtrToAdjVNode ipt = (mg->G)[que[cnt1]].FirstEdge; ipt != NULL; ipt = ipt->Next)
        {
            Vertex v_id = ipt->AdjV; // 获取邻接点的下标
            if (!Visited[v_id])      // 如果未访问过该节点
            {
                (*Visit)(v_id);
                Visited[v_id] = true;
                que[cnt2++] = v_id; // 将该节点入队列，记忆遍历顺序
            }
        }
        cnt1++; // 该节点出队列
    }
}