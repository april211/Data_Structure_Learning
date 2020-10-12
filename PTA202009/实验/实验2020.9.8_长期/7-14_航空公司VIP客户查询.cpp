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


