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
    struct LNode *next;
} LNode, *LinkList; //循环单链表类型定义与单链表定义相同，区别在尾节点next取值

Status ListCreate_CL(LinkList &CL);

void ListDelete_CL(LinkList &CL, ElemType min, ElemType max);

void ListPrint_CL(LinkList &CL)
{                        //输出单链表,空表时输出Empty List。
    LNode *p = CL->next; //p指向第一个元素结点
    if (p == CL)
    {
        printf("Empty List");
        return;
    }
    while (p != CL)
    {
        if (p->next != CL)
            printf("%d ", p->data);
        else
            printf("%d", p->data);
        p = p->next;
    }
}
int main()
{
    LinkList CL;
    ElemType min, max;
    if (ListCreate_CL(CL) != OK)
    {
        printf("循环链表创建失败！！！\n");
        return -1;
    }
        //ListPrint_CL(CL);
        //printf("\n");
    scanf("%d%d", &min, &max);
    ListDelete_CL(CL, min, max);
    ListPrint_CL(CL);
    return 0;
}

Status ListCreate_CL(LinkList &CL)
{
    int n = 0;
    scanf("%d", &n);
    CL = (LNode *)malloc(sizeof(LNode));
    if (!CL)
        exit(OVERFLOW);
    CL->next = CL;
    LNode *pt = CL;
    for (int i = 0; i < n; i++)
    {
        int value = 0;
        scanf("%d", &value);
        LNode* newnode = (LNode *)malloc(sizeof(LNode));
        if (!newnode)
            exit(OVERFLOW);
        newnode->data = value;
        newnode->next = CL;
        pt->next = newnode;
        pt = pt->next;
    }
    return OK;
}

void ListDelete_CL(LinkList &CL, ElemType min, ElemType max)
{
    LNode *pt = CL;
    while (pt->next != CL)
    {
        if (pt->next->data > min && pt->next->data < max)
        {
            LNode *pn = pt->next;
            pt->next = pn->next;
            free(pn);
        }
        else
        {
            pt = pt->next;
        }
    }
}


/* 
6-1 循环单链表区间删除 (15分)
本题要求实现带头结点的循环单链表的创建和单链表的区间删除。L是一个带头结点的循环单链表，函数ListCreate_CL用于创建一个循环单链表，函数ListDelete_CL用于删除取值大于min小于max的链表元素。

函数接口定义：
    Status ListCreate_CL(LinkList &CL); 
    void ListDelete_CL(LinkList &CL,ElemType min,ElemType max);
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
}LNode,*LinkList; //循环单链表类型定义与单链表定义相同，区别在尾节点next取值

Status ListCreate_CL(LinkList &CL);  

void ListDelete_CL(LinkList &CL, ElemType min, ElemType max);

void ListPrint_CL(LinkList &CL) 
{   //输出单链表,空表时输出Empty List。 
    LNode *p=CL->next;  //p指向第一个元素结点
    if(p==CL){
      printf("Empty List");
      return;
    }
    while(p!=CL)  
    {   
        if(p->next!=CL)
            printf("%d ",p->data);   
        else
            printf("%d",p->data);      
        p=p->next; 
    } 
}    
int main() 
{  
    LinkList CL;
    ElemType min,max;
    if(ListCreate_CL(CL)!= OK) 
    {
       printf("循环链表创建失败！！！\n");
       return -1;
    }
    scanf("%d%d",&min,&max);    
    ListDelete_CL(CL,min,max);   
    ListPrint_CL(CL);  	
    return 0;
}

输入格式： 第一行输入一个整数n，表示循环单链表中元素个数，接下来一行共n个整数，中间用空格隔开。第三行输入min和max。

输出格式： 输出删除后循环链表的各个元素，两个元素之间用空格隔开，最后一个元素后面没有空格。

输入样例：

6
1 2 3 4 5 6
2 5
输出样例：

1 2 5 6
 */