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


/* 7-8 修理牧场 (25分)
农夫要修理牧场的一段栅栏，他测量了栅栏，发现需要N块木头，每块木头长度为整数L
​i
​​ 个长度单位，于是他购买了一条很长的、能锯成N块的木头，即该木头的长度是L
​i
​​ 的总和。

但是农夫自己没有锯子，请人锯木的酬金跟这段木头的长度成正比。为简单起见，不妨就设酬金等于所锯木头的长度。例如，要将长度为20的木头锯成长度为8、7和5的三段，第一次锯木头花费20，将木头锯成12和8；第二次锯木头花费12，将长度为12的木头锯成7和5，总花费为32。如果第一次将木头锯成15和5，则第二次锯木头花费15，总花费为35（大于32）。

请编写程序帮助农夫计算将木头锯成N块的最少花费。

输入格式:
输入首先给出正整数N（≤10
​4
​​ ），表示要将木头锯成N块。第二行给出N个正整数（≤50），表示每段木块的长度。

输出格式:
输出一个整数，即将木头锯成N块的最少花费。

输入样例:
8
4 5 1 2 1 3 1 1
输出样例:
49 */
