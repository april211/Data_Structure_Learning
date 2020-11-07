/* 原博文地址：https://blog.csdn.net/tan_chi_she/article/details/69803111 */
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>
#define MAX_EDGE_NUM 500
#define MAX_LINE_LEN 200
using namespace std;

//读取文件的函数
int read_file(char **const buff, const unsigned int spec, const char *const filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Fail to open file %s, %s.\n", filename, strerror(errno));
        return 0;
    }
    printf("Open file %s OK.\n", filename);

    char line[MAX_LINE_LEN + 2];
    unsigned int cnt = 0;
    while ((cnt < spec) && !feof(fp))
    {
        line[0] = 0;
        if (fgets(line, MAX_LINE_LEN + 2, fp) == NULL)
            continue;
        if (line[0] == 0)
            continue;
        buff[cnt] = (char *)malloc(MAX_LINE_LEN + 2);
        strncpy(buff[cnt], line, MAX_LINE_LEN + 2 - 1);
        buff[cnt][MAX_LINE_LEN + 1] = 0;
        cnt++;
    }
    fclose(fp);
    printf("There are %d lines in file %s.\n", cnt, filename);

    return cnt;
}

//将每行的数据转换为int的函数
void char2int(char *char_data, int *int_data, int int_length)
{
    char c[10];
    int num = 0;
    int count = 0;
    for (int i = 0; i < 10;)
    {
        count = 0;
        while (char_data[i] != ' ' && char_data[i] != '\n' && char_data[i] != '\r' && count < 10)
        {
            c[count] = char_data[i];
            i++;
            count++;
        }
        int_data[num] = atoi(c);
        memset(c, 0, 10);
        ++num;
        if (num >= int_length)
        {
            return;
        }
        i++;
    }
}


int main(int argc, char *argv[])
{
    char *topo[MAX_EDGE_NUM];
    int line_num;
    //读取文件，需要在属性--配置属性--调试--命令参数，以及工作目录设置所读取的文件node.txt
    char *topo_file = argv[1];
    line_num = read_file(topo, MAX_EDGE_NUM, topo_file);

    printf("line num is :%d \n", line_num);
    if (line_num == 0)
    {
        printf("Please input valid topo file.\n");
        return -1;
    }
    //邻接矩阵
    int node_num = 11;
    short **adjcent_Matrix = new short *[node_num + 1](); //初始化邻接矩阵全为0
    for (int i = 0; i < node_num; i++)
    {
        adjcent_Matrix[i] = new short[node_num + 1]();
    }
    //按照例图填充邻接矩阵
    int start_node, end_node;
    int data2[2];
    for (int i = 0; i < line_num; i++)
    {
        char2int(topo[i], data2, 2);
        start_node = data2[0];
        end_node = data2[1];
        adjcent_Matrix[start_node][end_node] = 1;
    }
    bool *is_in_stack = new bool[node_num + 1](); //入栈状态变量
    stack<int> node_stack;
    int c_position = 0;
    vector<vector<int>> paths; //存储所有路径
    vector<int> path;          //存储单条路径

    //起点入栈
    node_stack.push(0);
    is_in_stack[0] = 1; //设置起点已入栈，1表示在栈中，0 表示不在
    int top_element;    //记录栈顶元素
    int tmp;
    while (!node_stack.empty())
    {
        top_element = node_stack.top(); //查看栈顶元素，判断是否已经到达终点
        if (top_element == node_num)    //若到达终点，输出路径，弹出栈中两个点，设置出栈状态
        {
            while (!node_stack.empty())
            {
                tmp = node_stack.top();
                node_stack.pop();
                path.push_back(tmp);
            }
            paths.push_back(path); //将路径加入路径组
            for (vector<int>::reverse_iterator rit = path.rbegin(); rit != path.rend(); rit++)
            {
                node_stack.push(*rit);
            }
            path.clear(); //清除单条路径

            node_stack.pop();
            is_in_stack[top_element] = 0;
            c_position = node_stack.top(); //记录位置，以便从该位置之后进行搜索
            top_element = node_stack.top();
            node_stack.pop();
            is_in_stack[top_element] = 0; //cout << vis[top_element];
        }
        else
        {
            int i = 0;
            for (i = c_position + 1; i < node_num + 2; i++)
            {

                if (is_in_stack[i] == 0 && adjcent_Matrix[top_element][i] != 0) //未入栈，而且节点之间有边相连
                {

                    is_in_stack[i] = 1; //stack In
                    node_stack.push(i); //入栈
                    c_position = 0;     //位置置零，是因为从记录的位置开始搜索完以后，在新的行上搜索，自然从零开始，以免漏掉节点
                    break;
                }
            }
            if (i == node_num + 2)
            {
                top_element = node_stack.top();
                is_in_stack[top_element] = 0;
                c_position = node_stack.top();
                node_stack.pop();
            }
        }
    }
    //========================  输出 ==========================
    //逆向
    for (int i = 0; i < paths.size(); i++)
    {
        cout << "路径" << i << ": ";
        for (int j = paths[i].size() - 1; j >= 0; j--)
        {
            if (j == 0)
            {
                cout << paths[i][j];
            }
            else
            {
                cout << paths[i][j] << "->";
            }
        }
        cout << endl;
    }
    //========================  输出 ==========================

    //删除内存
    for (int i = 0; i < node_num; i++)
    {
        delete[] adjcent_Matrix[i];
    }
    delete[] adjcent_Matrix;
}
