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

// “Gpdf"
int Graph_Adj[max_vnum][max_vnum]; // 图的邻接带权矩阵
vector<int> prevex[max_vnum];      // 记录当前节点的前一个结点
int distance[max_vnum];            // 存储起始节点到某个节点的距离
bool final[max_vnum];              // 若已经求得从起始点到该点的最短路径（已确定），则为 TRUE

// Dijkstra A.
void DIJ(int start, int n) // 起始节点编号 节点总数目
{
    // 初始化 起始点到各个节点的距离为 INF，各节点均未确定最短路径（FALSE）
    for (int i = 0; i < n; i++)
    {
        distance[i] = INF, final[i] = FALSE;
    }

    // 起始节点 到起始节点的距离赋值为 0
    distance[start] = 0;

    // 执行 n遍
    for (int i = 0; i < n; i++)
    {
        // 寻找中介点编号 mid
        int mid = DEFAULT, min_value = INF; // 中介点、最小值（注意在内层循环之外）
        if (i == 0)
        {
            mid = start;          // 第一轮的中介点就是起始点本身，不用循环              
        }
        else
        {
            for (int j = 0; j < n; j++)
            {
                if ((!final[j]) && (distance[j] < min_value)) // 在尚未确定的结点中找到了距离起始节点最近的结点
                {
                    mid = j; // 第一轮与起始节点相同
                    min_value = distance[j];
                }
            }
        }

        // 若找不到可用的中介点，则说明所有的节点均已确定最短路径长度，应当结束算法
        if (mid == DEFAULT)
            return;

        // 本轮的中介点标记为 已确定
        final[mid] = TRUE;

        // 藉由中介点拓展，使起始节点到其他节点的距离变小（相较于前一状态，图本身并未改变）
        for (int j = 0; j < n; j++)
        {
            // 该点尚未确定最短路径长度，且中介点可以直接到达该点
            if ((!final[j]) && (Graph_Adj[mid][j] != INF))
            {
                // 经过中介点后路径变短，更新最短路径
                if (distance[mid] + Graph_Adj[mid][j] < distance[j]) //WRONG: Graph_Adj[start][mid]
                {
                    distance[j] = distance[mid] + Graph_Adj[mid][j];
                    prevex[j].clear();
                    prevex[j].push_back(mid); // 该中介点是 j号节点的前一个节点
                }
                else if (distance[mid] + Graph_Adj[mid][j] == distance[j]) // 若相等，保存该节点，不删除旧的
                {
                    prevex[j].push_back(mid);
                }
            }
        }
    }
}

int minimum = INF;     // 这里是最小优化问题（例如要求路径长度最短）
int shortest_cnt = 0;  // 记录最短路径条数
vector<int> temp_path; // 暂存路径（跟随递归动态变化）
vector<int> best_path; // 最优路径（路程一定最短，可以加入其它条件综合优化）

void find_paths(int start, int d)
{
    if (start == d) // 递归到起始节点
    {
        ++shortest_cnt;             // 最短路径数加一
        temp_path.push_back(start); // 将起始节点压入栈
        int value = 0;              // 求这一条完整路径的总权值（度规不一定非是路径长度）
        for (int i = 0; i < temp_path.size() - 1; i++)
        {
            value += Graph_Adj[temp_path[i]][temp_path[i + 1]]; // 这里可以根据题目需要，换成另外一个度规
        }
        if (value < minimum)
        {
            minimum = value;
            best_path = temp_path; // 保存此最优路径
        }
        temp_path.pop_back(); // 必须出栈，保持是一条路径（返回上一层递归）
        return;
    }
    else
    {
        temp_path.push_back(d); // 压入末端节点
        for (int i = 0; i < prevex[d].size(); i++)
        {
            find_paths(start, prevex[d][i]); // 该点的前一节点可能有多种选择，使得整条路径均为最短
        }
        temp_path.pop_back(); // 必须出栈，保持是一条路径（返回上一层递归）
        return;
    }
}

int main()
{

    return 0;
}
