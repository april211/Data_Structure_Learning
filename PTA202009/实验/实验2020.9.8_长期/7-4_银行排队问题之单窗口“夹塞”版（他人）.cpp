#include <iostream>
#include <iomanip>
#include <algorithm> 
#include <vector>
#include <cstdio>
#include <queue>
#include <map>

#define maxp 10086
#define maxn 106
using namespace std;

typedef struct People
{
    string name;
    int come;
    int cost;
    int ID;
}People;

int find(int N, const queue<People> *queue_list)
{
    int pos = 1;
    while (queue_list[pos].empty())
    {
        pos++;
    }

    People a = queue_list[pos].front();
    for (int i = pos + 1; i <= N; i++)
    {
        if (queue_list[i].empty())
            continue;
        People b = queue_list[i].front();
        if (b.come < a.come || (b.come == a.come && b.ID < a.ID))
        {
            a = b;
            pos = i;
        }
    }
    return pos;
}

int main()
{    
    int N = 0, M = 0;
    People person[maxp];
    map<string, int> ditu;
    vector<string> vec[maxn];
    queue<People> queue_list[maxn]; //记录这个队伍是否有人

    cin >> N >> M;
    for(int i = 0; i< N; i++)
    {
        person[i].come = 0;
        person[i].cost = 0;
        person[i].ID = 0;
        person[i].name.clear();
    }


    for (int i = 1; i <= M; i++)
    {
        int num;
        cin >> num;
        for (int j = 0; j < num; j++)
        {
            string s;
            cin >> s;
            vec[i].push_back(s);
            ditu[s] = i;
        }
    }

    for (int i = 0; i < N; i++)
    {
        cin >> person[i].name >> person[i].come >> person[i].cost;
        person[i].ID = i + 1;
        if (person[i].cost > 60)
            person[i].cost = 60;
        int duiwu = ditu[person[i].name];
        if (duiwu == 0)
        {
            queue_list[M + 1].push(person[i]); //散人
        }
        else
        {
            queue_list[duiwu].push(person[i]);
        }
    }
    
    People a;
    int pos = find(M + 1, queue_list);
    int jieshu = 0;
    int cnt = 0;
    int wait = 0;
    bool flag = 0;

    while (cnt < N)
    {
        if (queue_list[pos].empty())
            pos = find(M + 1, queue_list);
        a = queue_list[pos].front();
        if (a.come > jieshu) //如果来晚了，朋友不在了
        {
            if (flag == 1)   //没人排队了，之后新来人
            {
                jieshu = a.come;
                flag = 0;
            }
            pos = find(M + 1, queue_list);
            flag = 1;
            continue;
        }
        else if (a.come <= jieshu) //有朋友，可以加塞
        {
            if (pos == M + 1)     //闲散人员
            {
                if (flag == 1)
                {
                    if (a.come <= jieshu)
                    {
                        wait += jieshu - a.come;
                        //jieshu += a.cost;
                    }
                    else          //来了就可以直接办理
                    {
                        jieshu += a.come - jieshu;
                        //jieshu += a.cost;
                    }

                    ++cnt; //办业务
                    queue_list[pos].pop();

                    jieshu += a.cost;
                    cout << a.name << endl;
                    flag = 0;
                    continue;
                }
                pos = find(M + 1, queue_list);
                flag = 1;
            }
            if (a.come <= jieshu)
            {
                wait += jieshu - a.come;
                //jieshu += a.cost;
            }
            else //来了就可以直接办理
            {
                jieshu += a.come - jieshu;
                //jieshu += a.cost;
            }
            ++cnt; //办业务
            queue_list[pos].pop();

            jieshu += a.cost;
            cout << a.name << endl;
        }
    }

    printf("%.1lf", (1.0* wait)/(N* 1.0));

    return 0;
}