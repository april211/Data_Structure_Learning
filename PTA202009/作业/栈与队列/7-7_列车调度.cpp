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