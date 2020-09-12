//库函数头文件包含
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

//函数状态码定义
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType; //假设线性表中的元素均为整型

typedef struct LNode
{
    ElemType data;
    struct LNode *tail;
    struct LNode *next;
} LNode, *LinkList;

// 初始化一个带有头节点的链表
Status ListInit_L(LinkList &L)
{
    L = (LNode*)malloc(sizeof(LNode));
    if (!L) exit(OVERFLOW);
    L->next = NULL;
    L->tail = L;
    return OK;
}

void ListPrint_L(LinkList &L)
{
    LNode *p = L->next;
    if(!p)
        printf("NULL");
    while (p != NULL)
    {
        if (p->next != NULL)
            printf("%d ", p->data);
        else
            printf("%d", p->data);
        p = p->next;
    }
}

LNode* GetLast(const LinkList &L)
{
    return L->tail;
}

int Append (LinkList &L, ElemType value)
{
    LNode *llast = GetLast(L), *newnode;
    newnode = (LNode*)malloc(sizeof(LNode));
    if(!newnode)    exit(OVERFLOW);
    newnode->data = value;
    newnode->next = NULL;
    llast->next = newnode;
    L->tail = newnode;
    return OK;
}

// 若存在指定值的元素，返回该节点。否则返回 NULL
LNode* inList(const LinkList &L, int value)
{
    LNode *pt = L->next;
    while(pt)
    {
        if(pt->data == value)
            return pt;
        else
            pt = pt->next;
    }
    if(pt == NULL)
        return NULL;
}

void ListIntersection_L(const LinkList &L1, const LinkList &L2, LinkList &L3)
{
    LNode *p1 = L1->next, *p2 = L2->next, *p3 = L3;
    while(p1 && p2)
    {
        if(p1->data == p2->data)
        {
            Append(L3, p1->data);
            p1 = p1->next;
            p2 = p2->next;
            p3 = p3->next;
        }
        else if(p1->data > p2->data)
        {
            p2 = p2->next;
        }
        else
        {
            p1 = p1->next;
        }
    }
}

int main()
{
    LinkList L1, L2;
    ListInit_L(L1);
    ListInit_L(L2);
    int n = 0;
    scanf("%d", &n);
    while (n != -1)
    {
        Append(L1, n);
        scanf("%d", &n);
    }
    scanf("%d", &n);
    while (n != -1)
    {
        Append(L2, n);
        scanf("%d", &n);
    }
    LinkList L3;
    ListInit_L(L3);
    ListIntersection_L(L1, L2, L3);
    ListPrint_L(L3);

    return 0;
}

/* 
7-2 两个有序链表序列的交集 (20分)
已知两个非降序链表序列S1与S2，设计函数构造出S1与S2的交集新链表S3。

输入格式:
输入分两行，分别在每行给出由若干个正整数构成的非降序序列，用−1表示序列的结尾（−1不属于这个序列）。数字用空格间隔。

输出格式:
在一行中输出两个输入序列的交集序列，数字间用空格分开，结尾不能有多余空格；若新链表为空，输出NULL。

输入样例:
1 2 5 -1
2 4 5 8 10 -1
输出样例:
2 5
作者
DS课程组
单位
浙江大学
代码长度限制
16 KB
时间限制
1000 ms
内存限制
64 MB
 */
