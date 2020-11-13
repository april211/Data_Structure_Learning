#include <cstring>
#include <iostream>
using namespace std;

#define len 100
#define INF 999999

class Graph
{
    // 内部类
private:
    // 邻接表中表对应的链表的顶点
    class ENode
    {
    public:
        int vex;         // 顶点
        int weight;      // 权重
        ENode *nextEdge; // 指向下一条弧
    };

    // 邻接表中表的顶点
    class VNode
    {
    public:
        char data;        // 顶点信息
        ENode *firstEdge; // 指向第一条依付该顶点的弧
    };

    // 私有成员
private:
    int n; // 节点个数
    int e; // 边的个数
    VNode mVexs[len];

public:
    Graph()
    {
        ENode *node1, *node2;
        n = 7;
        e = 12;

        // 设置节点为默认数值
        string nodes = "ABCDEFG";
        // 输入节点
        for (int i = 0; i < n; i++)
        {
            mVexs[i].data = nodes[i];
            mVexs[i].firstEdge = NULL;
        }

        // 设置边为默认值
        char edges[][2] = {
            {'A', 'B'},
            {'A', 'F'},
            {'A', 'G'},
            {'B', 'C'},
            {'B', 'F'},
            {'C', 'D'},
            {'C', 'E'},
            {'C', 'F'},
            {'D', 'E'},
            {'E', 'F'},
            {'E', 'G'},
            {'F', 'G'}};

        // 边的权重
        int weights[len] = {12, 16, 14, 10, 7, 3, 5, 6, 4, 2, 8, 9};

        //　初始化邻接表的边
        for (int i = 0; i < e; i++)
        {
            int start = get_Node_Index(edges[i][0]);
            int end = get_Node_Index(edges[i][1]);

            // 初始化 node1
            node1 = new ENode();
            node1->vex = end;
            node1->weight = weights[i];
            node1->nextEdge = NULL;
            // 将 node 添加到 start 所在链表的末尾
            if (mVexs[start].firstEdge == NULL)
            {
                mVexs[start].firstEdge = node1;
            }
            else
            {
                linkLast(mVexs[start].firstEdge, node1);
            }

            // 初始化 node2
            node2 = new ENode();
            node2->vex = start;
            node2->weight = weights[i];
            node2->nextEdge = NULL;
            // 将 node 添加到 end 所在链表的末尾
            if (mVexs[end].firstEdge == NULL)
            {
                mVexs[end].firstEdge = node2;
            }
            else
            {
                linkLast(mVexs[end].firstEdge, node2);
            }
        }
    }

    // 相邻节点链接子函数
    void linkLast(ENode *p1, ENode *p2)
    {
        ENode *p = p1;
        while (p->nextEdge)
        {
            p = p->nextEdge;
        }
        p->nextEdge = p2;
    }

    // 返回顶点下标
    int get_Node_Index(char number)
    {
        for (int i = 0; i < n; i++)
        {
            if (number == mVexs[i].data)
            {
                return i;
            }
        }
        return -1; //这句话永远不会执行的
    }

    // 输出邻接表
    void print()
    {
        for (int i = 0; i < n; i++)
        {
            cout << mVexs[i].data;
            ENode *temp = mVexs[i].firstEdge;
            while (temp)
            {
                cout << " -> " << temp->vex;
                temp = temp->nextEdge;
            }
            cout << endl;
        }
        cout << endl;
    }

    // 得到两个节点之间的权重
    int getWeight(int m, int n)
    {
        ENode *enode = mVexs[m].firstEdge;
        while (enode)
        {
            if (enode->vex == n)
            {
                return enode->weight;
            }
            enode = enode->nextEdge;
        }
        return INF;
    }

    // 弗洛伊德算法
    void floyd()
    {
        int dist[n][n]; // 距离矩阵
        int path[7][7]; // 路径矩阵, 7为节点数目
        int i, j, k;
        int temp;

        // 初始化权重
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (i == j)
                {
                    dist[i][j] = 0;
                }
                else
                {
                    dist[i][j] = getWeight(i, j);
                }
                path[i][j] = i;
            }
        }

        // floyd 算法开始
        for (k = 0; k < n; k++)
        {
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++)
                {
                    temp = (dist[i][k] == INF || dist[k][j] == INF) ? INF : (dist[i][k] + dist[k][j]);
                    if (temp < dist[i][j])
                    {
                        dist[i][j] = temp;
                        path[i][j] = path[k][j];
                    }
                }
            }
        }

        // 打印出两点之间最短距离 + 路径
        for (i = 0; i < n - 1; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                if (dist[i][j] < 10)
                {
                    cout << mVexs[i].data << " -> " << mVexs[j].data << ": " << dist[i][j] << "  , path is: ";
                }
                else
                {
                    cout << mVexs[i].data << " -> " << mVexs[j].data << ": " << dist[i][j] << " , path is: ";
                }
                getPath(i, j, path);
                cout << endl;
            }
            cout << endl;
        }

        // 输出路径矩阵观察, 可用此矩阵自己用笔演算一下路径查找过程
        // for(i = 0; i < n; i++){
        //     for(j = 0; j < n; j++){
        //         cout<<path[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }
    }

    // 递归实现得到节点之间最短路径
    void getPath(int start, int end, int path[][7])
    {
        if (path[start][end] == start)
        {
            cout << mVexs[start].data << " " << mVexs[end].data << " ";
        }
        else
        {
            getPath(start, path[start][end], path);
            cout << mVexs[end].data << " ";
        }
    }
};

int main()
{
    Graph g;
    // 输出邻接表
    // g.print();

    // 弗洛伊德算法
    g.floyd();
    return 0;
}


// 参考：https://www.jianshu.com/p/f73c7a6f5a53