#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

#define maxn 510
#define INF 0x3f3f3f3f

int G[maxn][maxn];          // 保存城市之间的距离
int rescue_num[maxn];       // 每个城市救援队的数目
int dis[maxn];              // 到某个点的距离
bool vis[maxn];             // 是否被访问过
vector<int> pre[maxn];      // 上一个结点

void Dijkstra(int s, int n)
{
    // 初始化所有距离为无限远
    for (int i = 0; i < n; i++)
    {
        dis[i] = INF;
    }
    dis[s] = 0;
    for (int i = 0; i < n; i++)
    {
        int u = -1, MIN = INF;
        for (int j = 0; j < n; j++)
        { // 寻找到能到达的距离最小的点
            if (vis[j] == false && dis[j] < MIN)
            {
                u = j;
                MIN = dis[j];
            }
        }
        if (u == -1) break; // 所有能到达的结点都使用过了
        vis[u] = true;
        for (int v = 0; v < n; v++)
        { // 如果 k 未被访问，且经过 u 为中介点使得到 k 的距离更小，那么就更新这条线路
            if (vis[v] == false && G[u][v] != INF)
            {
                if (dis[u] + G[u][v] < dis[v])
                {
                    dis[v] = dis[u] + G[u][v];
                    pre[v].clear();
                    pre[v].push_back(u);
                }
                else if (dis[u] + G[u][v] == dis[v])
                {
                    pre[v].push_back(u);
                }
            }
        }
    }
}

int maximum = 0;
int short_cnt = 0;                // 记录最短路径条数
vector<int> tempPath, shortest_path;

void DFS(int s, int v)
{
    if (s == v)
    { // 递归到了出发的结点
        short_cnt++;
        tempPath.push_back(v);
        int value = 0, id;
        for (int i = 0; i < tempPath.size(); i++)
        {
            id = tempPath[i];
            value += rescue_num[id];
        }
        if (value > maximum)
        {
            maximum = value;
            shortest_path = tempPath;
        }
        tempPath.pop_back();
    }
    else
    {
        tempPath.push_back(v);
        for (int i = 0; i < pre[v].size(); i++)
        {
            DFS(s, pre[v][i]);
        }
        tempPath.pop_back();
    }
}

int main()
{
    // N（2≤N≤500）是城市的个数，顺便假设城市的编号为 0 ~ (N−1)
    // M是快速道路的条数；S是出发地的城市编号；D是目的地的城市编号
    int N = 0, M = 0, S = 0, D = 0;
    scanf("%d%d%d%d", &N, &M, &S, &D);

    // 初始化邻接矩阵
    for(int i = 0; i< maxn; i++)
    {
        for(int j = 0; j< maxn; j++)
        {
            G[j][i] = INF;
        }
    }

    for (int i = 0; i < N; i++)
    { 
        scanf("%d", &rescue_num[i]);
    }// 载入每个城市的救援队数目
    
    for (int i = 0; i < M; i++)
    { 
        int c1, c2, miles;
        scanf("%d%d%d", &c1, &c2, &miles);
        G[c2][c1] = G[c1][c2] = miles;
    }// 载入城市间的距离

    Dijkstra(S, N);
    DFS(S, D);

    printf("%d %d\n", short_cnt, maximum);
    bool flag = false;
    for (int i = shortest_path.size() - 1; i >= 0; i--)
    {
        if (flag == true)
        {
            printf(" %d", shortest_path[i]);
        }
        else
        {
            printf("%d", shortest_path[i]);
            flag = true;
        }
    }

    return 0;
}