#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

// 学生类型
typedef struct Student
{
    char id[14];      // 该名学生的学号
    int exroom_num;   // 考场号
    int score;        // 该名学生的得分
    int local_rank;   // 在该考场的排名
    int overall_rank; // 总排名
} Student;

bool Small_str(Student &x, Student &y)
{
    return ((strcmp(x.id, y.id) < 0) ? true : false);
}

bool Big_int(Student &x, Student &y)
{
    return (x.score > y.score);
}

bool Cmp(Student &x, Student &y)
{
    if(x.score == y.score)      // 分数一样的，学号小的靠前
	{
		return strcmp(x.id, y.id) < 0;
	}
	return x.score > y.score;   // 分数不一样的，分数高的靠前
}

int bubble_sort(Student *tt, int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (tt[j].score < tt[j + 1].score) //这里由大到小排列
            {
                Student temp;
                temp = tt[j];
                tt[j] = tt[j + 1];
                tt[j + 1] = temp;
            }
        }
    }
    return 0;
}

int main()
{
    int N = 0; // 考点总数（≤100）
    scanf("%d", &N);
    Student *stu_list[N + 1];                            // 储存所有的学生对象（第一个位置空出，下标表示考场号）
    Student *stu_alls;                                   // 总排名之用
    int *stu_num = (int *)malloc((N + 1) * sizeof(int)); // 记录每个考场的学生人数
    int sumn = 0;                                        // 所有学生的总数

    for (int i = 1; i <= N; i++)
    {
        int K = 0; // 该考点的考生总数（≤300）
        scanf("%d", &K);
        sumn += K;
        stu_num[i] = K; // 记录该组学生总数

        // 分配空间
        stu_list[i] = (Student *)malloc(K * sizeof(Student));

        for (int j = 0; j < K; j++)
        {
            scanf("%s%d", (stu_list[i][j].id), &(stu_list[i][j].score));
            stu_list[i][j].exroom_num = i;
            stu_list[i][j].local_rank = -1;
            stu_list[i][j].overall_rank = -1;
        }
        sort(stu_list[i], stu_list[i] + K, Cmp); // 按照学号排序
        //bubble_sort(stu_list[i], K);                   // 按照成绩排序（稳定冒泡）
    }                                                  // 输入完成

    stu_alls = (Student *)malloc(sumn * sizeof(Student));
    int cnti = 0;

    // 本地排名
    for (int i = 1; i <= N; i++)
    {
        int rank_num = 1;
        int pre_score = stu_list[i][0].score;
        //printf("%d<<<\n", stu_num[i]);
        for (int j = 0; j < stu_num[i]; j++)
        {
            if (j == 0)
            {
                stu_list[i][j].local_rank = 1;
            }
            else if (stu_list[i][j - 1].score == stu_list[i][j].score)
            {
                stu_list[i][j].local_rank = stu_list[i][j - 1].local_rank;
            }
            else
            {
                stu_list[i][j].local_rank = rank_num;
            }
            rank_num++;

            strcpy(stu_alls[cnti].id, stu_list[i][j].id);
            stu_alls[cnti].score = stu_list[i][j].score;
            stu_alls[cnti].exroom_num = stu_list[i][j].exroom_num;
            stu_alls[cnti].local_rank = stu_list[i][j].local_rank;
            cnti++;
        }
    }

    sort(stu_alls, stu_alls + sumn, Cmp); // 按照学号排序
    //bubble_sort(stu_alls, sumn);                // 按照成绩排序（稳定冒泡）

    printf("%d\n", sumn);
    int pre_score = stu_alls[0].score;
    int rank_num = 1;
    for (int i = 0; i < sumn; i++)
    {
        if (i == 0)
        {
            stu_alls[i].overall_rank = 1;
        }
        else if (stu_alls[i].score == stu_alls[i-1].score)
        {
            stu_alls[i].overall_rank = stu_alls[i-1].overall_rank;
        }
        else
        {
            stu_alls[i].overall_rank = rank_num;
        }
        rank_num++;
        printf("%s %d %d %d\n", stu_alls[i].id, stu_alls[i].overall_rank, stu_alls[i].exroom_num, stu_alls[i].local_rank);
    }

    return 0;
}

/* 
7-19 PAT排名汇总 (25分)
计算机程序设计能力考试（Programming Ability Test，简称PAT）旨在通过统一组织的在线考试及自动评测方法客观地评判考生的算法设计与程序设计实现能力，科学的评价计算机程序设计人才，为企业选拔人才提供参考标准（网址http://www.patest.cn）。

每次考试会在若干个不同的考点同时举行，每个考点用局域网，产生本考点的成绩。考试结束后，各个考点的成绩将即刻汇总成一张总的排名表。

现在就请你写一个程序自动归并各个考点的成绩并生成总排名表。

输入格式:
输入的第一行给出一个正整数N（≤100），代表考点总数。随后给出N个考点的成绩，格式为：首先一行给出正整数K（≤300），代表该考点的考生总数；随后K行，每行给出1个考生的信息，包括考号（由13位整数字组成）和得分（为[0,100]区间内的整数），中间用空格分隔。

输出格式:
首先在第一行里输出考生总数。随后输出汇总的排名表，每个考生的信息占一行，顺序为：考号、最终排名、考点编号、在该考点的排名。其中考点按输入给出的顺序从1到N编号。考生的输出须按最终排名的非递减顺序输出，获得相同分数的考生应有相同名次，并按考号的递增顺序输出。

输入样例:
2
5
1234567890001 95
1234567890005 100
1234567890003 95
1234567890002 77
1234567890004 85
4
1234567890013 65
1234567890011 25
1234567890014 100
1234567890012 85
输出样例:
9
1234567890005 1 1 1
1234567890014 1 2 1
1234567890001 3 1 2
1234567890003 3 1 2
1234567890004 5 1 4
1234567890012 5 2 2
1234567890002 7 1 5
1234567890013 8 2 3
1234567890011 9 2 4 */
