#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define INFEASIBLE -1

#define STACK_INIT_CAPACITY 100
#define STACKINCREASEMENT 10

typedef int SElemType;
typedef int Status;

// 顺序栈结构的定义
typedef struct SqStack
{
    int stack_capacity;
    int stack_size;
    SElemType *base;
    SElemType *top;
} SqStack;

// 构造一个空栈
Status InitStack(SqStack &sqs)
{
    sqs.base = (SElemType *)malloc(STACK_INIT_CAPACITY * sizeof(SElemType));
    if (!(sqs.base))
        exit(OVERFLOW);
    sqs.top = sqs.base;
    sqs.stack_capacity = STACK_INIT_CAPACITY;
    sqs.stack_size = 0;
    return OK;
} // InitStack

// 判断栈是否为空
Status IsEmpty(const SqStack &sqs)
{
    if (sqs.stack_size == 0)
        return TRUE;
    else
        return FALSE;
} // IsEmpty

// 返回栈中元素的个数
Status Size(const SqStack &sqs)
{
    return sqs.stack_size;
} // Size

// 返回栈的最大容量
Status Capacity(const SqStack &sqs)
{
    return sqs.stack_capacity;
} // Capacity

// 读栈顶（前提非空）
SElemType GetTop(const SqStack &sqs)
{
    if (IsEmpty(sqs))
        return 0;
    SElemType value;
    value = *(sqs.top - 1);
    return value;
} // GetTop

// 压栈
Status Push(SqStack &sqs, SElemType value)
{
    //printf("PUSH\n");
    if (Size(sqs) >= Capacity(sqs)) // 考虑栈满的情况
    {
        SElemType *tt;
        tt = (SElemType *)realloc(sqs.base, (sqs.stack_size + STACKINCREASEMENT) * sizeof(SElemType));
        if (!tt)
            exit(OVERFLOW);
        sqs.base = tt;
        sqs.stack_capacity = sqs.stack_size + STACKINCREASEMENT; // Size(sqs) >= Capacity(sqs)
        sqs.top = sqs.base + sqs.stack_size;                     // Robust
    }
    *(sqs.top) = value; // sqs.top 指向栈顶元素的后一位
    ++(sqs.top);
    ++(sqs.stack_size); // 栈中元素个数增加 1
    return OK;
} // Push

// 删栈顶
Status Pop(SqStack &sqs, SElemType &value)
{
    if (Size(sqs) == 0)
        return ERROR;
    value = *(--sqs.top);
    --(sqs.stack_size);
    //printf("Size: %d<<<<\n", sqs.stack_size);
    return OK;
}

// 删栈顶
Status Pop(SqStack &sqs)
{
    if (Size(sqs) == 0)
        return ERROR;
    --sqs.top;
    --(sqs.stack_size);
    //printf("Size: %d<<<<\n", sqs.stack_size);
    return OK;
}

bool Smaller(int x, int y)
{
    return x > y;
}

bool Bigger(int x, int y)
{
    return x > y;
}

int main()
{
    int N = 0, cost = 0;
    SqStack wood_sec;
    InitStack(wood_sec);
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        int tt = 0;
        scanf("%d", &tt);
        Push(wood_sec, tt);
    }                                               // 输入结束
    sort(wood_sec.base, wood_sec.base + N, Bigger); // 小的排在栈顶附近

    if (N == 1)
    {
        printf("%d", 0);    //不花钱
        return 0;
    }
    else
    {
        int sm1 = 0, sm2 = 0;
        Pop(wood_sec, sm1);
        Pop(wood_sec, sm2);
        cost += sm1 + sm2;
        Push(wood_sec, sm1 + sm2);
        sort(wood_sec.base, wood_sec.base + N - 1, Bigger); // 小的排在栈顶附近

        int decrease = 1; // 比较原初的元素损失个数
        while (wood_sec.stack_size != 0)
        {
            if (wood_sec.stack_size == 1) // 取不出两个来（不用比较）
            {
                Pop(wood_sec);
                decrease++;
            }
            else
            {
                int ttsm1 = 0, ttsm2 = 0, tt = 0;
                Pop(wood_sec, ttsm1);
                Pop(wood_sec, ttsm2);
                tt = ttsm1 + ttsm2;
                cost += tt;
                Push(wood_sec, tt);
                decrease++;
                sort(wood_sec.base, wood_sec.base + N - decrease, Bigger); // 小的排在栈顶附近
            }
        }

        printf("%d", cost);
    }

    return 0;
}