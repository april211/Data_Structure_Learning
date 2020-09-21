#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW -2
#define INFEASIBLE -1

#define STACKINCREASEMENT 10
#define STACK_INIT_CAPACITY 100

typedef char SElemType;
typedef int  Status;

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
    return OK;
}

// 删栈顶
Status Pop(SqStack &sqs)
{
    if (Size(sqs) == 0)
        return ERROR;
    --sqs.top;
    --(sqs.stack_size);
    return OK;
}

// 检测单个字符是否属于十进制数字的一部分
bool isNum(char c)
{
    if (c == '.' || (c >= '0' && c <= '9')) return true;    // 小数点也要算
    else return false;
}

bool isOperator(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/')    return true;
    else return false;
}

void prespace(bool flag)
{ //前导空格
    if (flag) printf(" ");
}

int Priority(char op)
{
    if(op == '*' || op == '/') return 2;
    else if(op == '+' || op == '-') return 1;
    else return 0;
}

int main()
{
    SqStack sk;
    InitStack(sk);
    char formula[50];
    bool flag = false;
    memset(formula, 0, sizeof(formula));
    
    cin.getline(formula, 50);
    int flen = strlen(formula);

    for (int i = 0; i< flen;)
    {
        if (formula[i] == '+' || formula[i] == '-')
        {
            if (i == 0)
            {
                if (formula[i] == '-')  // 第一个数字是带负号的 (i == 0)
                {
                    printf("-");
                    flag = true;
                }
                ++i;
                while (isNum(formula[i]))   // 输出多位数（包括小数点）
                {
                    printf("%c", formula[i++]);
                    flag = true;
                }
            }
            else if (formula[i - 1] == '(')// 加一个负数带括号
            {
                prespace(flag);
                if (formula[i] == '-')
                {
                    printf("-");
                    flag = true;
                }
                ++i;
                while (isNum(formula[i]))
                {
                    printf("%c", formula[i++]);
                    flag = true;
                }
            }
            else if (isOperator(formula[i - 1]))
            {
                prespace(flag);
                if (formula[i] == '-')
                {
                    printf("-");
                    flag = true;
                }
                ++i;
                while (isNum(formula[i]))
                {
                    printf("%c", formula[i++]);
                    flag = true;
                }
            }
            else
            {
                while (!IsEmpty(sk) && Priority(GetTop(sk)) >= Priority(formula[i]) && GetTop(sk) != '(')
                {
                    prespace(flag);
                    printf("%c", GetTop(sk));
                    Pop(sk);
                    flag = true;
                }
                Push(sk, formula[i++]);
            }
        }
        else if (formula[i] == '*' || formula[i] == '/')
        {
            while (!IsEmpty(sk) && Priority(GetTop(sk)) >= Priority(formula[i]) && GetTop(sk) != '(')
            {
                prespace(flag);
                printf("%c", GetTop(sk));
                Pop(sk);
                flag = true;
            }
            Push(sk, formula[i++]);
        }
        else if (formula[i] >= '0' && formula[i] <= '9')
        {
            prespace(flag);
            while (isNum(formula[i]))
            {
                printf("%c", formula[i++]);
            }
            flag = true;  //amend
        }
        else if (formula[i] == '(')
        {
            Push(sk, formula[i++]);
        }
        else if (formula[i] == ')')
        {
            while (GetTop(sk) != '(')
            {
                prespace(flag);
                printf("%c", GetTop(sk));
                Pop(sk);
                flag = true;
            }
            Pop(sk);   // 删除左括号
            ++i;
        }
    }
    while (!IsEmpty(sk))
    {
        prespace(flag);
        printf("%c", GetTop(sk));
        Pop(sk);
        flag = true;
    }
    printf("\n");
}
