#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define MAX 1e9;
#define FRE() freopen("in.txt", "r", stdin)
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
const int maxn = 5000;
int vis[maxn], pre[maxn];
int N;
struct edge
{
    int st, en, co;
} e[maxn];

void init()
{
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= N; i++)
    { //注意pre数组的初始化
        pre[i] = i;
    }
    int st, en, co, state, k = N * (N - 1) / 2;
    for (int i = 0; i < k; i++)
    {
        scanf("%d%d%d%d", &st, &en, &co, &state);
        e[i].st = st;
        e[i].en = en;
        if (state)
        {
            e[i].co = 0;
        }
        else
        {
            e[i].co = co;
        }
    }
}

int Find(int x)
{ //查找x点的祖先
    return pre[x] == x ? x : pre[x] = Find(pre[x]);
}

bool cmd(edge a, edge b)
{
    return a.co < b.co;
}

void solve()
{
    int ans = 0, cnt = 0, k = N * (N - 1) / 2;
    for (int i = 0; i < k; i++)
    {
        edge te = e[i];
        int tx = Find(te.st), ty = Find(te.en);
        if (tx != ty)
        { //如果两个点不在同一个集合中,就通过并查集将两个点放在一个集合中
            cnt++;
            ans += te.co;
            pre[tx] = ty;
        }
        if (cnt == N - 1) //当确定的边数到达规定的数量的时候，就推出循环
            break;
    }
    //printf("cnt:%d\n",cnt);
    printf("%d\n", ans);
}

void check()
{
    int k = N * (N - 1) / 2;
    for (int i = 0; i < k; i++)
    {
        printf("%d ", e[i].co);
    }
    printf("\n");
}

int main()
{
    //FRE();
    scanf("%d", &N);
    init();
    int k = (N - 1) * N / 2;
    sort(e, e + k, cmd); //将所有的边的权值按从小到大进行排序
    //check();
    solve();
    return 0;
}
/*
PutIn:
4
1 2 1 1
1 3 4 0
1 4 1 1
2 3 3 0
2 4 2 1
3 4 5 0
PutOut:
3
*/

// 转载来源：https://www.cnblogs.com/sykline/p/10151659.html
