#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;


int main()
{
    int N = 0;
    int cnt = 0;    
    scanf("%d", &N);
    int *train = (int*)malloc(N* sizeof(int));
    int *min = (int*)malloc(N* sizeof(int));

    for(int i = 0; i< N; i++)
    {
        scanf("%d", &train[i]);
        int flag = 0;
        if(cnt == 0 || (cnt > 0 && min[cnt - 1] < train[i]))    // 保持有序
        {
            min[cnt++] = train[i];
        }
        else    //cnt != 0 && min[cnt - 1] > train[i]     （不可能相等）
        {
            int sub = lower_bound(min, min + cnt, train[i]) - min;      // 使用二分法查找，仍然保持有序性
            min[sub] = train[i];                                   // 在第一个大于此编号的地方改写，仍然保持有序性
        }
    }

    printf("%d", cnt);
    
    return 0;
}



/* 7-7 列车调度 (25分)
火车站的列车调度铁轨的结构如下图所示。



两端分别是一条入口（Entrance）轨道和一条出口（Exit）轨道，它们之间有N条平行的轨道。每趟列车从入口可以选择任意一条轨道进入，最后从出口离开。在图中有9趟列车，在入口处按照{8，4，2，5，3，9，1，6，7}的顺序排队等待进入。如果要求它们必须按序号递减的顺序从出口离开，则至少需要多少条平行铁轨用于调度？

输入格式：
输入第一行给出一个整数N (2 ≤ N ≤10
​5
​​ )，下一行给出从1到N的整数序号的一个重排列。数字间以空格分隔。

输出格式：
在一行中输出可以将输入的列车按序号递减的顺序调离所需要的最少的铁轨条数。

输入样例：
9
8 4 2 5 3 9 1 6 7
输出样例：
4 */