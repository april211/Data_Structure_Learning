//库函数头文件包含
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

//函数状态码定义
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2

typedef int  Status;
typedef int  ElemType; //假设线性表中的元素均为整型

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

Status ListCreate_L(LinkList &L,int n)
{
    LNode *rearPtr,*curPtr;   //一个尾指针，一个指向新节点的指针
    L=(LNode*)malloc(sizeof (LNode));
    if(!L)exit(OVERFLOW);
    L->next=NULL;               //先建立一个带头结点的单链表
    rearPtr=L;  //初始时头结点为尾节点,rearPtr指向尾巴节点
    for (int i=1;i<=n;i++){  //每次循环都开辟一个新节点，并把新节点拼到尾节点后
        curPtr=(LNode*)malloc(sizeof(LNode));//生成新结点
        if(!curPtr)exit(OVERFLOW);
        scanf("%d",&curPtr->data);//输入元素值
        curPtr->next=NULL;  //最后一个节点的next赋空
        rearPtr->next=curPtr;
        rearPtr=curPtr;
    }
    return OK;
}
void ListReverse_L(LinkList &L);
void ListPrint_L(LinkList &L){
//输出单链表
    LNode *p=L->next;  //p指向第一个元素结点
    while(p!=NULL)
    {
          if(p->next!=NULL)
               printf("%d ",p->data);
          else
               printf("%d",p->data);
          p=p->next;
    }
}
int main()
{
    LinkList L;
    int n;
    scanf("%d",&n);
    if(ListCreate_L(L,n)!= OK) {
          printf("表创建失败！！！\n");
          return -1;
    }
    ListReverse_L(L);
    ListPrint_L(L);
    return 0;
}

void ListReverse_L(LinkList &L)
{
    LNode *pt1 = L->next, *pt2 = L->next, *pt3 = L->next; // 将三个节点指针指向链表的第一个元素链环
    LNode *oldhead = L, *oldtail, *oldfirst = L->next;
    oldtail = oldhead; // 为了寻找原链表的尾结点，先赋值为头结点
    int len = 0;
    while (oldtail->next)
    {
        oldtail = oldtail->next; // 循环找到原尾结点
        len++;
    }
    L->next = oldtail;          // 将头结点的下一个结点修改为原链表的尾结点
    if (len == 1)
    {
        return;
    }
    else
    {
        pt2 = pt2->next;
        while (pt2 != oldtail)
        {
            pt3 = pt2->next;
            pt2->next = pt1;
            pt1 = pt2;
            pt2 = pt3;
        }
        pt2->next = pt1;
        oldfirst->next = NULL;
    }
}


/* 
6-1 带头结点的单链表就地逆置 (10分)
本题要求编写函数实现带头结点的单链线性表的就地逆置操作函数。L是一个带头结点的单链表，函数ListReverse_L(LinkList &L)要求在不新开辟节点的前提下将单链表中的元素进行逆置，如原单链表元素依次为1,2,3,4，则逆置后为4,3,2,1。

函数接口定义：
void ListReverse_L(LinkList &L);
其中 L 是一个带头结点的单链表。

裁判测试程序样例：
//库函数头文件包含
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

//函数状态码定义
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2

typedef int  Status;
typedef int  ElemType; //假设线性表中的元素均为整型

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

Status ListCreate_L(LinkList &L,int n)
{
    LNode *rearPtr,*curPtr;   //一个尾指针，一个指向新节点的指针
    L=(LNode*)malloc(sizeof (LNode));
    if(!L)exit(OVERFLOW);
    L->next=NULL;               //先建立一个带头结点的单链表
    rearPtr=L;  //初始时头结点为尾节点,rearPtr指向尾巴节点
    for (int i=1;i<=n;i++){  //每次循环都开辟一个新节点，并把新节点拼到尾节点后
        curPtr=(LNode*)malloc(sizeof(LNode));//生成新结点
        if(!curPtr)exit(OVERFLOW);
        scanf("%d",&curPtr->data);//输入元素值
        curPtr->next=NULL;  //最后一个节点的next赋空
        rearPtr->next=curPtr;
        rearPtr=curPtr;
    }
    return OK;
}
void ListReverse_L(LinkList &L);
void ListPrint_L(LinkList &L){
//输出单链表
    LNode *p=L->next;  //p指向第一个元素结点
    while(p!=NULL)
    {
          if(p->next!=NULL)
               printf("%d ",p->data);
          else
               printf("%d",p->data);
          p=p->next;
    }
}
int main()
{
    LinkList L;
    int n;
    scanf("%d",&n);
    if(ListCreate_L(L,n)!= OK) {
          printf("表创建失败！！！\n");
          return -1;
    }
    ListReverse_L(L);
    ListPrint_L(L);
    return 0;
}

输入格式：

第一行输入一个整数n，表示单链表中元素个数，接下来一行共n个整数，中间用空格隔开。

输出格式：

输出逆置后顺序表的各个元素，两个元素之间用空格隔开，最后一个元素后面没有空格。

输入样例：
4
1 2 3 4
输出样例：
4 3 2 1
作者
鲁法明
单位
浙江大学
代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB
 */
