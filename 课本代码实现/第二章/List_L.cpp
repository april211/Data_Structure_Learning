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

    // 在表的属性中记录线性链表中结点的数目，而不是在头结点中
    int  len;
}LinkList;  // "Link" 在计算机中表示链环，即链表的组成元素。"LinkList" 即表示 “链式表”

// 分配由 pt 指向的值为 value 的结点，并返回 OK ；若分配失败，则返回 ERROR 
Status MakeNode (Link &pt, ElemType value);

// 释放 pt 所指向的结点
void   FreeNode (Link &pt);

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

// 已知 pt 指向线性链表 L 中的一个结点，将 s 所指的结点插入在 pt 所指结点之前，并修改指针 pt 指向新插入的结点
Status InsBefore (LinkList &L, Link &pt, Link s);

// 已知 pt 指向线性链表 L 中的一个结点，将 s 所指的结点插入在 pt 所指结点之后，并修改指针 pt 指向新插入的结点
Status InsAfter (LinkList &L, Link &pt, Link s);

// 已知 pt 指向线性链表中的一个结点，用 value 更新 pt 所指结点中数据元素的值
Status SetCurElem (Link &pt, ElemType value);

// 已知 pt 指向线性链表中的一个结点，返回 pt 所指向的结点中数据元素的值
ElemType GetCurElem (Link pt);

// 若线性链表 L 为空表，则返回 TRUE，否则返回 FALSE
Status ListEmpty (LinkList L);

// 返回线性链表 L 中元素的个数
int ListLength (const LinkList &L);

// 返回由 pt 所指向的·一串普通链环·中·节点 (LNode)·的个数
int ListLength (const Link &pt);

// 返回线性链表 L 中·头结点·的·位置·
Position GetHead (const LinkList &L);

// 返回由 pt 所指向的·一串普通链环·中·的第一个节点
Position GetHead (const Link &pt);

// 返回线性链表 L 中·第一个元素结点·的·位置·（注意与 GetHead 区分）
Position GetFirst (const LinkList &L);

// 返回线性链表 L 中尾结点的·位置·
Position GetLast (const LinkList &L);

// 返回由 pt 所指向的·一串普通链环·中·的最后一个节点
Position GetLast (const Link &pt);

// 已知 pt 指向线性链表 L 中的一个结点，返回 pt 所指结点的直接前驱的位置，若无前驱，则返回 NULL
Position PriorPos (const LinkList &L, const Link &pt);

// 已知 pt 指向线性链表 L 中的一个结点，返回 pt 所指结点的直接后继的位置，若无后继，则返回 NULL
Position NextPos (const LinkList &L, const Link &pt);

// 返回 pt 指示的线性链表 L 中第 i 个结点的·position·并返回 OK ，i 值不合法时返回 ERROR
Status LocatePos (const LinkList &L, int i, const Link &pt, Position &pos);

// 返回线性链表 L 中 第 1 个与 value 满足函数 compare() 判定关系的元素的·位置·，若不存在这样的元素，则返回 NULL
Position LocateElem (const LinkList &L, ElemType value, Status (*compare)(ElemType, ElemType));

// 依次对 L 的每个元素调用函数 visit() 。一旦 visit() 调用失败，则操作失败
Status ListTraverse (const LinkList &L, Status (*visit)());

// 获取指定位置的结点存储的数据值
Status GetValue (const LinkList &L, int i, int &ans);

int main()
{
    LinkList lista;
    Link n1 = NULL;
    int value = 11;
    MakeNode(n1, value);
    FreeNode(n1);
    


    return 0;
}

Status MakeNode (Link &pt, ElemType value)
{
    // 仅对创建的节点中的值与指针进行修改，且该节点中的指针将被赋值为 NULL
    pt = (LNode*)malloc(sizeof(LNode));
    if(!pt) exit(OVERFLOW);
    pt->data = value;
    pt->next = NULL;
    return OK;
}

Status InitList (LinkList &L)
{
    // 需要无条件制造一个头结点。该头节点并不是 “第一个元素”，不计入链表的总长度中
    L.head = (LNode*)malloc(sizeof(LNode));
    if(!L.head) exit(OVERFLOW);
    L.tail = L.head;
    L.len = 0;
    L.head->next = NULL;
    return OK;
}

void FreeNode (Link &pt)
{
    free(pt);
    pt = NULL;
}

int ListLength (const LinkList &L)
{
    return L.len;
}

int ListLength (const Link &pt)
{
    if(!pt) return 0;
    int  len = 0;   // 头结点不算入
    Link pp = pt;
    while(pp->next)
    {
        pp = pp->next;
        ++len;
    }
    return len;
}

Status GetValue (const LinkList &L, int i, int &ans)
{
    if(L.len == 0 || i<=0 || i>L.len)    return ERROR;  // 如果此链表是一个空表，或者所指定的位置为非法值，返回 ERROR
    Link p1 = GetHead(L);         // 指向头结点，而不是第一个元素
    p1 = p1->next;                // 指向第一个元素
    int cnt = 1;
    while(cnt != i)
    {
        p1 = p1->next;
        ++cnt;
    }
    ans = p1->data;
    return OK;
}

Position GetHead (const LinkList &L)
{
    return L.head;
}

Position GetHead (const Link &pt)
{
    return pt;
}

Position GetFirst (const LinkList &L)
{
    return L.head->next;
}

Position GetLast (const Link &pt)
{
    Link pp = pt;
    while(pp->next)
    {
        pp = pp->next;
    }
    return pp;
}

Position GetLast (const LinkList &L)
{
    return L.tail;
}

Status Append (LinkList &L, Link s)
{
    int slen = ListLength(s);
    if(slen == 0)   return ERROR;
    Link slast = GetLast(s), shead = GetHead(s);
    Link llast = GetLast(L);
    llast->next = shead;
    L.tail = slast;
    slast->next = NULL;
    L.len += slen;
    return OK;
}

Status DestroyList (LinkList &L)
{
    
}
