#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define inf 0x3f3f3f3f
using namespace std;

typedef struct RoadInfo
{
    int id;             // 路径编号（在所有路径组中的位置）
    int rescue_num;     // 救援队人数   
    int miles;          // 路径长度
}RoadInfo;

bool smaller_miles(RoadInfo x, RoadInfo y)
{
    return x.miles < y.miles;
}


int main()
{
    // N（2≤N≤500）是城市的个数，顺便假设城市的编号为 0 ~ (N−1)
    // M是快速道路的条数；S是出发地的城市编号；D是目的地的城市编号
    int N = 0, M = 0, S = 0, D = 0;     // S > D?
    scanf("%d%d%d%d", &N, &M, &S, &D);
    
    stack<int> nodes_stack;                  // 寻找两点之间的简单路径
    int   rescues_num[N+6];                  // 存储各个城市的救援队的数目
    int  adj_mat[N+6][N+6];                  // 邻接矩阵，存储道路信息
    bool  is_in_stack[N+6];                  // 记录某个节点是否已经入栈
    //vector<int> paths_rescues;             // 记录每一条路径的救援队数量
    
    // 初始化邻接矩阵、救援队数组、入栈判断数组
    for(int i = 0; i< N+6; i++)
    {
        rescues_num[i] = 0;
        is_in_stack[i] = false;
        for(int j = 0; j< N+6; j++)
        {
            adj_mat[j][i] = inf;
        }
    }
    
    // 第二行给出N个正整数，其中第i个数是第i个城市的救援队的数目，数字间以空格分隔
    for(int i = 0; i< N; i++)
    {
        scanf("%d", &(rescues_num[i]));
    }// 载入各个城市的救援队的数量

    // 随后的M行中，每行给出一条快速道路的信息，
    // 分别是：城市1、城市2、快速道路的长度，中间用空格分开，数字均为整数且不超过500
    for(int i = 0; i< M; i++)
    {
        int row_id, column_id, miles;
        scanf("%d%d%d", &row_id, &column_id, &miles);
        adj_mat[row_id][column_id] = adj_mat[column_id][row_id] = miles;    // 保持无向图邻接矩阵对称性
    }// 记录所有的快速道路的信息

    // 寻找从起始点到终止点的所有简单路径
    nodes_stack.push(S);                // 起始节点号 S 入栈
    is_in_stack[S] = true;              // 该节点已入栈
    
    vector<vector<int>> all_paths;       //存储所有简单路径
    vector<int> single_path;             //存储单条简单路径
    int c_position = -1;
    int top_element = -1;

    while (!nodes_stack.empty())
    {
        top_element = nodes_stack.top();        // 查看栈顶元素，判断是否已经到达终点
        if (top_element == D)                   // 若到达终点，输出路径，弹出栈中两个点，设置出栈状态
        {
            while (!nodes_stack.empty())
            {
                int tmp = nodes_stack.top();
                nodes_stack.pop();              // 这里 pop 是为了读取整个栈以获得一条路径
                single_path.push_back(tmp);     // 结点序号依次加入到单一路径变量中
            }

            all_paths.push_back(single_path);   //将该路径加入路径组中

            for (vector<int>::reverse_iterator rit = single_path.rbegin(); rit != single_path.rend(); rit++)
            {
                nodes_stack.push(*rit);         // 再将结点推回去
            }

            single_path.clear(); //清除单条路径

            nodes_stack.pop();
            is_in_stack[top_element] = false;
            c_position = nodes_stack.top();     //记录位置，以便从该位置之后进行搜索
            top_element = nodes_stack.top();
            nodes_stack.pop();
            is_in_stack[top_element] = false;
        }
        else    // 还没到达终点，未形成完整路径
        {
            int i = 0;
            for (i = c_position + 1; i<= N; i++)
            {
                if (is_in_stack[i] == false && adj_mat[top_element][i] != inf) //未入栈，而且节点之间有边相连
                {
                    is_in_stack[i] = true;
                    nodes_stack.push(i);                //入栈  
                    top_element = nodes_stack.top();    // 更新栈顶元素

                    //位置置零，是因为从记录的位置开始搜索完以后，在新的行上搜索，自然从零开始，以免漏掉节点
                    c_position = -1;     
                    break;              // 就找一个点
                }
            }
        }
    }

    int all_paths_num = all_paths.size();    // 路径数总和

    RoadInfo info_paths[all_paths_num];

    int cnt_path = 0;
    for(vector<vector<int>>::iterator pt = all_paths.begin(); pt != all_paths.end(); pt++)
    {
        info_paths[cnt_path].id = cnt_path;
        info_paths[cnt_path].rescue_num = 0;
        info_paths[cnt_path].miles = 0;
        for(vector<int>::iterator it = pt->begin(); it != pt->end(); it++)
        {
            info_paths[cnt_path].rescue_num += rescues_num[*it];
            if((it+1) != pt->end())     // 不越界，累加计算路径长度
            {
                info_paths[cnt_path].miles += adj_mat[*it][*(it+1)];
            }
        }
        cnt_path++;
    }

    sort(info_paths, info_paths+all_paths_num, smaller_miles);     // 按照路径长度由小到大先排序，保证是最短路径
    int smallest_miles = info_paths[0].miles;
    int maximum = info_paths[0].rescue_num;                        // 救援队最大数量 初始化
    int smallest_cnt = 0;
    int best_id = 0;
    for(int i = 0; i< all_paths_num; i++)
    {
        if(info_paths[i].miles == smallest_miles)
        {
            smallest_cnt++;                                        // 最短路径数目 +1
            if(info_paths[i].rescue_num > maximum)
            {
                maximum = info_paths[i].rescue_num;
                best_id = info_paths[i].id;
            }
        }
    }// 计算最小路径数目


    printf("%d %d\n", smallest_cnt, maximum);

    vector<vector<int>>::iterator best_path = all_paths.begin()+best_id;
    for(vector<int>::reverse_iterator it = best_path->rbegin(); it != best_path->rend(); it++)
    {
        if(it == best_path->rbegin())
            printf("%d", (*it));
        else
            printf(" %d", (*it));
    }

    return 0;
}






/*         if(info_paths[cnt_path].rescue_num > maximum) // 这里是在所有的简单路径中统计救援数目最大的，应该不符要求
        {
            maximum = info_paths[cnt_path].rescue_num;
            maxpt = pt;
        } */