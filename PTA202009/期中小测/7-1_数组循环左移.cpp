#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

#define MAXS 120
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW -2
#define INFEASIBLE -1

typedef int Status;

// 队列的结点之类型
typedef struct QNode
{
    int data;           // 数据域
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
Status EnQueue(LinkQueue &Q, int &c)
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
Status DeQueue(LinkQueue &Q, int &c)
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
Status GetHead(const LinkQueue &Q, int &c)
{
    if (Q.front->next == NULL)
        return ERROR;
    c = Q.front->next->data;
    return OK;
}


int main()
{
    int n = 0, m = 0;   // n个整数，左移 m 位

    LinkQueue str;
    InitQueue(str);

    scanf("%d%d", &n, &m);

    for(int i = 0; i< n; i++)
    {
        int tt = 0;
        scanf("%d", &tt);
        EnQueue(str, tt);
    }

    for(int i = 0; i< m; i++)
    {
        int tt = 0;
        DeQueue(str, tt);
        EnQueue(str, tt);
    }

    int slen = QueueLength(str);
    for(int i = 0; i< slen; i++)
    {
        int tt = 0;
        DeQueue(str, tt);

        if(i == 0)
            printf("%d", tt);
        else
            printf(" %d", tt);
            
    }

    return 0;
}




/* 
7-1 数组循环左移 (25分)
本题要求实现一个对数组进行循环左移的简单函数：一个数组a中存有n（>0）个整数，在不允许使用另外数组的前提下，将每个整数循环向左移m（≥0）个位置，即将a中的数据由（a
​0
​​ a
​1
​​ ⋯a
​n−1
​​ ）变换为（a
​m
​​ ⋯a
​n−1
​​ a
​0
​​ a
​1
​​ ⋯a
​m−1
​​ ）（最前面的m个数循环移至最后面的m个位置）。如果还需要考虑程序移动数据的次数尽量少，要如何设计移动的方法？

输入格式:
输入第1行给出正整数n（≤100）和整数m（≥0）；第2行给出n个整数，其间以空格分隔。

输出格式:
在一行中输出循环左移m位以后的整数序列，之间用空格分隔，序列结尾不能有多余空格。

输入样例：
8 3
1 2 3 4 5 6 7 8
输出样例：
4 5 6 7 8 1 2 3 */
