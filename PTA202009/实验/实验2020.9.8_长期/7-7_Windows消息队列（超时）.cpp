#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW -2
#define INFEASIBLE -1
#define MAX_SIZE 100010  

typedef int Status;

typedef struct Message
{
    int  priority;
    char content[15];
}Message;

bool Big(Message &x, Message &y)
{
    return (x.priority > y.priority);
}

int main()
{
    Message m_line[MAX_SIZE];
    int command_sumn = 0;
    int command_nown = 0;
    scanf("%d", &command_sumn);

    for(int i = 0; i< command_sumn; i++)
    {
        char tt_c[5];
        char tt_m[15];
        int  tt_p = 0;
        memset(tt_m, 0, sizeof(tt_m));
        memset(tt_c, 0, sizeof(tt_c));
        scanf("%s", tt_c);
        if(strcmp(tt_c, "PUT") == 0)
        {
            scanf("%s %d", tt_m, &tt_p);
            strcpy(m_line[command_nown].content, tt_m);
            m_line[command_nown].priority = tt_p;
            command_nown++;
            //printf("%d<<<<\n", command_nown);
        }
        else if(strcmp(tt_c, "GET") == 0)
        {
            if(command_nown == 0) 
            {
                printf("EMPTY QUEUE!\n");
            }
            else
            {
                sort(m_line, m_line + command_nown, Big);   // 优先级高的在最后面
                printf("%s\n", m_line[command_nown-1].content);
                command_nown--;
            }
        }
    }
    return 0;
}