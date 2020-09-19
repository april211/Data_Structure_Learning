#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Elem
{
    int coefficient;
    int exponent;
} Elem;

typedef struct Multi
{
    Elem *head;
    int len;
} Multi;

int InitMulti(Multi &L, int len)
{
    L.head = (Elem *)malloc(len * sizeof(Elem));
    if (!L.head)
        return 0;
    L.len = len;
    return 1;
}

int AppendMulti(Multi &L, const Elem &e)
{
    Elem *n = (Elem *)realloc(L.head, (L.len + 1) * sizeof(Elem));
    if (!n)
        return 0;
    L.head = n;
    L.len++;
    L.head[L.len - 1].exponent = e.exponent;
    L.head[L.len - 1].coefficient = e.coefficient;
    return 1;
}

int main()
{
    int c, e;
    Multi l1;
    l1.len = 0;
    l1.head = NULL;
    while (1)
    {
        scanf("%d%d", &c, &e);
        Elem tt;
        tt.exponent = 0, tt.coefficient = 0;
        if (e != 0) // 指数不是零
        {
            tt.coefficient = c * e;
            tt.exponent = e - 1;
            AppendMulti(l1, tt);
        }
        if (getchar() == '\n')
            break;
    }

    if (!l1.head) // 零多项式的情况，有两个数据点
    {
        printf("0 0");
    }
    else
    {
        for (int i = 0; i < l1.len; i++)
        {
            if (i == 0)
                printf("%d %d", l1.head[i].coefficient, l1.head[i].exponent);
            else
                printf(" %d %d", l1.head[i].coefficient, l1.head[i].exponent);
        }
    }

    free(l1.head);
    return 0;
}


/* 7-1 一元多项式求导 (20分)
设计函数求一元多项式的导数。

输入格式:
以指数递降方式输入多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。

输出格式:
以与输入相同的格式输出导数多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。

输入样例:
3 4 -5 2 6 1 -2 0
输出样例:
12 3 -10 1 6 0
作者
DS课程组
单位
浙江大学
代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB */
