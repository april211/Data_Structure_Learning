#include <cstdio>
#include <cstdlib>

// 单向链表的简单实现

// 函数所返回的错误代码
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define LIST_INIT_SIZE  100
#define LISTINCREMENT   10
// 函数返回的状态值
typedef int  Status;

// 假设线性表中的元素均为整型
typedef int  ElemType;

// 节点类型
typedef struct LNode    
{
    ElemType      data;
    struct LNode *next;
}LNode, *Link, *Position;            

// 链表类型
typedef struct          
{
    // 分别指向线性链表的头结点和尾结点
    Link head, tail;  

    // 记录线性链表中结点的数目
    int  len;           
}LinkList;

// 分配由 p 指向的值为 value 的结点，并返回 OK ；若分配失败，则返回 ERROR 
Status MakeNode (Link &p, ElemType value);

// 释放 p 所指向的结点
void   FreeNode (Link &p);

// 构造一个空的线性链表
Status InitList (LinkList &L);

// 销毁线性链表 L ，L不再存在
Status DestroyList (LinkList &L);

// 将线性链表 L 重置为空表，并释放原链表的结点空间
Status ClearList (LinkList &L);

// 已知 h 指向线性链表的头结点，将 s 所指结点插入在第一个结点之前
Status InsFirst (Link h, Link s);

// 已知 h 指向线性链表的头结点，删除链表中的第一个结点并以 q 返回
Status DelFirst (Link h, Link &q);

// 将指针 s 所指（彼此以指针相链）的一串结点链接在线性链表 L 的最后一个结点之后，并改变链表 L 的尾指针指向新的尾结点
Status Append (LinkList &L, Link s);

// 删除线性链表 L 中的尾结点并以 q 返回，改变链表 L 的尾指针指向新的尾结点
Status Remove (LinkList &L, Link &q);

// 已知 p 指向线性链表 L 中的一个结点，将 s 所指的结点插入在 p 所指结点之前，并修改指针 p 指向新插入的结点
Status InsBefore (LinkList &L, Link &p, Link s);

// 已知 p 指向线性链表 L 中的一个结点，将 s 所指的结点插入在 p 所指结点之后，并修改指针 p 指向新插入的结点
Status InsAfter (LinkList &L, Link &p, Link s);

// 已知 p 指向线性链表中的一个结点，用 value 更新 p 所指结点中数据元素的值
Status SetCurElem (Link &p, ElemType value);

// 已知 p 指向线性链表中的一个结点，返回 p 所指向的结点中数据元素的值
ElemType GetCurElem (Link p);

// 若线性链表 L 为空表，则返回 TRUE，否则返回 FALSE
Status ListEmpty (LinkList L);

// 返回线性链表 L 中元素的个数
int ListLength (LinkList L);

// 返回线性链表 L 中头结点的位置
Position GetHead (LinkList L);

// 返回线性链表 L 中尾结点的位置
Position GetLast (LinkList L);

// 已知 p 指向线性链表 L 中的一个结点，返回 p 所指结点的直接前驱的位置，若无前驱，则返回 NULL
Position PriorPos (LinkList L, Link p);

// 已知 p 指向线性链表 L 中的一个结点，返回 p 所指结点的直接后继的位置，若无后继，则返回 NULL
Position NextPos (LinkList L, Link p);

// 返回 p 指示的线性链表 L 中第 i 个结点的位置并返回 OK ，i 值不合法时返回 ERROR
Status LocatePos (LinkList L, int i, Link &p);

// 返回线性链表 L 中 第 1 个与 value 满足函数 compare() 判定关系的元素的位置，若不存在这样的元素，则返回 NULL
Position LocateElem (LinkList L, ElemType value, Status (*compare)(ElemType, ElemType));

// 依次对 L 的每个元素调用函数 visit() 。一旦 visit() 调用失败，则操作失败
Status ListTraverse (LinkList L, Status (*visit)());


int main()
{
    LinkList mylist;
    LNode *n1 = NULL;
    int value = 11;
    MakeNode(n1, value);
    FreeNode(n1);
    


    return 0;
}

Status MakeNode (Link &p, ElemType value)
{
    p = (LNode*)malloc(sizeof(LNode));
    if(!p) exit(OVERFLOW);
    p->data = value;
    p->next = NULL;
    return OK;
}

Status InitList (LinkList &L)
{
    L.head = (LNode*)malloc(sizeof(LNode));
    if(!L.head) exit(OVERFLOW);
    L.tail = L.head;
    L.len = 0;
    return OK;
}

void   FreeNode (Link &p)
{
    free(p);
    p = NULL;
}

Status Append (LinkList &L, Link s)
{
    // L.tail = s->




}
