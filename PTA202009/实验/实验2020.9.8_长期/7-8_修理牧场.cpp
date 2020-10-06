#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;

// 使用了优先队列。同目录下有相同思路但超时的方法（用自写栈 + sort实现）


bool Smaller(int x, int y)
{
    return x < y;
}

int main()
{
    int N = 0, cost = 0;
    priority_queue<int, vector<int>, greater<int>> wood_sec;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        int tt = 0;
        scanf("%d", &tt);
        wood_sec.push(tt);
    } // 输入结束

    if (N == 1)
    {
        printf("%d", 0);
        return 0;
    }
    else
    {
        int sm1 = 0, sm2 = 0;
        sm1 = wood_sec.top();
        wood_sec.pop();
        sm2 = wood_sec.top();
        wood_sec.pop();
        cost += sm1 + sm2;
        wood_sec.push(sm1 + sm2);

        while (!wood_sec.empty())
        {
            if (wood_sec.size() == 1) // 取不出两个来（不用比较）
            {
                wood_sec.pop();
            }
            else
            {
                int ttsm1 = 0, ttsm2 = 0, tt = 0;
                ttsm1 = wood_sec.top();
                wood_sec.pop();
                ttsm2 = wood_sec.top();
                wood_sec.pop();
                tt = ttsm1 + ttsm2;
                cost += tt;
                wood_sec.push(tt);
            }
        }

        printf("%d", cost);
    }

    return 0;
}