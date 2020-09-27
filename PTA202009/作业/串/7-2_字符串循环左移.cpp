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
    char data;      // 顾客数据集
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
Status EnQueue(LinkQueue &Q, char &c)
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
Status DeQueue(LinkQueue &Q, char &c)
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
Status GetHead(const LinkQueue &Q, char &c)
{
    if (Q.front->next == NULL)
        return ERROR;
    c = Q.front->next->data;
    return OK;
}


int main()
{
    int n = 0;
    char ch = 0;
    LinkQueue str;
    InitQueue(str);
    while((ch = getchar())!='\n')
    {
        EnQueue(str, ch);
    }
    scanf("%d", &n);

    for(int i = 0; i< n; i++)
    {
        char tt = 0;
        DeQueue(str, tt);
        EnQueue(str, tt);
    }

    int slen = QueueLength(str);
    for(int i = 0; i< slen; i++)
    {
        char tt = 0;
        DeQueue(str, tt);
        printf("%c", tt);
    }

    return 0;
}


/* 
7-2 字符串循环左移 (20分)
输入一个字符串和一个非负整数N，要求将字符串循环左移N次。

输入格式：
输入在第1行中给出一个不超过100个字符长度的、以回车结束的非空字符串；第2行给出非负整数N。

输出格式：
在一行中输出循环左移N次后的字符串。

输入样例：
Hello World!
2
输出样例：
llo World!He 
*/
