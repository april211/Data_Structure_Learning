#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

// 学生类型
typedef struct Student
{
    int score;    // 该名学生的得分（[0, 100]内的整数）
    char id[7];   // 该名学生的学号（不超过六位）
    char name[9]; // 学生姓名（不超过 8位且不包含空格的字符串）
} Student;

bool Cmp_name(Student &x, Student &y)
{
    if (strcmp(x.name, y.name) == 0)
    {
        return ((strcmp(x.id, y.id) < 0) ? true : false);
    }
    else
    {
        return ((strcmp(x.name, y.name)<0)?true:false);
    }
}

bool Cmp_id(Student &x, Student &y)
{
    return ((strcmp(x.id, y.id) < 0) ? true : false);
}

bool Cmp_score(Student &x, Student &y)
{
    if (x.score == y.score)
    {
        return ((strcmp(x.id, y.id) < 0) ? true : false);
    }
    else
    {
        return (x.score < y.score);
    }
}

int main()
{
    int N = 0; // 纪录的条数
    int C = 0; // 指定排序的列号

    scanf("%d%d", &N, &C);
    Student *stu_list = (Student *)malloc(N * sizeof(Student)); // 学生列表

    for (int i = 0; i < N; i++)
    {
        scanf("%s%s%d", stu_list[i].id, stu_list[i].name, &(stu_list[i].score));
    } // 输入结束

    if (C == 1)         //按学号递增排序
    {
        sort(stu_list, stu_list + N, Cmp_id);
    }
    else if (C == 2)    //按姓名的非递减字典序排序
    {
        sort(stu_list, stu_list + N, Cmp_name);
    }
    else // C == 3, 按成绩的非递减排序
    {
        sort(stu_list, stu_list + N, Cmp_score);
    }

    for(int i = 0; i< N; i++)
    {
        printf("%s %s %d\n", stu_list[i].id, stu_list[i].name, stu_list[i].score);
    }

    return 0;
}


/* 3 2
000007 James 85
000010 Amy 90
000011 Amy 90

000010 Amy 90
000011 Amy 90
000007 James 85 */

/* 3 2
000007 James 85
000010 Amy 90
000009 Amy 90

000009 Amy 90
000010 Amy 90
000007 James 85 */