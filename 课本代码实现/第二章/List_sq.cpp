#include <cstdio>
#include <cstdlib>

// 顺序线性表的简单实现

// 函数所返回的错误代码
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2
#define LIST_INIT_SIZE  100
#define LISTINCREMENT   10

typedef int  Status;    // 函数返回的状态值
typedef int  Mode;      // 函数模式参数
typedef int  ElemType;  // 假设线性表中的元素均为整型
typedef struct
{
    ElemType* elem;   // 存储空间基地址
    int length;       // 表中元素的个数
    int listsize;     // 表容量大小
}SqList;              // 顺序表类型定义

// 初始化线性表
Status InitList (SqList &L, int len = LIST_INIT_SIZE, Mode all = 0, int value = 0)
{
    if(len == 0)    
    {
        L.elem = NULL;          // 指定长度为 0 时，建立一个·真·空表
        L.length = 0;
        L.listsize = 0;
    }
    else                        // 指定长度不是 0 时，建立一个长度为 len 的线性表，并将所有元素赋值为 value 的值
    {
        L.elem = (ElemType*)malloc(len* sizeof(ElemType));
        if(!L.elem) exit(OVERFLOW);
        L.listsize = len;

        if(all)                 // 选择初始化模式（附带元素、空）
            L.length = len;
        else
            L.length = 0;

        // 为保无野值，一律赋值（默认为0）
        for(int i = 0; i< len; i++)
        {
            L.elem[i] = value;
        }
    }
    return OK;
}// InitList

// 销毁线性表
Status DestroyList (SqList &L)
{
    if(L.elem != NULL)
    {
        free(L.elem);
        L.elem = NULL;
        return OK;
    }
    else
    {
        return ERROR;
    }
}// DestroyList

// 将线性表重置为空表，原指针仍有效（仅修改参数 length）
Status ClearList (SqList &L)
{
    if(!L.elem)     return ERROR;
    L.length = 0;
    return OK;
}// ClearList

// 判断线性表是否为空
Status IsEmpty (const SqList &L)
{
    if(L.elem == NULL) return ERROR;
    if(L.length == 0)  return TRUE;
    else               return FALSE;
}// IsEmpty

// 返回线性表元素的真实个数
int ListLength (const SqList &L)
{
    return L.length;
/*     if(IsEmpty(L))      // 不加这句的话，当线性表为空时，将返回 -1
        return 0;
    else
        return (_msize(L) / sizeof(int)); */
}// ListLength

// 获取线性表中第 i 个位置的数据元素的值 value
Status GetElem (const SqList &L, int i, int &value)
{
    if(L.elem == NULL)   
        return ERROR;
    else
    {
        value = L.elem[i - 1];
        return OK;
    }
}// GetElem

// 将所给的值 'a' 放入三元组的指定位置 'i' 处。若表为空或者超出表的长度范围，则返回错误代码
Status SetValue (SqList &L, int i, int value)
{
    if((L.elem == NULL) || (i < 0) || (i > ListLength(L)))
        return ERROR;
    else
    {
        L.elem[i - 1] = value;
        return OK;
    }
}// PutValue

// 返回表中第一个与 a 满足关系 compare 的数据元素的位序（从 1 开始）。若这样的数据元素不存在，则返回值为 0。
int LocateElem (const SqList &L, int a, Status (*compare)(int, int))
{
    if(L.elem == NULL)   return ERROR;
    int i = 1, len = ListLength(L);
    int *pt = L.elem;
    while(i <= len && !compare(*pt++, a))       //优先级：*x >> x++。注意不要越界
    {
        i++;
    }
    if(i <= len)    return i;                   
    else            return 0;                   //如果不存在符合条件的元素，i 的值会超过 len 的值
}// LocateElem

// 判断前一个数是否比后一个数大
Status Bigger (int x, int y)
{
    return (x > y)?TRUE:FALSE;
}// Bigger

// 判断前一个数是否比后一个数小
Status Smaller (int x, int y)
{
    return (x < y)?TRUE:FALSE;
}// Smaller

// 判断前一个数是是否等于后一个数
Status Equal (int x, int y)
{
    return (x == y)?TRUE:FALSE;
}// Equal

// 获得某个元素的前驱（需要指定该元素的值，且只能寻找到第一个出现的元素）
Status PriorElem (const SqList &L, int cur, int &pre)
{
    if(L.elem == NULL)   return ERROR;
    int location = LocateElem(L, cur, Equal);    //返回了位置
    if(location && location != 1)
    {
        pre = L.elem[location - 2];
        return OK;
    }
    else
    {
        return ERROR;
    }
}// PriorElem

// 获得某个元素的后继（需要指定该元素的值，且只能寻找到第一个出现的元素）
Status NextElem (const SqList &L, int cur, int &next)
{
    if(L.elem == NULL)   return ERROR;
    int location = LocateElem(L, cur, Equal);    //返回了位置
    if(location && location != ListLength(L))
    {
        next = L.elem[location];
        return OK;
    }
    else
    {
        return ERROR;
    }
}// NextElem

