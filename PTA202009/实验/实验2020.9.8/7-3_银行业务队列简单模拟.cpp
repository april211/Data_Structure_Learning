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