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

// 顺序表的存储结构定义
typedef struct{
    int* elem;          
    int  length;       
    int  listsize;    
}SqList;

// 顺序表初始化函数
Status InitList_Sq(SqList &L, int n)
{
    L.elem = (int*)malloc(n* sizeof(int));
    if(!L.elem)  exit(OVERFLOW);
    L.length = 0;
    L.listsize = n;
    return OK;
}

// 删除顺序表中指定数据范围内的元素
Status DeleteEle(SqList &L, int x, int y)
{
    if(L.length == 0)   return OK;
    int len = L.length;
    SqList rel;
    if(InitList_Sq(rel, len))
    {
        int *p1 = L.elem, *p2 = L.elem + L.length -1, *p3 = rel.elem;
        while(p1 <= p2)
        {
            if(!(*p1 >= x && *p1 <= y))
            {
                *p3 = *p1;
                p3++;
                rel.length++;
            }
            p1++;
        }
        L = rel;
        return OK;
    }
    else
    {
        return ERROR;
    }
}

int main()
{
    SqList L;
    int  n = 0;
    int  x = 0, y = 0;
    scanf("%d", &n);
    InitList_Sq(L, n);

    for(int i = 0; i < n; i++)
    {
        int e = 0;
	    scanf("%d", &e);//输入数据
        L.elem[i] = e;
        L.length++;
    }

    scanf("%d%d", &x, &y);
    DeleteEle(L, x, y);
    int newlen = L.length;
    for(int i = 0; i< newlen; i++)
    {
        if(i == 0)
            printf("%d", L.elem[i]);
        else
            printf(" %d", L.elem[i]);
    }

    return  0;
}



/* 7-2 jmu-ds-顺序表区间元素删除 (15分)
若一个线性表L采用顺序存储结构存储，其中所有的元素为整数。设计一个算法，删除元素值在[x,y]之间的所有元素，要求算法的时间复杂度为O(n)，空间复杂度为O(1)。

输入格式:
三行数据，第一行是顺序表的元素个数，第二行是顺序表的元素，第三行是x和y。

输出格式:
删除元素值在[x,y]之间的所有元素后的顺序表。

输入样例:
10
5 1 9 10 67 12 8 33 6 2
3 10

输出样例:
1 67 12 33 2 */
