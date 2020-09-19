#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *oddhead, *evenhead;
    int *ans;
    int n, odd, even;
    int j = 0, k = 0, len = 0;
    scanf("%d", &n);
    oddhead = (int *)malloc(n * sizeof(int));
    evenhead = (int *)malloc(n * sizeof(int));
    ans = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        int tt;
        scanf("%d", &tt);
        if (tt % 2 == 0) // 输入数据为偶数
        {
            evenhead[j++] = tt; // B
        }
        else // odd
        {
            oddhead[k++] = tt; // A
        }
    }
    if (k % 2 == 0) // 奇数的个数为一个偶数
    {
        k /= 2;
        int i = 0, z = 0, h = 0;
        while (j > 0 && k > 0)
        {
            ans[i++] = oddhead[z++];
            ans[i++] = oddhead[z++];
            ans[i++] = evenhead[h++];
            k--;
            j--;
        }
        while (j > 0)
        {
            ans[i++] = evenhead[h++];
            j--;
        }
        while (k > 0)
        {
            ans[i++] = oddhead[z++];
            ans[i++] = oddhead[z++];
            k--;
        }
        len = i;
    }
    else // 奇数的个数是奇数
    {
        k /= 2, k++;
        int i = 0, z = 0, h = 0;
        while (j > 0 && k > 0)
        {
            if (k == 1)
            {
                ans[i++] = oddhead[z++];
            }
            else
            {
                ans[i++] = oddhead[z++];
                ans[i++] = oddhead[z++];
            }
            ans[i++] = evenhead[h++];
            k--;
            j--;
        }
        while (j > 0)
        {
            ans[i++] = evenhead[h++];
            j--;
        }
        while (k > 0)
        {
            ans[i++] = oddhead[z++];
            ans[i++] = oddhead[z++];
            k--;
        }
        len = i;
    }

    for (int i = 0; i < len; i++)
    {
        if (i == 0)
            printf("%d", ans[i]);
        else
            printf(" %d", ans[i]);
    }
    return 0;
}


/* 7-5 银行业务队列简单模拟 (25分)
设某银行有A、B两个业务窗口，且处理业务的速度不一样，其中A窗口处理速度是B窗口的2倍 —— 即当A窗口每处理完2个顾客时，B窗口处理完1个顾客。给定到达银行的顾客序列，请按业务完成的顺序输出顾客序列。假定不考虑顾客先后到达的时间间隔，并且当不同窗口同时处理完2个顾客时，A窗口顾客优先输出。

输入格式:
输入为一行正整数，其中第1个数字N(≤1000)为顾客总数，后面跟着N位顾客的编号。编号为奇数的顾客需要到A窗口办理业务，为偶数的顾客则去B窗口。数字间以空格分隔。

输出格式:
按业务处理完成的顺序输出顾客的编号。数字间以空格分隔，但最后一个编号后不能有多余的空格。

输入样例:
8 2 1 3 9 4 11 13 15
输出样例:
1 3 2 9 11 4 13 15 */