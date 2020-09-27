#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

#define MAXS 100

char *search_sub(char *s, char *t);
void ReadString(char s[]);
void delete_sub(char* &s, char *t, char *pos);

int main()
{
    char *s, *t, *pos;
    s = (char*)malloc(MAXS* sizeof(char));
    t = (char*)malloc(MAXS* sizeof(char));

    ReadString(s);
    ReadString(t);
        //printf("%s\n", s);
        //printf("%s\n", t);
    
    while(1)
    {   
        pos = search_sub(s, t);
        if(pos == NULL) break;
        delete_sub(s, t, pos);
    }
     
    printf("%s", s);
    return 0;
}

void ReadString(char s[])
{
    memset(s, 0, sizeof(s));
    cin.getline(s, MAXS);
}


char *search_sub(char *s, char *t)
{
    char *point_s = s, *point_t = t;
    while(*point_s!='\0' && *point_t!='\0')
    {
        //printf("%c %c\n", *point_s, *point_t);
        if(*point_s == *point_t)
        {
            point_t++;
            point_s++;
        }
        else
        {
            point_s = point_s - (point_t - t) + 1;
            point_t = t;
        }
    }

    if(*point_t == '\0')
    {
        return point_s - (point_t - t);
    }
    else
    {
        return NULL;
    }
}

void delete_sub(char* &s, char *t, char *pos)
{
    char *point_s = s, *point_t = t, *point_pos = pos;
    int tlen = strlen(t);
    int slen = strlen(s);
    char *pt = pos + tlen;
    while(*pt!='\0')
    {
        *(pt-tlen) = *pt;
        pt++;
        //printf("-------\n");
    }
    pt--;
    for(int i = 0; i< tlen; i++)
    {
        *pt = '\0';
        pt--;
    }
}



/* 
7-1 删除字符串中的子串 (20分)
输入2个字符串S1和S2，要求删除字符串S1中出现的所有子串S2，即结果字符串中不能包含S2。

输入格式：
输入在2行中分别给出不超过80个字符长度的、以回车结束的2个非空字符串，对应S1和S2。

输出格式：
在一行中输出删除字符串S1中出现的所有子串S2后的结果字符串。

输入样例：
Tomcat is a male ccatat
cat
输出样例：
Tom is a male  
*/
