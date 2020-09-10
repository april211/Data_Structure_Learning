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
