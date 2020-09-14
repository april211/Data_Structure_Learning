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

int main()
{
    int m, n;
    Multi l1, l2, ans, merge;
    scanf("%d", &m);
    InitMulti(l1, m);
    for (int i = 0; i < m; i++)
    {
        int c, e;
        scanf("%d%d", &c, &e);
        l1.head[i].coefficient = c, l1.head[i].exponent = e;
    }
    scanf("%d", &n);
    InitMulti(l2, n);
    for (int i = 0; i < n; i++)
    {
        int c, e;
        scanf("%d%d", &c, &e);
        l2.head[i].coefficient = c, l2.head[i].exponent = e;
    } // 数据输入完成
    InitMulti(ans, n * m);
    InitMulti(merge, n * m);
    int k = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ans.head[k].coefficient = (l1.head[i].coefficient) * (l2.head[j].coefficient);
            ans.head[k].exponent = (l1.head[i].exponent) + (l2.head[j].exponent);
            k++;
        }
    }

    Elem tt1;
    k = 0;
    merge.len = 0;
    merge.head[0].coefficient = 0;
    merge.head[0].exponent = 0;
    for (int i = l1.head[0].exponent + l2.head[0].exponent; i >= 0; i--)
    {
        tt1.exponent = 0, tt1.coefficient = 0;
        for (int j = 0; j < m * n; j++)
        {
            if (ans.head[j].exponent == i)
            {
                tt1.coefficient += ans.head[j].coefficient;
                tt1.exponent = i;
            }
        }
        if (tt1.coefficient != 0)
        {
            merge.head[k] = tt1;
            merge.len++;
            k++;
        }
    }
    if (merge.head[0].exponent == 0 && merge.head[0].coefficient == 0)
    {
        printf("0 0\n");
    }
    else
    {
        for (int i = 0; i < k; i++)
        {
            if (i == 0)
                printf("%d %d", merge.head[i].coefficient, merge.head[i].exponent);
            else
                printf(" %d %d", merge.head[i].coefficient, merge.head[i].exponent);
        }
        printf("\n");
    } // 乘法部分结束
    free(ans.head);
    free(merge.head);

    InitMulti(ans, m + n);
    InitMulti(merge, m + n);
    k = 0;
    ans.head[0].coefficient = 0, ans.head[0].exponent = 0;
    int maxe = (l1.head[0].exponent > l2.head[0].exponent) ? l1.head[0].exponent : l2.head[0].exponent;
    Elem *p1 = l1.head;
    Elem *p2 = l2.head;
    while ((p1 <= l1.head + l1.len - 1)&&(p2 <= l2.head + l2.len - 1))
    {
        if (p1->exponent > p2->exponent)
        {
            ans.head[k].exponent = p1->exponent;
            ans.head[k].coefficient = p1->coefficient;
            k++;
            p1++;
        }
        else
        {
            ans.head[k].exponent = p2->exponent;
            ans.head[k].coefficient = p2->coefficient;
            k++;
            p2++;
        }
    }
    while (p1 <= l1.head + l1.len - 1)
    {

        ans.head[k].exponent = p1->exponent;
        ans.head[k].coefficient = p1->coefficient;
        k++;
        p1++;
    }
    while (p2 <= l2.head + l2.len - 1)
    {
        ans.head[k].exponent = p2->exponent;
        ans.head[k].coefficient = p2->coefficient;
        k++;
        p2++;
    }
    Elem tt2;
    k = 0;
    merge.len = 0;
    merge.head[0].coefficient = 0;
    merge.head[0].exponent = 0;
    for (int i = maxe; i >= 0; i--)
    {
        tt2.exponent = 0, tt2.coefficient = 0;
        for (int j = 0; j < m + n; j++)
        {
            if (ans.head[j].exponent == i)
            {
                tt2.coefficient += ans.head[j].coefficient;
                tt2.exponent = i;
            }
        }
        if (tt2.coefficient != 0)
        {
            merge.head[k] = tt2;
            merge.len++;
            k++;
        }
    }
    if (merge.head[0].exponent == 0 && merge.head[0].coefficient == 0)
    {
        printf("0 0\n");
    }
    else
    {
        for (int i = 0; i < k; i++)
        {
            if (i == 0)
                printf("%d %d", merge.head[i].coefficient, merge.head[i].exponent);
            else
                printf(" %d %d", merge.head[i].coefficient, merge.head[i].exponent);
        }
    } // 加法部分结束

    free(ans.head);
    free(merge.head);
    return 0;
}


/* 7-1 一元多项式的乘法与加法运算 (20分)
设计函数分别求两个一元多项式的乘积与和。

输入格式:
输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。

输出格式:
输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。零多项式应输出0 0。

输入样例:
4 3 4 -5 2  6 1  -2 0
3 5 20  -7 4  3 1
输出样例:
15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
5 20 -4 4 -5 2 9 1 -2 0 */
