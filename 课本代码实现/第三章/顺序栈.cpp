#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>

#define TRUE        1
#define FALSE       0
#define OK          1
#define ERROR       0
#define INFEASIBLE -1
#define OVERFLOW   -2

#define STACK_INIT_CAPACITY  100
#define STACKINCREASEMENT     10

typedef char SElemType;
typedef int Status;

// 顺序栈结构的定义
typedef struct SqStack
{
    int  stack_capacity;
    int  stack_size;
    SElemType *base;
    SElemType *top;
}SqStack;

// 构造一个空栈
Status InitStack (SqStack &sqs)
{
    sqs.base = (SElemType*)malloc(STACK_INIT_CAPACITY* sizeof(SElemType));
    if(!(sqs.base)) exit(OVERFLOW);
    sqs.top = sqs.base;
    sqs.stack_capacity = STACK_INIT_CAPACITY;
    sqs.stack_size = 0;
    return OK;
}// InitStack

// 判断栈是否为空
Status IsEmpty (const SqStack &sqs)
{
    if(sqs.stack_size == 0) return TRUE;
    else return FALSE;
}// IsEmpty

// 返回栈中元素的个数
Status Size (const SqStack &sqs)
{
    return sqs.stack_size;
}// Size

// 返回栈的最大容量
Status Capacity (const SqStack &sqs)
{
    return sqs.stack_capacity;
}// Capacity


// 读栈顶（前提非空）
Status GetTop (const SqStack &sqs, SElemType &value)
{
    if(IsEmpty(sqs))    return ERROR;
    value = *(sqs.top - 1);
    return OK;
}// GetTop

// 压栈
Status Push (SqStack &sqs, SElemType value)
{
    if(Size(sqs) >= Capacity(sqs))  // 考虑栈满的情况
    {
        SElemType *tt;
        tt = (SElemType*)realloc(sqs.base, (sqs.stack_size + STACKINCREASEMENT)* sizeof(SElemType));
        if(!tt) exit(OVERFLOW);
        sqs.base = tt;
        sqs.stack_capacity = sqs.stack_size + STACKINCREASEMENT;    // Size(sqs) >= Capacity(sqs)
        sqs.top = sqs.base + sqs.stack_size;    // Robust
    }
    *(sqs.top) = value; // sqs.top 指向栈顶元素的后一位
    ++(sqs.top);    
    ++(sqs.stack_size); // 栈中元素个数增加 1
    return OK;
}// Push

// 删栈顶
Status Pop (SqStack &sqs, SElemType &value)
{
    if(Size(sqs) == 0) return ERROR;
    value = *(--sqs.top);
    return OK;
}