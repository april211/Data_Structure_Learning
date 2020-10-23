#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

List Read();        /* 细节在此不表 */
void Print(List L); /* 细节在此不表；空链表将输出NULL */

List Merge(List L1, List L2);

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}


// L1 和 L2 是给定的带头结点的单链表，其结点存储的数据是递增有序的；
// 函数 Merge 要将 L1 和 L2 合并为一个非递减的整数序列。
// 应直接使用原序列中的结点，返回归并后的带头结点的链表头指针。


List Merge(List L1, List L2)
{
    struct Node *pt_l1 = L1->Next;  // 越过头结点
    struct Node *pt_l2 = L2->Next;
    List  ans = (PtrToNode)malloc(sizeof(struct Node));               // 初始化答案链表（头结点）
    ans->Next = NULL;
    ans->Data = -1;
    struct Node *pt_ans = ans;      // 指向头结点
    while(pt_l1 && pt_l2)
    {
        struct Node* newnpt = (PtrToNode)malloc(sizeof(struct Node));
        if(pt_l1->Data > pt_l2->Data)
        {
            newnpt->Data = pt_l2->Data;
            pt_l2 = pt_l2->Next;
        }
        else
        {
            newnpt->Data = pt_l1->Data;
            pt_l1 = pt_l1->Next;
        }
        newnpt->Next = NULL;
        pt_ans->Next = newnpt;
        pt_ans = pt_ans->Next;
    }

    //pt_ans->Next = (pt_l1 != NULL)?pt_l1:pt_l2;

    while(pt_l1)
    {
        struct Node* newnpt = (PtrToNode)malloc(sizeof(struct Node));
        newnpt->Data = pt_l1->Data;
        newnpt->Next = NULL;
        pt_l1 = pt_l1->Next;
        pt_ans->Next = newnpt;
        pt_ans = pt_ans->Next;
    }

    while(pt_l2)
    {
        struct Node* newnpt = (PtrToNode)malloc(sizeof(struct Node));
        newnpt->Data = pt_l2->Data;
        newnpt->Next = NULL;
        pt_l2 = pt_l2->Next;
        pt_ans->Next = newnpt;
        pt_ans = pt_ans->Next;
    }

    L1->Next = NULL;
    L2->Next = NULL;
    return ans;
}


/* 
6-1 两个有序链表序列的合并 (25分)
本题要求实现一个函数，将两个链表表示的递增整数序列合并为一个非递减的整数序列。

函数接口定义：
List Merge( List L1, List L2 );
其中List结构定义如下：

typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;  存储结点数据 
    PtrToNode   Next;  指向下一个结点的指针 
};
typedef PtrToNode List;  定义单链表类型 
L1和L2是给定的带头结点的单链表，其结点存储的数据是递增有序的；函数Merge要将L1和L2合并为一个非递减的整数序列。应直接使用原序列中的结点，返回归并后的带头结点的链表头指针。

裁判测试程序样例：
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read();  细节在此不表 
void Print( List L );  细节在此不表；空链表将输出NULL 

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    L2 = Read();
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

 你的代码将被嵌在这里 
输入样例：
3
1 3 5
5
2 4 6 8 10
输出样例：
1 2 3 4 5 6 8 10 
NULL
NULL
 */

