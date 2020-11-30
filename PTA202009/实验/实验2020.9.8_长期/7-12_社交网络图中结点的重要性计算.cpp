#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f;
const int maxn = 21114;
using namespace std;
int Graph[maxn][maxn];

int main()
{
    
    int N = 0, M = 0;
    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            if (i == j)
                Graph[i][j] = 0;
            else
                Graph[i][j] = INF;
        }
    }

    for (int i = 0; i < M; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        Graph[a][b] = 1;
        Graph[b][a] = 1;
    }

    for (int k = 1; k <= N; ++k)
    {
        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                if (Graph[i][j] > Graph[i][k] + Graph[k][j])
                {
                    Graph[i][j] = Graph[i][k] + Graph[k][j];
                }
            }
        }
    }

    bool flag = true;
    for (int i = 1; i <= N; ++i)
    {
        if (Graph[1][i] == INF)
        {
            flag = false;
            break;
        }
    }
    int K = 0;
    scanf("%d", &K);
    while (K--)
    {
        int num = 0;
        scanf("%d", &num);
        if (!flag)
        {
            printf("Cc(%d)=%.2f\n", num, 0);
        }
        else
        {
            double average = 0;
            for (int i = 1; i <= N; ++i)
            {
                average += Graph[num][i];
            }
            average = 1.0 / (average * 1.0 / (N - 1));
            printf("Cc(%d)=%.2f\n", num, average);
        }
    }
    return 0;
}
