#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXS 30

char *search(char *s, char *t);
void ReadString( char s[] );


void ReadString(char s[])
{
    memset(s, 0, sizeof(s));
    cin.getline(s, MAXS);
}

int main()
{
    char s[MAXS], t[MAXS], *pos;

    ReadString(s);
    ReadString(t);
    pos = search(s, t);
    if ( pos != NULL )
        printf("%d\n", pos - s);
    else
        printf("-1\n");

    return 0;
}


char *search(char *s, char *t)
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


/* 
6-1 查找子串 (20分)
本题要求实现一个字符串查找的简单函数。

函数接口定义：
char *search( char *s, char *t );
函数search在字符串s中查找子串t，返回子串t在s中的首地址。若未找到，则返回NULL。

裁判测试程序样例：
#include <stdio.h>
#define MAXS 30

char *search(char *s, char *t);
void ReadString( char s[] ); /* 裁判提供，细节不表 */

/*
int main()
{
    char s[MAXS], t[MAXS], *pos;

    ReadString(s);
    ReadString(t);
    pos = search(s, t);
    if ( pos != NULL )
        printf("%d\n", pos - s);
    else
        printf("-1\n");

    return 0;
}

输入样例1：
The C Programming Language
ram
输出样例1：
10
输入样例2：
The C Programming Language
bored
输出样例2：
-1 
*/
