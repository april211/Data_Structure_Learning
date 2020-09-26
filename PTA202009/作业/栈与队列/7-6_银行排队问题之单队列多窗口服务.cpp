#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW -2
#define INFEASIBLE -1

typedef int Status;

typedef struct Customer
{
    int start_t;  // 顾客的到达时间
    int during_t; // 顾客所需的办理时长
    int wait_t;   // 顾客的等待时长
    int id;
} Customer;

typedef struct Pwindow
{
    int rece_sn;    // 该窗口总接待顾客数
    int status;     // 该窗口当前状态
    int process_st; // 总处理时长
    int cust_id;    // 当前顾客ID
} Pwindow;


// 队列的结点之类型
typedef struct QNode
{
    Customer data;      // 顾客数据集
    struct QNode *next; // 指针域
} QNode, *QueuePtr;

// 队列之类型
typedef struct LinkQueue
{
    QueuePtr front; // 队头指针
    QueuePtr rear;  // 队尾指针
    int length;     // 队列的长度（实际元素个数）
} LinkQueue;

// 构造一个空队列
Status InitQueue(LinkQueue &Q)
{
    Q.front = (QNode *)malloc(sizeof(QNode)); // Q.front 指向头结点
    if (!Q.front)
        exit(OVERFLOW);
    Q.rear = Q.front;
    Q.front->next = NULL;
    Q.length = 0;
    return OK;
}

// 销毁队列
Status DestroyQueue(LinkQueue &Q)
{
    while (Q.front)
    {
        Q.rear = Q.front->next;
        free(Q.front);
        Q.front = Q.rear;
    }
    Q.length = 0;
    return OK;
}

// 入队列
Status EnQueue(LinkQueue &Q, Customer &c)
{
    QNode *s = (QNode *)malloc(sizeof(QNode));
    if (!s)
        exit(OVERFLOW);
    s->data = c, s->next = NULL;
    Q.rear->next = s;
    Q.rear = s;
    Q.length++;
    return OK;
}

// 出队列（删去的是头结点的后一个结点），并用 c 返回其值
Status DeQueue(LinkQueue &Q, Customer &c)
{
    if (Q.front == Q.rear)
        return ERROR;
    QNode *p = Q.front->next;
    c = Q.front->next->data;
    Q.front->next = p->next;
    Q.length--;
    if (Q.rear == p)
        Q.rear = Q.front; // 删去的是尾结点时，需要修改尾结点
    free(p);
    return OK;
}

// 判空
Status QueueEmpty(const LinkQueue &Q)
{
    if (Q.front->next == NULL)
        return TRUE;
    else
        return FALSE;
}

// 返回队列的长度
int QueueLength(const LinkQueue &Q)
{
    return Q.length;
}

// 获得队头元素
Status GetHead(const LinkQueue &Q, Customer &c)
{
    if (Q.front->next == NULL)
        return ERROR;
    c = Q.front->next->data;
    return OK;
}

bool Big(int x, int y)
{
    return (x > y);
}

bool Small(Customer &x, Customer &y)
{
    return (x.wait_t < y.wait_t);
}

bool Cmp(Pwindow &x, Pwindow &y)
{
    return x.status < y.status;
}

