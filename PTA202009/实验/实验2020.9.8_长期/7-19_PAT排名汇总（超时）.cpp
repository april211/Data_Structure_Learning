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
        sort(stu_list[i], stu_list[i] + K, Small_str); // 按照学号排序
        bubble_sort(stu_list[i], K);                   // 按照成绩排序（稳定冒泡）
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

    sort(stu_alls, stu_alls + sumn, Small_str); // 按照学号排序
    bubble_sort(stu_alls, sumn);                // 按照成绩排序（稳定冒泡）

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
