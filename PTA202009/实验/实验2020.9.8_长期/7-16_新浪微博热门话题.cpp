#include <bits/stdc++.h>

using std::string;
using std::map;
using std::set;
using std::cin;
using std::cout;
using std::endl;

string change(string &s)
{
    int len = s.size();
    for (int i = 0; i < len; i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9'))
        {
            if (i != 0 && (s[i] >= 'A' && s[i] <= 'Z'))
                s[i] = s[i] - 'A' + 'a';
            if (i == 0 && (s[i] >= 'a' && s[i] <= 'z'))
                s[i] = s[i] - 'a' + 'A';
        }
        else
        {
            s.replace(i, 1, " ");
        }
    }
    if (s[len - 1] == ' ')
        s.erase(s.end() - 1);
    return s;
}
int main()
{
    int N;
    scanf("%d", &N);
    map<string, set<int>> topic;
    string tmp;
    getchar();
    for (int i = 0; i < N; i++)
    {
        std::getline(cin, tmp, '\n');
        int cur = 0, begin, end;
        string sub, h;
        while (cur != string::npos)
        {
            sub = tmp.substr(cur);
            if ((begin = sub.find("#")) != string::npos)
                sub = sub.substr(begin + 1);
            else
                break;
            if ((end = sub.find("#")) != string::npos)
                h = sub.substr(0, end);
            else
                break;
            h = change(h);
            topic[h].insert(i);
            cur += begin + end + 2;
        }
    }
    int max = 0, mct = 0;
    string h;
    for (map<string, set<int>>::iterator it = topic.begin(); it != topic.end(); it++)
    {
        if (it->second.size() > max)
        {
            max = it->second.size();
            h = it->first;
            mct = 1;
        }
        else if (it->second.size() == max)
        {
            mct++;
            if (it->first < h)
                h = it->first;
        }
    }
    cout << h << endl;
    cout << max << endl;
    if (mct > 1)
        cout << "And " << mct - 1 << " more ..." << endl;
    return 0;
}