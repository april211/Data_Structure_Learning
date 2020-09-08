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

//顺序表的存储结构定义
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int ElemType; //假设线性表中的元素均为整型
typedef struct
{
    ElemType *elem; //存储空间基地址
    int length;     //表中元素的个数
    int listsize;   //表容量大小
} SqList;           //顺序表类型定义

Status ListCreate_Sq(SqList &L);
void ListReverse_Sq(SqList &L);

int main()
{
    SqList L;
    ElemType *p;

    if (ListCreate_Sq(L) != OK)
    {
        printf("ListCreate_Sq: 创建失败！！！\n");
        return -1;
    }

    ListReverse_Sq(L);

    if (L.length)
    {
        for (p = L.elem; p < L.elem + L.length - 1; ++p)
        {
            printf("%d ", *p);
        }
        printf("%d", *p);
    }
    return 0;
}
/* 请在这里填写答案 */

Status ListCreate_Sq(SqList &L)
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!L.elem)
        return ERROR;
    else
    {
        int n = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            int tt;
            scanf("%d", &tt);
            L.elem[i] = tt;
        }
        L.length = n;
        L.listsize = LIST_INIT_SIZE;
        return OK;
    }
}

void ListReverse_Sq(SqList &L)
{
    ElemType *p1 = L.elem;
    ElemType *p2 = L.elem + L.length - 1;
    while (p1 < p2)
    {
        int tt;
        tt = *p1;
        *p1 = *p2;
        *p2 = tt;
        p1++;
        p2--;
    }
}


/* 
6-1 顺序表创建和就地逆置 (10分)
本题要求实现顺序表的创建和就地逆置操作函数。L是一个顺序表，函数ListCreate_Sq(SqList &L)用于创建一个顺序表，函数ListReverse_Sq(SqList &L)是在不引入辅助数组的前提下将顺序表中的元素进行逆置，如原顺序表元素依次为1,2,3,4，则逆置后为4,3,2,1。

函数接口定义：
Status ListCreate_Sq(SqList &L);
void ListReverse_Sq(SqList &L);
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

//顺序表的存储结构定义
#define LIST_INIT_SIZE  100
#define LISTINCREMENT   10
typedef int ElemType;  //假设线性表中的元素均为整型
typedef struct{
    ElemType* elem;   //存储空间基地址
    int length;       //表中元素的个数
    int listsize;     //表容量大小
}SqList;    //顺序表类型定义

Status ListCreate_Sq(SqList &L);
void ListReverse_Sq(SqList &L);

int main() {
    SqList L;
    ElemType *p;

    if(ListCreate_Sq(L)!= OK) {
        printf("ListCreate_Sq: 创建失败！！！\n");
        return -1;
    }

    ListReverse_Sq(L);

    if(L.length){
	for(p=L.elem;p<L.elem+L.length-1;++p){
	    printf("%d ",*p);
	}
	printf("%d",*p); 
    }
    return 0;
}



输入格式： 第一行输入一个整数n，表示顺序表中元素个数，接下来n个整数为表元素，中间用空格隔开。 输出格式： 输出逆置后顺序表的各个元素，两个元素之间用空格隔开，最后一个元素后面没有空格。

输入样例：
4
1 2 3 4

输出样例：
4 3 2 1 */
