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
    if(!T) exit(OVERFLOW);              //如果存储空间分配失败，返回 OVERFLOW，中断进程
    T[0] = v1, T[1] = v2, T[2] = v3;
    return OK;
}// InitTriplet

//销毁三元组
Status DestroyTriplet(Triplet &T)
{
    free(T);
    T = NULL;
    return OK;
}// DestroyTriplet

//获取三元组中第 i 个元素的值
Status GetValue(const Triplet T, int i, int &ans)
{
    if(!(i >= 1 && i <= 3)) return ERROR;
    ans = T[i - 1];
    return OK;
}// GetValue

Status PutValue(Triplet &T, int i, int a)
{
    if(!(i >= 1 && i <= 3)) return ERROR;
    T[i - 1] = a;
    return OK;
}// PutValue





int main()
{
    Triplet tp;
    int     ans;
    InitTriplet(tp, 11, 14, 28);
    printf("The data which used a regular way to access is : %d.\n", *(tp+1));    //访问第二个元素
    if(GetValue(tp, 3, ans))
        printf("(Using function to access the data) : %d.\n", ans);
    if(PutValue(tp, 3, 2001))
        printf("The 3rd element which has been edited is : %d.\n", tp[2]);
    DestroyTriplet(tp);

    return 0;
}