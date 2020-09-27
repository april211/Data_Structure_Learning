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

typedef char SElemType;
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

int main()
{
    SqStack match;
    InitStack(match);
/*     printf("%d<<<<\n", IsEmpty(match)); */
    char code[500], exam[120];
    memset(code, 0, sizeof(code));
    memset(exam, 0, sizeof(exam));
    int exlen = 0;
    // 以行的形式读取代码字符串，并存入暂存数组
    while (1)
    {
        cin.getline(code, 500); // 按照行进行输入
        int len = strlen(code);
        if (len == 1 && code[0] == '.')
            break; // 输入点 + 空行结束输入
        for (int i = 0; i < len; i++)
        {
            if (code[i] == '(' || code[i] == ')' || code[i] == '[' || code[i] == ']' || code[i] == '{' || code[i] == '}')
            {
                exam[exlen++] = code[i];
            }
            else if ((i <= len - 2) && (code[i] == '/') && (code[i + 1] == '*'))
            {
                exam[exlen++] = code[i++];
                exam[exlen++] = code[i];
            }
            else if ((i <= len - 2) && code[i] == '*' && code[i + 1] == '/')
            {
                exam[exlen++] = code[i++];
                exam[exlen++] = code[i];
            }
        }
        memset(code, 0, sizeof(code));
    } // 这里已经从输入中获取了全部的合法检测字符

/*     printf("%s\n", exam);
    printf("Exlen: %d\n", exlen);
 */
    // 入栈、初步检测
    int flag = 0;
    for (int i = 0; i < exlen; i++)
    {

        if (exam[i] == '(' || exam[i] == '{' || exam[i] == '[')
        {
            Push(match, exam[i]);
        }
        else if (exam[i] == ')' && GetTop(match) == '(')
        {
            Pop(match);
        }
        else if (exam[i] == ')' && GetTop(match) != '(' && !IsEmpty(match))
        {
            ++flag;
            printf("NO\n");
            char c = *(match.top - 1);
            if (c == '*')
            {
                printf("/*-?");
            }
            else
            {
                printf("%c-?", c);
            }
            break;
        }
        else if (exam[i] == ')' && IsEmpty(match))
        {
            ++flag;
            printf("NO\n");
            printf("?-)");
            break;
        }
        else if (exam[i] == ']' && GetTop(match) == '[')
        {
            Pop(match);
        }
        else if (exam[i] == ']' && GetTop(match) != '[' && !IsEmpty(match))
        {
            ++flag;
            /*             printf("%d----\n", IsEmpty(match));
            printf("%c----\n", GetTop(match)); */
            printf("NO\n");
            char c = *(match.top - 1);
            if (c == '*')
            {
                printf("/*-?");
            }
            else
            {
                printf("%c-?", c);
            }
            break;
        }
        else if (exam[i] == ']' && IsEmpty(match))
        {
            ++flag;
            printf("NO\n");
            printf("?-]");
            break;
        }
        else if (exam[i] == '}' && GetTop(match) == '{')
        {
            Pop(match);
        }
        else if (exam[i] == '}' && GetTop(match) != '{' && !IsEmpty(match))
        {
            ++flag;
            printf("NO\n");
            char c = *(match.top - 1);
            if (c == '*')
            {
                printf("/*-?");
            }
            else
            {
                printf("%c-?", c);
            }
            break;
        }
        else if (exam[i] == '}' && IsEmpty(match))
        {
            ++flag;
            printf("NO\n");
            printf("?-}");
            break;
        }
        else if ((i <= exlen - 2) && (exam[i] == '/') && (exam[i + 1] == '*'))
        {
            Push(match, exam[i++]);
            Push(match, exam[i]);
            //printf("----------\n");
        }
        else if ((i <= exlen - 2) && (exam[i] == '*') && (exam[i + 1] == '/'))
        {
            char latter;
            Pop(match, latter);
            if ((!IsEmpty(match)) && (GetTop(match) == '/') && (latter == '*'))
            {
                Pop(match);
                ++i;
            }
            else if (!IsEmpty(match))
            {
                ++flag;
                printf("NO\n");
                char c = latter;
                printf("%c-?", c);
                break;
            }
            else if (IsEmpty(match))
            {
                //printf("----------");
                ++flag;
                printf("NO\n");
                printf("?-*/");
                break;
            }
        }
    }
    //printf("----------\n");
    //printf("%d", flag);

    if (IsEmpty(match) && flag == 0) // flag == 0
    {
        /*         printf("%d<<<<\n", IsEmpty(match));
        printf("%c----\n", GetTop(match)); */
        printf("YES");
    }
    else if (!IsEmpty(match) && flag == 0)
    {
        printf("NO\n");
        char c = *(match.base);
        if (c == '/')
        {
            printf("/*-?");
        }
        else
        {
            printf("%c-?", c);
        }
    }

    return 0;
}


/* 
7-3 符号配对 (20分)
请编写程序检查C语言源程序中下列符号是否配对：/*与*/ //、(与)、[与]、{与}。

/* 输入格式:
输入为一个C语言源程序。当读到某一行中只有一个句点.和一个回车的时候，标志着输入结束。程序中需要检查配对的符号不超过100个。

输出格式:
首先，如果所有符号配对正确，则在第一行中输出YES，否则输出NO。然后在第二行中指出第一个不配对的符号：如果缺少左符号，则输出?-右符号；如果缺少右符号，则输出左符号-?。
 */
//输入样例1：
//void test()
//{
//    int i, A[10];
//    for (i=0; i<10; i++) /*/
//        A[i] = i;
//}
//.

//输出样例1：
//NO
/*-?
输入样例2：
void test()
{
    int i, A[10];
    for (i=0; i<10; i++) /**/
//        A[i] = i;
//}]
//.

//输出样例2：
//NO
//?-]
//输入样例3：
//void test()
//{
//    int i
//    double A[10];
//    for (i=0; i<10; i++) /**/
//        A[i] = 0.1*i;
//}
//.

//输出样例3：
//YES