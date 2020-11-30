#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// 寻找指定整型向量容器中是否存在元素 value。若存在，则返回其 ID，否则返回 -10
int vfind(const vector<int> &location, int value, string &str, const vector<string> &all_strings)
{
    int size = location.size();
    int loc = -10;
    for(int i = 0; i< size; i++)
    {
        if(location[i] == value && all_strings[i] != str)
        {
            loc = i;
            break;
        }
    }
    return loc;
}

int main()
{
    // 输入第一行首先给出两个正整数 N（≤500）和 P（≥2N的最小素数）
    int N = 0, P = 0; // 分别为待插入的关键字总数、以及散列表的长度
    scanf("%d%d", &N, &P);

    // 存储给定的所有字符串
    vector<string> all_strings;
    vector<int> location;

    // 产生平方探测数列
    int base = 1;
    vector<int> array;
    for (int i = 0; i < P* P + 4; i++)
    {
        array.push_back(1 * base * base);
        array.push_back(-1 * base * base);
        ++base;
    }

    // 第二行给出 N个字符串关键字，每个长度不超过 8位，其间以空格分隔
    for (int i = 0; i < N; i++)
    {
        string tt;
        cin >> tt;
        all_strings.push_back(tt);
    }

    for (int i = 0; i < N; i++)
    {
        int size = all_strings[i].size();
        int tt = 0;
        int loc = 0;
        if(size >= 3)
        {
            for (int j = size - 1; j >= size - 3; j--)
            {
                tt += (all_strings[i][j] - 'A') * pow(32, size - j - 1);
            }
            loc = (tt) % P;
        }
        else
        {
            for (int j = 0; j < size; j++)
            {
                tt += (all_strings[i][j] - 'A') * pow(32, j);
            }
            loc = (tt) % P;
        }
        

        //printf("%d\n", loc);
        int contra = vfind(location, loc, all_strings[i], all_strings);

        int cnt = 0;
        int ttt = loc;
        while (contra != -10) // 发生冲突，并且是不同的字符串
        {
            if(ttt + array[cnt] < 0)
            {
                ttt = (ttt + array[cnt] + P) % P;
            }
            else
            {
                ttt = (ttt + array[cnt]) % P;
            }

            cnt++;
            contra = vfind(location, ttt, all_strings[i], all_strings);
            if(contra != -10) ttt = loc;
        }
        loc = ttt;

        // 直到没有冲突时，可以压入
        location.push_back(loc);
    }

    for (int i = 0; i < N; i++)
    {
        if (i == 0)
            printf("%d", location[i]);
        else
            printf(" %d", location[i]);
    }

    return 0;
}
