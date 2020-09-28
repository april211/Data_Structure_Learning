#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
using namespace std;

// 本题使用了 STL中的优先队列
typedef struct Message
{
    int  priority;
    char content[15];
}Message;

// 重写仿函数
struct Big
{
    bool operator() (Message &x, Message &y) 
    {
         return (x.priority > y.priority);
    }
};

int main()
{
    priority_queue<Message, vector<Message>, Big> m_queue;
    int command_sumn = 0;
    scanf("%d", &command_sumn);

    for(int i = 0; i< command_sumn; i++)
    {
        Message tt_m;
        char tt_command[5];
        memset(tt_command, 0, sizeof(tt_command));
        memset(tt_m.content, 0, sizeof(tt_m.content));
        scanf("%s", tt_command);
        if(strcmp(tt_command, "PUT") == 0)
        {
            scanf("%s %d", tt_m.content, &tt_m.priority);
            m_queue.push(tt_m);
        }
        else if(strcmp(tt_command, "GET") == 0)
        {
            if(m_queue.empty())
            {
                printf("EMPTY QUEUE!\n");
            }
            else
            {
                printf("%s\n",  m_queue.top().content);
                m_queue.pop();
            }
        }
    }
    return 0;
}