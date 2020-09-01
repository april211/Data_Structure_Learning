#include <cstdio>
#include <cstdlib>

//函数所返回的错误代码
#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2

typedef int *Triplet;   //指向整型的指针
typedef int  Status;    //函数返回的状态值

//初始化三元组
Status InitTriplet(Triplet &T, int v1, int v2, int v3)
{
    T = (int*)malloc(3* sizeof(int));
    if(!T) exit(OVERFLOW);      //如果存储空间分配失败，返回 OVERFLOW
    T[0] = v1, T[1] = v2, T[2] = v3;
    return OK;
}

int main()
{
    Triplet tp;
    InitTriplet(tp, 11, 14, 28);
    printf("%d\n", tp[0]);



    return 0;
}