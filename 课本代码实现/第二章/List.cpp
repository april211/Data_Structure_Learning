#include <cstdio>
#include <cstdlib>

// 函数所返回的错误代码
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2

typedef int  Status;    // 函数返回的状态值
typedef int *List;      // 指向整型的指针

// 初始化线性表
Status InitList (List &L, int len = 0, int value = 0)
{
    if(len == 0) L = NULL;  // 指定长度为 0 时，建立一个空表
    else                    // 指定长度不是 0 时，建立一个长度为 len 的线性表，并将所有元素赋值为 value 的值
    {
        L = (int*)malloc(len* sizeof(int));
        if(!L) exit(OVERFLOW);
        for(int i = 0; i< len; i++)
        {
            L[i] = value;
        }
    }
    return OK;
}// InitList

// 销毁线性表
Status DestroyList (List &L)
{
    if(L != NULL)
    {
        free(L);
        L = NULL;
        return OK;
    }
    else
    {
        return ERROR;
    }
}// DestroyList

// 将线性表重置为空表
Status ClearList (List &L)
{
    if(DestroyList(L)) return OK;
    else               return ERROR;
}// ClearList

// 判断线性表是否为空
Status IsEmpty (const List &L)
{
    if(L == NULL) return TRUE;
    else          return FALSE;
}// IsEmpty

// 返回线性表元素的个数
int ListLength (const List &L)
{
    if(IsEmpty(L))      // 不加这句的话，当线性表为空时，将返回 -1
        return 0;
    else
        return (_msize(L) / sizeof(int));
}// ListLength

// 获取线性表中第 i 个位置的数据元素的值 value
Status GetElem (const List &L, int i, int &value)
{
    if(L == NULL)   
        return ERROR;
    else
    {
        value = L[i - 1];
        return OK;
    }
}// GetElem

// 将所给的值 'a' 放入三元组的指定位置 'i' 处。若表为空或者超出表的长度范围，则返回错误代码
Status SetValue (List &L, int i, int value)
{
    if((L == NULL) || (i < 0) || (i > ListLength(L)))
        return ERROR;
    else
    {
        L[i - 1] = value;
        return OK;
    }
}// PutValue

// 返回表中第一个与 a 满足关系 compare 的数据元素的位序（从 1 开始）。若这样的数据元素不存在，则返回值为 0。
int LocateElem (const List &L, int a, Status (*compare)(int, int))
{
    if(L == NULL)   return ERROR;
    int i = 1, len = ListLength(L);
    int *pt = L;
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
Status PriorElem (const List &L, int cur, int &pre)
{
    if(L == NULL)   return ERROR;
    int location = LocateElem(L, cur, Equal);    //返回了位置
    if(location && location != 1)
    {
        pre = L[location - 2];
        return OK;
    }
    else
    {
        return ERROR;
    }
}// PriorElem

// 获得某个元素的后继（需要指定该元素的值，且只能寻找到第一个出现的元素）
Status NextElem (const List &L, int cur, int &next)
{
    if(L == NULL)   return ERROR;
    int location = LocateElem(L, cur, Equal);    //返回了位置
    if(location && location != ListLength(L))
    {
        next = L[location];
        return OK;
    }
    else
    {
        return ERROR;
    }
}// PriorElem

// 在顺序线性表中插入元素
Status ListInsert (List &L, int i, int value)
{
    int prelen = ListLength(L);         // 线性表在插入元素之前的长度
    int aftlen = prelen + 1;            // 线性表在插入元素之后的长度
    if(L == NULL || i < 1 ||( i > (prelen + 1)))   return ERROR;
    int *aftlist = (int*)realloc(L, aftlen* sizeof(int));
    if(!aftlist)   exit(OVERFLOW);      // 若分配失败，原指针也不会失效
    L = aftlist;
    int *ptstill = &(L[i - 1]);         // 设立目标位置指针（静止）
    for(int *ptmove = &(L[prelen - 1]); ptmove >= ptstill; ptmove--)
    {
        *(ptmove + 1) = *ptmove;        // 从原线性表的最后一个元素开始，依次向后移动
    }
    *ptstill = value;                   // 在最终空出来的位置写入新值（目标值）
    return OK;                          // 插入成功
}// ListInsert

// 打印出线性表中所有元素的值。可以自定义间隔符
Status PrintAll (const List& L, char spacer)
{
    if(!L)  return ERROR;
    int len = ListLength(L);
    for(int i = 0; i < len; i++)
    {
        if(i == 0)
            printf("%d", L[i]);
        else
        {
            printf("%c%d", spacer, L[i]);
        }
    }
    printf("\n");
    return OK;
}// PrintAll

int main()
{
    List lp;
    int  ans = 0;
    Status (*equal)(int, int) = Equal;              // 定义一个函数指针。该指针使用函数 Equal 来赋值
    Status (*smaller)(int, int) = Smaller;          // 定义一个函数指针。该指针使用函数 Smaller 来赋值    
    Status (*bigger)(int, int) = Bigger;            // 定义一个函数指针。该指针使用函数 Bigger 来赋值    

    InitList(lp, 10, 8);                            // 初始化一个线性表
    SetValue(lp, 2, 11);                            // 将第二个元素的值设置为 11
    SetValue(lp, 3, 14);
    SetValue(lp, 4, 28);
    SetValue(lp, 10, 444);
    if(IsEmpty(lp))                                 // 判断一下这个表是不是空的 
        printf("This list is empty.\n");
    PrintAll(lp, ' ');
    printf("The length of this list is : %d.\n", ListLength(lp));
    if(GetElem(lp, 3, ans))                         // 获取第三个元素的值
        printf("The third element's value of this list is : %d.\n", ans);
    printf("The 2nd element's value of this list is : %d.\n", lp[1]);

    //使用定位函数，结合函数指针来获得符合条件的元素的位序
    printf("The location of the first \"11\" is : %d.\n", LocateElem(lp, 11, equal));

    if(PriorElem(lp, 14, ans))  
        printf("The value of the element which before the first \"14\" is : %d.\n", ans);
    if(NextElem(lp, 14, ans))  
        printf("The value of the element which after the first \"14\" is : %d.\n", ans);    

    if(ListInsert(lp, 1, 999))
        printf("Now the first element's value is : %d.\n", lp[0]);
    printf("Now we have %d element(s).\n", ListLength(lp));

    PrintAll(lp, ' ');


    DestroyList(lp);                                // 销毁该线性表


    return 0;
}