// 在顺序线性表中插入元素
Status ListInsert (SqList &L, int pos, ElemType value)
{
    if(pos < 1 || ( pos > (L.length + 1)))   return ERROR;

    if(L.length >= L.listsize)              // 已分配空间不足，需要重新分配以扩容
    {
        ElemType *aftlist = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT)* sizeof(ElemType));
        if(!aftlist)   exit(OVERFLOW);      // 若分配失败，原指针也不会失效
        L.elem = aftlist;
    }

    int *ptstill = L.elem + pos - 1;    // 设立目标位置指针（静止）
    for(int *ptmove = (L.elem + L.length - 1); ptmove >= ptstill; ptmove--)
    {
        *(ptmove + 1) = *ptmove;        // 从原线性表的最后一个元素开始，依次向后移动
    }
    *ptstill = value;                   // 在最终空出来的位置写入新值（目标值）
    L.length++;
    L.listsize++;
    return OK;                          // 插入成功
}// ListInsert_Sq

// 删除线性表中的第 i 个元素，并用 value 返回其值
Status ListDelete (SqList &L, int pos, ElemType &value)
{
    int prelen = L.length;              // 线性表在删除元素之前的长度
    int aftlen = prelen - 1;            // 线性表在删除元素之后的长度
    if(L.elem == NULL || pos < 1 || pos > prelen)   return ERROR;
    int *pt1 = L.elem + pos - 1;         
    value = *pt1;                       // 把将要删除的元素的值赋给 value  
    pt1++;                              // 移到目标元素的下一个位置，准备覆盖
    for(int *pt2 = L.elem + prelen - 1; pt2 >= pt1; pt1++)
    {
        *(pt1 - 1) = *pt1;
    }
    L.length--;                         // 实际使用元素个数减少 1，原分配空间大小保持不变
    return OK;                          // 删除成功
}// ListDelete_Sq

// 打印出线性表中所有元素的值。可以自定义间隔符
Status PrintAll (const SqList& L, char spacer)
{
    if(!L.elem)  return ERROR;
    int len = ListLength(L);
    for(int i = 0; i < len; i++)
    {
        if(i == 0)
            printf("%d", L.elem[i]);
        else
            printf("%c%d", spacer, L.elem[i]);
    }
    printf("\n");
    return OK;
}// PrintAll

// 访问单个数据元素，并获取它的值
Status Visit (const SqList &L, int i, ElemType &value)
{
    if(!L.elem)  return ERROR;
    else
    {
        value = L.elem[i];
        return OK;
    }
}// Visit


// 顺序遍历、并以空格为间隔符输出线性表
Status ListTraverse (const SqList &L, Status (*visit)(const SqList&, int, int&))
{
    if(!L.elem)  return ERROR;
    int len = ListLength(L);
    for(int i = 0; i< len; i++)
    {
        int ans = 0;
        if((*visit)(L, i, ans))
        {
            if(i == 0)
                printf("%d", ans);
            else
            {
                printf("%c%d", ' ', ans);
            }
        }
        else
        {
            return ERROR;
        }
    }
    printf("\n");
    return OK;
}

int main()
{
    SqList lp;
    int  ans = 0;
    Status (*equal)(int, int) = Equal;              // 定义一个函数指针。该指针使用函数 Equal 来赋值
    Status (*smaller)(int, int) = Smaller;          // 定义一个函数指针。该指针使用函数 Smaller 来赋值    
    Status (*bigger)(int, int) = Bigger;            // 定义一个函数指针。该指针使用函数 Bigger 来赋值    
    Status (*visit)(const SqList&, int, int&) = Visit;

    InitList(lp, 10, TRUE, 8);                      // 初始化一个线性表
    SetValue(lp, 2, 11);                            // 将第二个元素的值设置为 11
    SetValue(lp, 3, 14);
    SetValue(lp, 4, 28);
    SetValue(lp, 10, 444);
    if(IsEmpty(lp))                                 // 判断一下这个表是不是空的 
        printf("This SqList is empty.\n");
    PrintAll(lp, ' ');
    printf("The length of this SqList is : %d.\n", ListLength(lp));
    if(GetElem(lp, 3, ans))                         // 获取第三个元素的值
        printf("The third element's value of this SqList is : %d.\n", ans);
    printf("The 2nd element's value of this SqList is : %d.\n", lp.elem[1]);

    //使用定位函数，结合函数指针来获得符合条件的元素的位序
    printf("The location of the first \"11\" is : %d.\n", LocateElem(lp, 11, equal));

    if(PriorElem(lp, 14, ans))  
        printf("The value of the element which before the first \"14\" is : %d.\n", ans);
    if(NextElem(lp, 14, ans))  
        printf("The value of the element which after the first \"14\" is : %d.\n", ans);    

    if(ListInsert(lp, 1, 999))
        printf("Now the first element's value is : %d.\n", lp.elem[0]);
    printf("Now we have %d element(s).\n", ListLength(lp));
    PrintAll(lp, ' ');
    if(ListDelete(lp, 11, ans))
        printf("A \"%d\" has been deleted.\n", ans);
    printf("Now we have %d element(s).\n", ListLength(lp));
    ListTraverse(lp, visit);

    DestroyList(lp);                                // 销毁该线性表


    return 0;
}