int main()
{
    int cn = 0, wn = 0; // 顾客数、窗口数
    scanf("%d", &cn);
    Customer *wline = (Customer *)malloc(cn * sizeof(Customer));
    int *wt_array = (int *)malloc(cn * sizeof(int));
    int sumwt = 0;
    for (int i = 0; i < cn; i++)
    {
        int start_t = 0, during_t = 0;
        scanf("%d%d", &start_t, &during_t);
        if (during_t > 60) // 处理时间最长为 60
        {
            during_t = 60;
        }
        wline[i].during_t = during_t;
        wline[i].start_t = start_t;
        wline[i].wait_t = 0; // 初始化数据源
    }

/*     for (int i = 0; i < cn; i++)
    {
        printf("%d %d<<<<\n", wline[i].start_t, wline[i].during_t);
    } */

    scanf("%d", &wn); // 输入结束
    if (wn == 0)
        return 0;
    LinkQueue *pw_array = (LinkQueue *)malloc((wn + 1) * sizeof(LinkQueue)); // 下标表示窗口号

    for (int i = 1; i <= wn; i++)
    {
        InitQueue(pw_array[i]);
    } // 初始化所有窗口

    int cnt = 0;
    int *endtime = (int*)malloc(cn* sizeof(int));
    for (int i = 0; i < cn; i++)
    {
        if (i == 0) //第一个人绝对无需等待
        {
            wline[i].wait_t = 0; // 等待时长为 0
            wt_array[i] = wline[i].wait_t;
            sumwt += wline[i].wait_t;
            endtime[i] = wline[i].start_t + wline[i].wait_t + wline[i].during_t;
                //printf("%d %d First person\n", wline[i].start_t, wline[i].during_t);
            EnQueue(pw_array[1], wline[i]);
            cnt++;
        }
        else
        {
            if (cnt < wn) // 是 真·第一批人 才用得着
            {
                for (int j = 1; j <= wn; j++)
                {
                    if ((!QueueEmpty(pw_array[j]) && (pw_array[j].rear->data.start_t + pw_array[j].rear->data.during_t + pw_array[j].rear->data.wait_t <= wline[i].start_t)) || QueueEmpty(pw_array[j])) 
                    {
                        wline[i].wait_t = 0;
                        wt_array[i] = wline[i].wait_t;
                        sumwt += wline[i].wait_t;
                        endtime[i] = wline[i].start_t + wline[i].wait_t + wline[i].during_t;
                            //printf("%d %d First wave\n", wline[i].start_t, wline[i].during_t);
                        EnQueue(pw_array[j], wline[i]);
                        cnt++;
                        break; // 结合 flag 使用，安排下一位顾客
                    }
                }
            }
            else // 不是 真·第一批人
            {
                int flag = 0;                 // 先安排顾客到空闲窗口
                for (int j = 1; j <= wn; j++) // 按照序号，顾客优先去窗口号小的窗口
                {
                    QNode *perear = pw_array[j].rear;
                    if (perear->data.start_t + perear->data.during_t + perear->data.wait_t <= wline[i].start_t) // 当前所查找队列的最后一个顾客的完成时间点比后来者的开始时间点要早（实际为空）
                    {
                        wline[i].wait_t = 0;
                        wt_array[i] = wline[i].wait_t;
                        sumwt += wline[i].wait_t;
                        endtime[i] = wline[i].start_t + wline[i].wait_t + wline[i].during_t;
                            //printf("%d %d Have space\n", wline[i].start_t, wline[i].during_t);
                        EnQueue(pw_array[j], wline[i]);
                        flag++;
                        break; // 结合 flag 使用，安排下一位顾客
                    }
                }
                if (flag == 0) // 最坏情况：实际的窗口没有空闲的，顾客需要等待（实际上选择了等待时长最小的）
                {
                    int k = 0;
                    Customer *rear_array = (Customer *)malloc(wn * sizeof(Customer));
                    for (int j = 1; j <= wn; j++) // 按照序号，顾客优先去窗口号小的窗口
                    {
                        QNode *perear = pw_array[j].rear;
                        rear_array[k].id = j;
                        rear_array[k].wait_t = perear->data.start_t + perear->data.during_t + perear->data.wait_t - wline[i].start_t;
                        k++;
                    }   //printf("%d>>>>\n", rear_array[0].wait_t);
                    sort(rear_array, rear_array + wn, Small);
                        
                        //printf("%dSmallest wait time(rears)\n", rear_array[0].wait_t);
                    int nid = rear_array[0].id;
                    wline[i].wait_t = rear_array[0].wait_t;
                    wt_array[i] = wline[i].wait_t;
                    sumwt += wline[i].wait_t;
                    endtime[i] = wline[i].start_t + wline[i].wait_t + wline[i].during_t;
                        //printf("%d %d No space\n", wline[i].start_t, wline[i].during_t);
                    EnQueue(pw_array[nid], wline[i]);
                }
            }
        }
    } // 所有队列历史记录完毕

    
    sort(wt_array, wt_array + cn, Big);
        //printf("%dSum wait time\n", sumwt);
    double aver = (sumwt* 1.0)/(cn* 1.0);
    sort(endtime, endtime + cn, Big);

    printf("%.1lf %d %d\n", aver, wt_array[0], endtime[0]);


    for (int i = 1; i <= wn; i++)
    {
        if (i == 1)
            printf("%d", pw_array[i].length);
        else
            printf(" %d", pw_array[i].length);
    }

    return 0;
}



/* 
2
1 10
13 2
4
0.0 0 15
1 1 0 0 
*/
