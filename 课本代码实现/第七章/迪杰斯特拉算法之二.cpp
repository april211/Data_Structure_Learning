#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

#define max_vnum 10
#define INF 999999
#define FALSE 0
#define TRUE 1
#define DEFAULT -1

using std::vector;

int Graph_Adj[max_vnum][max_vnum]; // 图的邻接带权矩阵
vector<int> prevex[max_vnum];      // 记录当前节点的前一个结点
int distance[max_vnum];            // 存储起始节点到某个节点的距离
bool final[max_vnum];              // 若已经求得从起始点到该点的最短路径（已确定），则为 TRUE

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
            if ((!final[j]) && (Graph_Adj[mid][j] != INF))
            {
                // 经过中介点后路径变短，更新最短路径
                if (distance[mid] + Graph_Adj[mid][j] < distance[j])   //WRONG: Graph_Adj[start][mid]    
                {
                    distance[j] = distance[mid] + Graph_Adj[mid][j];
                    prevex[j].clear();
                    prevex[j].push_back(mid);   // 该中介点是 j号节点的前一个节点
                }
                else if(distance[mid] + Graph_Adj[mid][j] == distance[j])   // 若相等，保存该节点，不删除旧的
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
            value += Graph_Adj[temp_path[i]][temp_path[i+1]];
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
    





    return 0;
}
