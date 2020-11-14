#include <algorithm>
#include <cstdio>
#include <iostream>

#define MAX_SIZE 106

int num[MAX_SIZE] = {0};

int main()
{
    // 第 1行中给出 N和 K（1 ≤ K < N ≤ 100），在第 2行中给出 N个待排序的整数，数字间以空格分隔
    int N = 0, K = 0;
    scanf("%d%d", &N, &K);

    for (int i = 0; i < N; i++)
    {
        scanf("%d", &(num[i]));
    }

    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (num[j] > num[j + 1])
            {
                int temp = num[j];
                num[j] = num[j + 1];
                num[j + 1] = temp;
            }
        }
        if (i == K - 1)
        {
            for (int i = 0; i < N; i++)
            {
                if (i == 0)
                    printf("%d", num[i]);
                else
                    printf(" %d", num[i]);
            }
            break;
        }
    }

    return 0;
}


/* 7-3 冒泡法排序 (20分)
将N个整数按从小到大排序的冒泡排序法是这样工作的：从头到尾比较相邻两个元素，如果前面的元素大于其紧随的后面元素，则交换它们。通过一遍扫描，则最后一个元素必定是最大的元素。然后用同样的方法对前N−1个元素进行第二遍扫描。依此类推，最后只需处理两个元素，就完成了对N个数的排序。

本题要求对任意给定的K（<N），输出扫描完第K遍后的中间结果数列。

输入格式：
输入在第1行中给出N和K（1≤K<N≤100），在第2行中给出N个待排序的整数，数字间以空格分隔。

输出格式：
在一行中输出冒泡排序法扫描完第K遍后的中间结果数列，数字间以空格分隔，但末尾不得有多余空格。

输入样例：
6 2
2 3 5 1 6 4
输出样例：
2 1 3 4 5 6 */
