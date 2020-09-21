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
        int tt = train[i];
        int flag = 0;
        if(i == 0)
        {
            min[cnt++] = tt;
        }
        else
        {
            for(int j = 0; j< cnt; j++)
            {
                if(tt < min[j])
                {
                    min[j] = tt;
                    ++flag;
                    break;
                }
            }
            if(flag == 0)
            {
                min[cnt++] = tt;
            }
        }
    }

    printf("%d", cnt);

    



    return 0;
}