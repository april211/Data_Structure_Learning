#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>

#define ERROR -1
#define OK     1
typedef int Status;
using namespace std;

bool compare_s(int a, int b)
{
    return a>b;
}

int main()
{
    int sum = 0, n = 0;
    int *rm = NULL;
    scanf("%d%d", &sum, &n);
    rm = (int*)malloc(sum*sizeof(int));
    for(int i = 0; i< sum; i++)
    {
        int tt = 0;
        scanf("%d", &tt);
        rm[i] = tt;
    }// 输入完成



	sort(rm, rm + sum, compare_s);
    // 排序完成

    if(sum == 0)
    {
        printf("\n");
    }
    else if(n > sum)
    {
        for(int i = 0; i< sum; i++)
        {
            if(i == 0)
                printf("%d", rm[i]);
            else
                printf(" %d", rm[i]);
        }

    }
    else
    {
        for(int i = 0; i< n; i++)
        {
            if(i == 0)
                printf("%d", rm[i]);
            else
                printf(" %d", rm[i]);
        }
    }




    return 0;
}


//7-17 寻找大富翁 (25分)
//胡润研究院的调查显示，截至2017年底，中国个人资产超过1亿元的高净值人群达15万人。假设给出N个人的个人资产值，请快速找出资产排前M位的大富翁。
//
//输入格式:
//输入首先给出两个正整数N（≤10
//​6
//​​ ）和M（≤10），其中N为总人数，M为需要找出的大富翁数；接下来一行给出N个人的个人资产值，以百万元为单位，为不超过长整型范围的整数。数字间以空格分隔。
//
//输出格式:
//在一行内按非递增顺序输出资产排前M位的大富翁的个人资产值。数字间以空格分隔，但结尾不得有多余空格。
//
//输入样例:
//8 3
//8 12 7 3 20 9 5 18
//输出样例:
//20 18 12
