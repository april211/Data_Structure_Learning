#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;
#define inf 0x3f3f3f3f

void InitBiTree()
{
    int tt;
    scanf("%d", &tt);
    //printf("###########\n");
}

int main()
{
    int N, L;
    scanf("%d", &N);
    printf("###########\n");
    while (N)
    {
        printf("---------\n");
        scanf("%d", &L);
        InitBiTree();
        for (int i = 1; i < N; i++)
        {
            int tt;
            scanf("%d", &tt);
            printf("---------\n");
        }
        for (int i = 0; i < L; i++) // L行
        {
            InitBiTree();
            for (int i = 1; i < N; i++)
            {
                int tt;
                scanf("%d", &tt);
            }
        }
        scanf("%d", &N);
    }

    return 0;
}
