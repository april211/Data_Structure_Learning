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

//函数声明
Status ListInsert_SortedSq(SqList &L, ElemType e);

//顺序表初始化函数
Status InitList_Sq(SqList &L)
{
    //开辟一段空间
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    //检测开辟是否成功
    if(!L.elem){
        exit(OVERFLOW);
    }
    //赋值
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;

    return OK;
}

//顺序表输出函数
void ListPrint_Sq(SqList L)
{
    ElemType *p = L.elem;//遍历元素用的指针

	
    for(int i = 0; i < L.length; ++i){
        if(i == L.length - 1){
            printf("%d", *(p+i));
        }
        else{
            printf("%d ", *(p+i));
        }
    }
}
int main()
{
    //声明一个顺序表
    SqList L;
    //初始化顺序表
    InitList_Sq(L);

    int number = 0;
    ElemType e;

     scanf("%d", &number);//插入数据的个数 

    for(int i = 0; i < number; ++i)
    {
	scanf("%d", &e);//输入数据
        ListInsert_SortedSq(L, e);
    }

    ListPrint_Sq(L);

    return  0;
}


/* 请在这里填写答案 */

Status ListInsert_SortedSq(SqList &L, ElemType e)
{
    if(!L.elem) return ERROR;
    if(L.length >= L.listsize)
    {
        ElemType *rel = (ElemType*)realloc(L.elem, (LISTINCREMENT + L.listsize)* sizeof(ElemType));
        if(!rel) return ERROR;
        L.elem = rel;
        L.listsize += LISTINCREMENT;
    }
    if(L.length == 0)
    {
        L.elem[0] = e;
        L.length++;
        return OK;
    }
    ElemType *p1 = L.elem;
    ElemType *p2 = L.elem + L.length - 1;
    while(*p1 < e)
    {
        p1++;
        if(p2+1 == p1)  break;  // p1 已经移动到了 p2 的后一个位置（超过了 length）， 此时 p2 < p1
    }// 现在 p1 已经指到了将要插入的位置
    while((p2 >= p1))
    {
        *(p2+1) = *p2;
        p2--;
    }
    *p1 = e;
    L.length++;

    return OK;
}


/* 
6-2 有序顺序表的插入 (10分)
本题要求实现递增顺序表的有序插入函数。L是一个递增的有序顺序表，函数Status ListInsert_SortedSq(SqList &L, ElemType e)用于向顺序表中按递增的顺序插入一个数据。 比如：原数据有：2 5，要插入一个元素3，那么插入后顺序表为2 3 5。 要考虑扩容的问题。

函数接口定义：
Status ListInsert_SortedSq(SqList &L, ElemType e);
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

//函数声明
Status ListInsert_SortedSq(SqList &L, ElemType e);

//顺序表初始化函数
Status InitList_Sq(SqList &L)
{
    //开辟一段空间
    L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    //检测开辟是否成功
    if(!L.elem){
        exit(OVERFLOW);
    }
    //赋值
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;

    return OK;
}

//顺序表输出函数
void ListPrint_Sq(SqList L)
{
    ElemType *p = L.elem;//遍历元素用的指针

	
    for(int i = 0; i < L.length; ++i){
        if(i == L.length - 1){
            printf("%d", *(p+i));
        }
        else{
            printf("%d ", *(p+i));
        }
    }
}
int main()
{
    //声明一个顺序表
    SqList L;
    //初始化顺序表
    InitList_Sq(L);

    int number = 0;
    ElemType e;

     scanf("%d", &number);//插入数据的个数 

    for(int i = 0; i < number; ++i)
    {
	scanf("%d", &e);//输入数据
        ListInsert_SortedSq(L, e);
    }

    ListPrint_Sq(L);

    return  0;
}



输入格式： 第一行输入接下来要插入的数字的个数 第二行输入数字 输出格式： 输出插入之后的数字

输入样例：
5
2 3 9 8 4

输出样例：
2 3 4 8 9

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
