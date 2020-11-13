#include <iostream>
#include <string.h>
using namespace std;

#define len 100
#define INF 999999

class Graph
{
    // 内部类
private:
    // 邻接表中表对应的链表的顶点（链表节点）
    class ENode
    {
    public:
        int vex;         // 顶点
        int weight;      // 权重
        ENode *nextEdge; // 指向下一条弧
    };

    // 邻接表中表的顶点（数组元素）
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

    // 迪杰斯特拉算法
    void dijkstra(int start)
    {
        int i, j, k, min;
        int temp;
        int dist[n]; // 距离数组
        int flag[n]; // 记录是否已找到最小距离,已找到为1，没找到为0
        int prev[n]; // 当前节点的最短路径中前一个节点

        // 初始化
        for (i = 0; i < n; i++)
        {
            dist[i] = getWeight(start, i);  // 导入自起始点伸展的所有的边的代价（没有的是 INF）
            flag[i] = 0;                    // 均为未访问状态
            prev[i] = start;                // 起始节点是路径的前一个结点
        }

        dist[start] = 0;                    // 确保到达起始节点的代价为 0
        flag[start] = 1;                    // 已访问起始节点

        // 注意这里有一个坑，比如一共有 n个节点，目前已知 start->start距离为0，
        // 　　则现在只要求出 start->剩下 n-1个节点最短距离即可，所以此处循环次数是 n-1次，而不是 n次
        for (j = 0; j < n - 1; j++)
        {
            min = INF;
            // 找到目前 dist 中的距离最短节点
            for (i = 0; i < n; i++)
            {
                if (flag[i] == 0 && dist[i] < min)
                {
                    min = dist[i];
                    k = i;          // 记录该节点
                }
            }

            // cout<<mVexs[k].data<<" "<<min<<endl; 可将大循环中的 n-1改为 n，看这句话执行效果，将会明白我说的坑的含义
            dist[k] = min;
            flag[k] = 1;            // 下一步将在该节点上拓展边与新结点，在此过程中可能产生其他节点到起始节点更短的路径

            // 更新最短距离
            for (i = 0; i < n; i++)
            {
                temp = dist[k] + getWeight(k, i);       // 注意，这里是合计路径长度
                if (flag[i] == 0 && temp < dist[i])
                {
                    dist[i] = temp;
                    prev[i] = k;
                }
            }
        }

        // 输出最短距离
        for (i = 0; i < n; i++)
        {
            if (i == start)
            {
                cout <<"The shortest path's length between "<< mVexs[start].data << " and " << mVexs[start].data << " is : " << dist[i] << "  , path : " << mVexs[start].data << " " << mVexs[start].data << endl;
            }
            else
            {
                cout <<"The shortest path's length between " << mVexs[start].data << " and " << mVexs[i].data << " is : " << dist[i] << " , path : ";
                getPath(i, start, prev);
                cout << endl;
            }
            // cout<<mVexs[start].data<<" -> "<<mVexs[i].data<<" 最短距离为: "<<dist[i]<<endl;
        }
    }

    // 得到 dijkstra 节点之间最短路径
    void getPath(int i, int start, int prev[])
    {
        if (i == start)
        {
            cout << mVexs[i].data << " ";
        }
        else
        {
            getPath(prev[i], start, prev);
            cout << mVexs[i].data << " ";
        }
    }
};

int main()
{
    Graph g;
    // 输出邻接表
    // g.print();

    char start;
    cout << "Please enter the initial node: ";
    cin >> start;
    g.dijkstra(g.get_Node_Index(start));
    return 0;
}

// 原地址：https://www.jianshu.com/p/8f4c869b321e
// 有改动
