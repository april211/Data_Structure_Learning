#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 110

int n, m;
int g[maxn][maxn];
int order[maxn][maxn];

vector<int> adj[maxn]; //用邻接表存后继结点
int indegree[maxn];
vector<int> topo; 

bool topoSort()
{
    int num = 0;
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
            q.push(i);
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        topo.push_back(u); //拓扑序
        num++;
        for (int i = 0; i < adj[u].size(); i++)
        {
            int v = adj[u][i];
            indegree[v]--;
            if (indegree[v] == 0)
                q.push(v);
        }
        adj[u].clear();
    }
    if (num == n)
        return true;
    else
        return false;
}

int dp[maxn]; //dp[i]：从i号顶点出发能到达的最大长度
vector<int> choice[maxn];
int DP(int i)
{
    if (dp[i] > 0)
        return dp[i]; //如果dp[i]已经计算得到，直接返回
    for (int j = 1; j <= n; j++)
    { //遍历i的所有出边
        if (g[i][j] != inf)
        {
            int temp = dp[j] + g[i][j];
            if (temp > dp[i])
            {
                dp[i] = temp;
                choice[i].clear();
                choice[i].push_back(j);
            }
            else if (temp == dp[i])
            {
                choice[i].push_back(j);
            }
        }
    }
    return dp[i];
}

bool vis[maxn];
void DFS(int i)
{
    vis[i] = true;
    for (auto j : choice[i])
    {
        DFS(j);
    }
}

int main()
{
    fill(g[0], g[0] + maxn * maxn, inf);
    int u, v, w;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &u, &v, &w);
        order[u][v] = i;
        g[u][v] = w;
        adj[u].push_back(v);
        indegree[v]++;
    }
    if (topoSort())
    {
        vector<int> st; //所有路径起点
        int max = -inf;
        for (auto it = topo.rbegin(); it != topo.rend(); it++)
        { //注意要逆拓扑求DP
            int i = *it;
            if (DP(i) > max)
            {
                max = DP(i);
                st.clear();
                st.push_back(i);
            }
            else if (DP(i) == max)
            {
                st.push_back(i);
            }
        }
        printf("%d\n", max);
        //按题目要求输出每段关键路径
        for (auto nums : st)
        {
            DFS(nums);
        }
        for (int i = 1; i <= n; i++)
        {
            if (!vis[i])
                continue;
            sort(choice[i].begin(), choice[i].end(), [&](int a, int b) { //起点相同 输出与输入时的顺序相反
                return order[i][a] > order[i][b];
            });
            for (auto j : choice[i])
            {
                printf("%d->%d\n", i, j);
            }
        }
    }
    else
    {
        printf("0\n");
    }
    return 0;
}


/* 7-5 关键活动 (30分)
假定一个工程项目由一组子任务构成，子任务之间有的可以并行执行，有的必须在完成了其它一些子任务后才能执行。“任务调度”包括一组子任务、以及每个子任务可以执行所依赖的子任务集。

比如完成一个专业的所有课程学习和毕业设计可以看成一个本科生要完成的一项工程，各门课程可以看成是子任务。有些课程可以同时开设，比如英语和C程序设计，它们没有必须先修哪门的约束；有些课程则不可以同时开设，因为它们有先后的依赖关系，比如C程序设计和数据结构两门课，必须先学习前者。

但是需要注意的是，对一组子任务，并不是任意的任务调度都是一个可行的方案。比如方案中存在“子任务A依赖于子任务B，子任务B依赖于子任务C，子任务C又依赖于子任务A”，那么这三个任务哪个都不能先执行，这就是一个不可行的方案。

任务调度问题中，如果还给出了完成每个子任务需要的时间，则我们可以算出完成整个工程需要的最短时间。在这些子任务中，有些任务即使推迟几天完成，也不会影响全局的工期；但是有些任务必须准时完成，否则整个项目的工期就要因此延误，这种任务就叫“关键活动”。

请编写程序判定一个给定的工程项目的任务调度是否可行；如果该调度方案可行，则计算完成整个工程项目需要的最短时间，并输出所有的关键活动。

输入格式:
输入第1行给出两个正整数N(≤100)和M，其中N是任务交接点（即衔接相互依赖的两个子任务的节点，例如：若任务2要在任务1完成后才开始，则两任务之间必有一个交接点）的数量。交接点按1~N编号，M是子任务的数量，依次编号为1~M。随后M行，每行给出了3个正整数，分别是该任务开始和完成涉及的交接点编号以及该任务所需的时间，整数间用空格分隔。

输出格式:
如果任务调度不可行，则输出0；否则第1行输出完成整个工程项目需要的时间，第2行开始输出所有关键活动，每个关键活动占一行，按格式“V->W”输出，其中V和W为该任务开始和完成涉及的交接点编号。关键活动输出的顺序规则是：任务开始的交接点编号小者优先，起点编号相同时，与输入时任务的顺序相反。

输入样例:
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 1
4 6 6
5 7 5
6 7 2
输出样例:
17
1->2
2->4
4->6
6->7 */
