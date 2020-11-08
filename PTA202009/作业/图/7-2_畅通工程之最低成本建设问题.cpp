#include <algorithm>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// 使用 Kruskal 算法

#define inf 0x3f3f3f3f
using namespace std;

// 图的通用边类型（对无向图、有向图）
typedef struct Edge
{
    int weight;     // 边的权重
    int tail;       // 边的尾部
    int head;       // 边的头部
}Edge;


int find1(int x, int* par)  // 找到连通分量的根节点
{
    if (x == par[x])
    {
        return x;
    }
    else // x != par[x]
    {
        return par[x] = find1(par[x], par);
    }  
}

bool smaller(const Edge a, const Edge b)
{
    return a.weight < b.weight;
}


int main()
{
    int N = 0, M = 0;

    scanf("%d%d", &N, &M);

    int  part[N+6];          // 标定节点
    Edge edge[M+6];          // 存储所有给定的边的信息

    // 初始化 par 数组，每个结点各自单独构成一个连通分量，用序号进行分类标记
    for (int i = 1; i <= N; i++)
    {
        part[i] = i;
    }

    for (int i = 0; i < M; i++)
    {
        int v1, v2, cost;   // 村庄 1、村庄 2、花费
        scanf("%d%d%d", &v1, &v2, &cost);
        edge[i].tail = v1;
        edge[i].head = v2;
        edge[i].weight = cost;
    }// 载入给出的边的信息到边集中，输入结束

    sort(edge, edge + M, smaller);      // 对边集进行排序，便于后面寻找最小权值的边来组成最小生成树

    int ans = 0;        // 最终的结果变量
    int cnt = 0;        // 计算加入的边的条数之和，最终与需要的最少边数 (N-1)比较
    for (int i = 0; i < M; i++)
    {
        int x = find1(edge[i].tail, part);
        int y = find1(edge[i].head, part);
        if (x != y)                  // 如果这两个点所在的联通分量的根节点不是同一个
        {
            ans += edge[i].weight;   // 该边是最小生成树的一条边，算上它的权值
            part[x] = y;             // 将该节点并入该连通分量
            cnt++;                   // 已构成的边数目加 1
        }
    }

    if (cnt != N - 1)
    {
        printf("Impossible");
    }
    else
    {
        printf("%d", ans);
    }

    return 0;
}


/* 
7-2 畅通工程之最低成本建设问题 (30分)
某地区经过对城镇交通状况的调查，得到现有城镇间快速道路的统计数据，并提出“畅通工程”的目标：使整个地区任何两个城镇间都可以实现快速交通（但不一定有直接的快速道路相连，只要互相间接通过快速路可达即可）。现得到城镇道路统计表，表中列出了有可能建设成快速路的若干条道路的成本，求畅通工程需要的最低成本。

输入格式:
输入的第一行给出城镇数目N (1<N≤1000)和候选道路数目M≤3N；随后的M行，每行给出3个正整数，分别是该条道路直接连通的两个城镇的编号（从1编号到N）以及该道路改建的预算成本。

输出格式:
输出畅通工程需要的最低成本。如果输入数据不足以保证畅通，则输出“Impossible”。

输入样例1:
6 15
1 2 5
1 3 3
1 4 7
1 5 4
1 6 2
2 3 4
2 4 6
2 5 2
2 6 6
3 4 6
3 5 1
3 6 1
4 5 10
4 6 8
5 6 3
输出样例1:
12
输入样例2:
5 4
1 2 1
2 3 2
3 1 3
4 5 4
输出样例2:
Impossible
作者
DS课程组
单位
浙江大学
代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB
 */