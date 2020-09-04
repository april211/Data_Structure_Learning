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

//顺序表的存储结构定义
#define LIST_INIT_SIZE  100
#define LISTINCREMENT   10
typedef int ElemType;  //假设线性表中的元素均为整型
typedef struct{
    ElemType* elem;   //存储空间基地址
    int length;       //表中元素的个数
    int listsize;     //表容量大小
}SqList;    //顺序表类型定义
Status ListInsert_Sq(SqList &L, int pos, ElemType e);
Status ListDelete_Sq(SqList &L, int pos, ElemType &e);
int ListLocate_Sq(SqList L, ElemType e);
void ListPrint_Sq(SqList L);

//结构初始化与销毁操作
Status InitList_Sq(SqList &L){
  //初始化L为一个空的有序顺序表
    L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem)exit(OVERFLOW);
    L.listsize=LIST_INIT_SIZE;
    L.length=0;
    return OK;
}


int main() {
    SqList L;

    if(InitList_Sq(L)!= OK) {
        printf("InitList_Sq: 初始化失败！！！\n");
        return -1;
    }

    for(int i = 1; i <= 10; ++ i)
        ListInsert_Sq(L, i, i);

    int operationNumber;  //操作次数
    scanf("%d", &operationNumber);

    while(operationNumber != 0) {
        int operationType;  //操作种类
        scanf("%d", & operationType);

        if(operationType == 1) {  //增加操作
            int pos, elem;
            scanf("%d%d", &pos, &elem);
            ListInsert_Sq(L, pos, elem);
        } else if(operationType == 2) {  //删除操作
             int pos; ElemType elem;
             scanf("%d", &pos);
             ListDelete_Sq(L, pos, elem);
             printf("%d\n", elem);
        } else if(operationType == 3) {  //查找定位操作
            ElemType elem;
            scanf("%d", &elem);
            int pos = ListLocate_Sq(L, elem);
            if(pos >= 1 && pos <= L.length)
                printf("%d\n", pos);
            else
                printf("NOT FIND!\n");
        } else if(operationType == 4) {  //输出操作
            ListPrint_Sq(L);
        }
       operationNumber--;
    }
    return 0;
}

// 在顺序线性表中插入元素
Status ListInsert_Sq (SqList &L, int pos, ElemType value)
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

// 从线性表中删除一个元素
Status ListDelete_Sq (SqList &L, int pos, ElemType &value)
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

// 定位元素
int ListLocate_Sq (SqList L, ElemType value)
{
    if(L.elem == NULL)   return ERROR;
    int i = 1, len = L.length;
    int *pt = L.elem;
    while(i <= len && !(*pt++ == value))       //优先级：*x >> x++。注意不要越界
    {
        i++;
    }
    if(i <= len)    return i;                   
    else            return 0;                   //如果不存在符合条件的元素，i 的值会超过 len 的值
}// ListLocate_Sq

// 输出顺序表元素
void ListPrint_Sq(SqList L)
{
    int len = L.length;
    for(int i = 0; i < len; i++)
    {
        if(i == 0)
            printf("%d", L.elem[i]);
        else
        {
            printf("%c%d", ' ', L.elem[i]);
        }
    }
    //printf("\n");
}// ListPrint_Sq
