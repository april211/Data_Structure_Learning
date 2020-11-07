#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 110

int main()
{
    int N = 0;
    scanf("%d", &N);
    vector<int> s;

    for(int i = 0; i< 2* N; i++)
    {
        int tt;
        scanf("%d", &tt);
        s.push_back(tt);
    }

    sort(s.begin(), s.end(), less<int>());

    printf("%d", s[int(floor((2* N+1)/2))-1]);



    return 0;
}