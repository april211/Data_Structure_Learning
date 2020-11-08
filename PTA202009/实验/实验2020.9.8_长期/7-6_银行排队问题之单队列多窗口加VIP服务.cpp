#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
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
    int id;       // 顾客应去（所在）窗口号
    int is_vip;   // 是否为 VIP
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

// 判断普通窗口现在有没有空的（已知VIP窗口现在有人）。如果有，返回第一个现在空闲的窗口号；否则返回 -1
int ElseAvaliable(LinkQueue *pw_array, Customer &cc, int wn, int vipwid)
{
    int normwid = -1; // 如果最终没找到，直接返回该原始值
    for (int i = 0; i < wn; i++)
    {
        if (i == vipwid)
            continue;
        if ((!QueueEmpty(pw_array[i]) && (pw_array[i].rear->data.start_t + pw_array[i].rear->data.during_t + pw_array[i].rear->data.wait_t < cc.start_t)) || QueueEmpty(pw_array[i]))
        {
            normwid = i;
            break;
        }
    }
    return normwid;
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
    int cn = 0, wn = 0, vipn = 0, norn = 0;                      // 总顾客数、窗口数、VIP顾客数、普通顾客数
    int vipwid = -1;                                             // VIP 窗口编号（ 0 ~ wn - 1 ）
    int sumwt = 0;                                               // 所有顾客的等待时长总和
    scanf("%d", &cn);                                            // 第一行输入顾客总人数
    int *wt_array = (int *)malloc(cn * sizeof(int));             // 记录所有顾客的等待时长
    int *endtime = (int *)malloc(cn * sizeof(int));              // 记录每位顾客的结束时间点
    Customer *wline = (Customer *)malloc(cn * sizeof(Customer)); // 顾客原始等待序列

    // 开始逐行读入每个顾客的信息
    for (int i = 0; i < cn; i++)
    {
        int start_t = 0, during_t = 0, is_vip = 0;
        scanf("%d%d%d", &start_t, &during_t, &is_vip);
        if (during_t > 60) // 处理时间最长为 60
        {
            during_t = 60;
        }
        wline[i].during_t = during_t;
        wline[i].start_t = start_t;
        wline[i].wait_t = 0; // 初始化到达时间、预计处理时间、等待时间
        wline[i].id = -1;    // 应去窗口id初始化为 -1
        if (!is_vip)
        {
            wline[i].is_vip = 0; // 不是 VIP
            norn++;              // 普通顾客数增加 1
        }
        else
        {
            wline[i].is_vip = 1; // 是 VIP
            vipn++;              // VIP顾客数增加 1
        }
    }

    /*     for (int i = 0; i < cn; i++)
    {
        printf("%d %d<<<<\n", wline[i].start_t, wline[i].during_t);
    } */

    scanf("%d%d", &wn, &vipwid); // 输入总窗口个数、VIP窗口编号，全部输入结束

    if (wn == 0)
        return 0; // 若未开设等待窗口，直接结束程序

    // 这是所有的处理窗口的序列。顺序表下标表示窗口号（从 0 到 wn-1），共计 wn 个窗口
    LinkQueue *pw_array = (LinkQueue *)malloc(wn * sizeof(LinkQueue));

    // 初始化所有窗口序列
    for (int i = 0; i < wn; i++)
    {
        InitQueue(pw_array[i]);
    }

    int cnt = 0; // 已服务顾客数

    // 将每位顾客安排到各个窗口的队列中
    for (int i = 0; i < cn; i++)
    {
        if (i == 0) //第一个人绝对无需等待
        {
            wline[i].wait_t = 0; // 等待时长为 0
            wt_array[i] = wline[i].wait_t;
            sumwt += wline[i].wait_t; // 在这里，这一步可以舍弃
            endtime[i] = wline[i].start_t + wline[i].wait_t + wline[i].during_t;
            //printf("%d %d First person\n", wline[i].start_t, wline[i].during_t);
            if (wline[i].is_vip) // 如果该顾客的确是 VIP
            {
                EnQueue(pw_array[vipwid], wline[i]);
                vipn--;
            }
            else // 如果该顾客不是 VIP
            {
                EnQueue(pw_array[0], wline[i]);
                norn--;
            }
            cnt++;
        }
        else
        {
            if (cnt < wn) // 是 真·第一批人 才用得着
            {
                // 如果此顾客不是VIP但是遍历到了VIP口，且原始队列中还有VIP客户，则直接跳过
                // 当原始队列里已经没有VIP时，普通顾客就可以使用VIP窗口
                if (wline[i].is_vip && vipn != 0) // 是VIP
                {
                    // 由于是第一波人，肯定有空窗口
                    if ((!QueueEmpty(pw_array[vipwid]) && (pw_array[vipwid].rear->data.start_t + pw_array[vipwid].rear->data.during_t + pw_array[vipwid].rear->data.wait_t < wline[i].start_t)) || QueueEmpty(pw_array[vipwid]))
                    // VIP出列时，①VIP窗口曾经有人，且他现在走了；②VIP窗口真空
                    {
                        wline[i].wait_t = 0;
                        wt_array[i] = wline[i].wait_t;
                        sumwt += wline[i].wait_t;
                        endtime[i] = wline[i].start_t + wline[i].wait_t + wline[i].during_t;
                        //printf("%d %d First wave\n", wline[i].start_t, wline[i].during_t);
                        EnQueue(pw_array[vipwid], wline[i]);
                        cnt++;
                        vipn--;
                        continue; // 安排下一位顾客
                    }
                    else // VIP现在有人
                    {
                        int normwid = ElseAvaliable(pw_array, wline[i], wn, vipwid);
                        if (normwid == -1) // 其他窗口全部有人，仍选择 VIP窗口
                        {
                            //wline[i].wait_t = ;<<<<<<<<<
                            wt_array[i] = wline[i].wait_t;
                            sumwt += wline[i].wait_t;
                            endtime[i] = wline[i].start_t + wline[i].wait_t + wline[i].during_t;
                            //printf("%d %d First wave\n", wline[i].start_t, wline[i].during_t);
                            EnQueue(pw_array[vipwid], wline[i]);
                            cnt++;
                            vipn--;
                            continue; // 安排下一位顾客
                        }
                        else    // 找到了其他空闲的普通窗口
                        {
                            wline[i].wait_t = 0;
                            wt_array[i] = wline[i].wait_t;
                            sumwt += wline[i].wait_t;
                            endtime[i] = wline[i].start_t + wline[i].wait_t + wline[i].during_t;
                            //printf("%d %d First wave\n", wline[i].start_t, wline[i].during_t);
                            EnQueue(pw_array[normwid], wline[i]);
                            cnt++;
                            vipn--;
                            continue; // 安排下一位顾客
                        }
                    }
                }
                else
                {
                    for (int j = 0; j < wn; j++)
                    {
                        if ((!QueueEmpty(pw_array[j]) && (pw_array[j].rear->data.start_t + pw_array[j].rear->data.during_t + pw_array[j].rear->data.wait_t < wline[i].start_t)) || QueueEmpty(pw_array[j])) //①该队列曾经有人，但他现在已经走了；②该队列是“真空”的（从未有人来过）
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
            }
            // 遍历整个窗口

            else // 不是 真·第一批人
            {
                int flag = 0;                // 先安排顾客到空闲窗口
                for (int j = 0; j < wn; j++) // 按照序号，顾客优先去窗口号小的窗口
                {
                    QNode *perear = pw_array[j].rear;
                    if (perear->data.start_t + perear->data.during_t + perear->data.wait_t < wline[i].start_t) // 当前所查找队列的最后一个顾客的完成时间点比后来者的开始时间点要早（实际为空）
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
                    for (int j = 0; j < wn; j++) // 按照序号，顾客优先去窗口号小的窗口
                    {
                        QNode *perear = pw_array[j].rear;
                        rear_array[k].id = j;
                        rear_array[k].wait_t = perear->data.start_t + perear->data.during_t + perear->data.wait_t - wline[i].start_t;
                        k++;
                    } //printf("%d>>>>\n", rear_array[0].wait_t);
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
    double aver = (sumwt * 1.0) / (cn * 1.0);
    sort(endtime, endtime + cn, Big);

    printf("%.1lf %d %d\n", aver, wt_array[0], endtime[0]);

    for (int i = 0; i < wn; i++)
    {
        if (i == 0)
            printf("%d", pw_array[i].length);
        else
            printf(" %d", pw_array[i].length);
    }

    return 0;
}
