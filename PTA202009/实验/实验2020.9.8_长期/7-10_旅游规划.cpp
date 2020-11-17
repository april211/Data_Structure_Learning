#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>

#define max_vnum 504            // 注意啊。。节点数最多是 500个。。。
#define INF 999999
#define FALSE 0
#define TRUE 1
#define DEFAULT -1

using std::vector;

// 邻接矩阵双度规信息
typedef struct Info
{
    int miles; // 城市间路程长度
    int costs; // 路花费的钱
} Info;

Info Graph_Adj[max_vnum][max_vnum]; // 图的邻接带权矩阵
vector<int> prevex[max_vnum];       // 记录当前节点的前一个结点
int distance[max_vnum];             // 存储起始节点到某个节点的距离
bool final[max_vnum];               // 若已经求得从起始点到该点的最短路径（已确定），则为 TRUE

// 返回整型向量容器中的元素之和
int sum_vector(const vector<int> &v)
{
    int sum = 0, n = v.size();
    for (int i = 0; i < n; i++)
    {
        sum += v[i];
    }
    return sum;
}

// Dijkstra A.
void DIJ(int start, int n) // 起始节点编号 节点总数目
{
    // 初始化起始点到各个节点的距离为 INF，各节点均未确定最短路径（FALSE）
    for (int i = 0; i < n; i++)
    {
        distance[i] = INF, final[i] = FALSE;
    }

    // 将起始节点到起始节点的距离赋值为 0
    distance[start] = 0;

    // 执行 n遍
    for (int i = 0; i < n; i++)
    {
        // 寻找中介点编号 mid
        int mid = DEFAULT, min_value = INF; // 中介点、最小值（注意在内层循环之外）
        for (int j = 0; j < n; j++)
        {
            if ((!final[j]) && (distance[j] < min_value)) // 找到了距离起始节点最近的结点
            {
                mid = j; // 第一轮与起始节点相同
                min_value = distance[j];
            }
        }

        // 若找不到可用的中介点，则说明所有的节点均已确定最短路径长度，应当结束算法
        if (mid == DEFAULT)
            return;

        // 本轮的中介点标记为已访问
        final[mid] = TRUE;

        // 藉由中介点拓展，使起始节点到其他节点的距离变小
        for (int j = 0; j < n; j++)
        {
            // 该点尚未确定最短路径长度，且中介点可以直接到达该点
            if ((!final[j]) && (Graph_Adj[mid][j].miles != INF))
            {
                // 经过中介点后路径变短，更新最短路径
                if (distance[mid] + Graph_Adj[mid][j].miles < distance[j]) //WRONG: Graph_Adj[start][mid]
                {
                    distance[j] = distance[mid] + Graph_Adj[mid][j].miles;
                    prevex[j].clear();
                    prevex[j].push_back(mid); // 该中介点是 j号节点的前一个节点
                }
                else if (distance[mid] + Graph_Adj[mid][j].miles == distance[j]) // 若相等，保存该节点，不删除旧的
                {
                    prevex[j].push_back(mid);
                }
            }
        }
    }
}

int minimum = INF;

vector<int> temp_path; // 暂存路径

void find_paths(int start, int d)
{
    if (start == d)
    {
        temp_path.push_back(start);
        int value = 0;
        for (int i = 0; i < temp_path.size()-1; i++)
        {
            //printf("--> %d <--\n", Graph_Adj[temp_path[i]][temp_path[i+1]].costs);
            value += Graph_Adj[temp_path[i]][temp_path[i+1]].costs;
        }
        //printf("Value : %d\n", value);
        if (value < minimum)
        {
            minimum = value;
        }
        temp_path.pop_back();
        return;
    }
    else
    {
        temp_path.push_back(d); // 压入末端节点
        for (int i = 0; i < prevex[d].size(); i++)
        {
            find_paths(start, prevex[d][i]);
        }
        temp_path.pop_back();
    }
}

int main()
{
    // N（2≤N≤500）是城市的个数，顺便假设城市的编号为 0 ~ (N−1)
    // M是快速道路的条数；S是出发地的城市编号；D是目的地的城市编号
    int N = 0, M = 0, S = 0, D = 0;
    scanf("%d%d%d%d", &N, &M, &S, &D);

    // 初始化双度规邻接矩阵
    for (int i = 0; i < max_vnum; i++)
    {
        for (int j = 0; j < max_vnum; j++)
        {
            Graph_Adj[j][i].miles = Graph_Adj[i][j].miles = INF;
            Graph_Adj[j][i].costs = Graph_Adj[i][j].costs = INF;
        }
    }

    // 载入城市间信息到邻接矩阵中
    for (int i = 0; i < M; i++)
    {
        int city1, city2, miles, costs;
        scanf("%d%d%d%d", &city1, &city2, &miles, &costs);
        Graph_Adj[city1][city2].miles = Graph_Adj[city2][city1].miles = miles;
        Graph_Adj[city1][city2].costs = Graph_Adj[city2][city1].costs = costs;
    }

    // 寻找单源最短路径
    DIJ(S, N);
    find_paths(S, D);


    printf("%d %d", distance[D], minimum);

    return 0;
}


/* 7-10 旅游规划 (25分)
有了一张自驾旅游路线图，你会知道城市间的高速公路长度、以及该公路要收取的过路费。现在需要你写一个程序，帮助前来咨询的游客找一条出发地和目的地之间的最短路径。如果有若干条路径都是最短的，那么需要输出最便宜的一条路径。

输入格式:
输入说明：输入数据的第1行给出4个正整数N、M、S、D，其中N（2≤N≤500）是城市的个数，顺便假设城市的编号为0~(N−1)；M是高速公路的条数；S是出发地的城市编号；D是目的地的城市编号。随后的M行中，每行给出一条高速公路的信息，分别是：城市1、城市2、高速公路长度、收费额，中间用空格分开，数字均为整数且不超过500。输入保证解的存在。

输出格式:
在一行里输出路径的长度和收费总额，数字间以空格分隔，输出结尾不能有多余空格。

输入样例:
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
输出样例:
3 40 */
