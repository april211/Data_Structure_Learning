#include <iostream>
#include <algorithm>
#include <cstdio>

#define MAX_SIZE 100006

int num[MAX_SIZE] = {0, };

bool Smaller(int x, int y)
{
    return (x<y);
}

int main()
{
    int N;
    scanf("%d", &N);
    
    for(int i = 0; i< N; i++)
    {
        scanf("%d", &(num[i]));
    }
    std::sort(num, num + N, Smaller);

    for(int i = 0; i< N; i++)
    {
        if(i == 0)
            printf("%d", num[i]);
        else
            printf(" %d", num[i]);
    }


    return 0;
}
