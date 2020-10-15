#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <string>
using namespace std;

struct ptrCmp
{
    bool operator()(const char *s1, const char *s2) const
    {
        return strcmp(s1, s2) < 0;
    }
};

int main()
{
    int N = 0, K = 0, M = 0;
    scanf("%d%d", &N, &K);
    map<char *, int, ptrCmp> c_database;

    for (int i = 0; i < N; i++)
    {
        char* tt_id = (char*)malloc(20* sizeof(char));
        memset(tt_id, 0, sizeof(tt_id));
        int tt_m = 0;
        scanf("%s%d", tt_id, &tt_m);

        if (!c_database.count(tt_id))
        {
            if (tt_m < K)
                tt_m = K;
            c_database.insert(make_pair(tt_id, tt_m));
        }
        else
        {
            if (tt_m < K)
                c_database[tt_id] += K;
            else
                c_database[tt_id] += tt_m;
        }
    }

    scanf("%d", &M);
    for (int i = 0; i < M; i++)
    {
        char* tt_id = (char*)malloc(20* sizeof(char));
        memset(tt_id, 0, sizeof(tt_id));
        scanf("%s", tt_id);
        if (c_database.count(tt_id)>0)
        {
            printf("%d\n", c_database[tt_id]);
        }
        else
        {
            cout << "No Info" << endl;
        }
    }

    return 0;
}


/* 7-14 航空公司VIP客户查询 (25分)
不少航空公司都会提供优惠的会员服务，当某顾客飞行里程累积达到一定数量后，可以使用里程积分直接兑换奖励机票或奖励升舱等服务。现给定某航空公司全体会员的飞行记录，要求实现根据身份证号码快速查询会员里程积分的功能。

输入格式:
输入首先给出两个正整数N（≤10
​5
​​ ）和K（≤500）。其中K是最低里程，即为照顾乘坐短程航班的会员,航空公司还会将航程低于K公里的航班也按K公里累积。随后N行，每行给出一条飞行记录。飞行记录的输入格式为：18位身份证号码（空格）飞行里程。其中身份证号码由17位数字加最后一位校验码组成，校验码的取值范围为0~9和x共11个符号；飞行里程单位为公里，是(0, 15 000]区间内的整数。然后给出一个正整数M（≤10
​5
​​ ），随后给出M行查询人的身份证号码。

输出格式:
对每个查询人，给出其当前的里程累积值。如果该人不是会员，则输出No Info。每个查询结果占一行。

输入样例:
4 500
330106199010080419 499
110108198403100012 15000
120104195510156021 800
330106199010080419 1
4
120104195510156021
110108198403100012
330106199010080419
33010619901008041x
输出样例:
800
15000
1000
No Info */
