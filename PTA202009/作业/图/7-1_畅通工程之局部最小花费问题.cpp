#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <stack>
#include <vector>
#define MAX_SIDE 106
#define inf 0x3f3f3f3f
using namespace std;

stack<int> empty_row;
stack<int> empty_column;

int main()
{
    int N = 0;                          // 村庄数目 N (1≤N≤100)
    scanf("%d", &N);

    int matrix[N+6][N+6];
    int in_u[N+6] = {0,}, weight[N+6] = {0,};    // 初始化为 0
    int n_line = (N%2==0)?((N/2)*(N-1)):(((N-1)/2)*N);  // 输入行数

    // 准备使用 Prim算法，初始化矩阵为不可到达（边的权值为无穷大）
    for(int i = 1; i<= N; i++)
    {
        for(int j = 1; j<= N; j++)
        {
            matrix[j][i] = inf;
        }
    }

    // 随后的 N(N−1)/2行对应村庄间道路的成本及修建状态：
    // 每行给出4个正整数，分别是两个村庄的编号（从 1 编号到 N），此两村庄间道路的成本，以及修建状态 — 1表示已建，0表示未建
    for(int i = 0; i< n_line; i++)
    {
        int v1, v2, cost, status;
        scanf("%d%d%d%d", &v1, &v2, &cost, &status);
        if(status == 0)     // 如果该路没有建成，把边的权值赋值为修建成本
        {
            matrix[v1][v2] = matrix[v2][v1] = cost;     // 保持无向图矩阵的对称性
        }
        else                // 建成了的话，这条路径就会作为最小生成树的边，不需要成本（一定使用这条边）
        {
            matrix[v1][v2] = matrix[v2][v1] = 0;
        }
    }// 输入完毕

    // 从一号节点开始，将整个节点集分为两大部分：U 和 V-U
    in_u[1] = 1;

    // 载入其他各节点到集合 U 的代价
    for(int i = 1; i<= N; i++)
    {
        if(i == 1)
        {
            weight[i] = 0;      // 代价为零，表示该点已经并入集合 U
        }
        else
        {
            weight[i] = matrix[1][i];
        }
    }

    for(int i = 0; i< N; i++)
    {
        int min = inf, node = 0;
        for(int j = 1; j<= N; j++)
        {
            if((!in_u[j]) && (min > weight[j]))
            {
                min = weight[j];
                node = j;
            }
        }// 在集合 V-U 中找到到达 U 的最小代价，并记录节点号
        in_u[node] = 1;      // 将该节点归入集合 U 中

        // 更新 weigth 数列（原因是有新的节点加入到了集合 U 中，需要更新 V-U 到 U 的最小代价，看看有没有更小的代价可以更新到该数组中）
        for(int j = 1; j<= N; j++)
        {
            if((!in_u[j]) && (weight[j] > matrix[node][j]))
            {
                weight[j] = matrix[node][j];    // 更新为更小的代价
            }
        }
    }// 此时，weight 数组中存储的就是最小生成树各边的权值

    int sum_cost = 0;   // 新修建的路的总花费
    for(int i = 1; i<= N; i++)
    {
        sum_cost += weight[i];
    }// 对数组中元素求和即可

    printf("%d", sum_cost);

    return 0;
}
