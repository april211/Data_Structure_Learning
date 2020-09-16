#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#define ERROR -1
#define OK 1
using namespace std;

typedef struct Country
{
    int id;
    int gold_rank;
    int all_rank;
    int gav_rank;
    int aav_rank;
    double gold_medal;
    double all_medal;
    double popularity;
    double gold_average;
    double all_average;
} Country, *CountryList;

bool compare_s(int a, int b)
{
    return a > b;
}

// 返回最佳排名序号：金牌榜=1，奖牌榜=2，国民人均金牌榜=3，国民人均奖牌榜=4
int compare_r(const Country &cy)
{
    if (cy.gold_rank <= cy.all_rank && cy.gold_rank <= cy.gav_rank && cy.gold_rank <= cy.aav_rank)
    {
        return 1;
    }
    else if (cy.all_rank <= cy.gold_rank && cy.all_rank <= cy.gav_rank && cy.all_rank <= cy.aav_rank)
    {
        return 2;
    }
    else if (cy.gav_rank <= cy.gold_rank && cy.gav_rank <= cy.all_rank && cy.gav_rank <= cy.aav_rank)
    {
        return 3;
    }
    else if (cy.aav_rank <= cy.gold_rank && cy.aav_rank <= cy.all_rank && cy.aav_rank <= cy.gav_rank)
    {
        return 4;
    }
    else
    {
        return 0; // 此时错误
    }
}



int main()
{
    int len = 0, qn = 0;
    int *cqlist = NULL;
    CountryList cy = NULL;
    scanf("%d%d", &len, &qn);
    cy = (Country *)malloc(len * sizeof(Country));
    cqlist = (int *)malloc(qn * sizeof(int));

    for (int i = 0; i < len; i++)
    {
        double gold_medal = 0, all_medal = 0, popularity = 0;
        scanf("%lf%lf%lf", &gold_medal, &all_medal, &popularity);
        cy[i].id = i;
        cy[i].gold_medal = gold_medal;
        cy[i].all_medal = all_medal;
        cy[i].popularity = popularity;
        cy[i].all_average = cy[i].all_medal / cy[i].popularity;
        cy[i].gold_average = cy[i].gold_medal / cy[i].popularity;
    }

    for (int i = 0; i < qn; i++)
    {
        int id = 0;
        scanf("%d", &id);
        cqlist[i] = id;
    } // 输入完成

    // 按照指定方法进行排序
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (cy[j].gold_medal - cy[j + 1].gold_medal < -0.00000001)
            {
                Country tt = cy[j];
                cy[j] = cy[j + 1];
                cy[j + 1] = tt;
            }
        }
    }

    int rk = 1;

    // 将当前国家顺序导入至榜单中
    for (int i = 0; i < len; i++)
    {
        if(i == 0)
        {
            cy[i].gold_rank = rk;
        }
        else
        {
            if(fabs(cy[i].gold_medal - cy[i-1].gold_medal) < 0.00000001)
                cy[i].gold_rank = cy[i-1].gold_rank;
            else
            {
                cy[i].gold_rank = rk;
            }
        }
        ++rk;
        //printf("%d<<<\n", cy[i].gold_rank);
    }

    // 按照指定方法进行排序
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (cy[j].all_medal - cy[j + 1].all_medal < -0.00000001)
            {
                Country tt = cy[j];
                cy[j] = cy[j + 1];
                cy[j + 1] = tt;
            }
        }
    }

    rk = 1;


    // 将当前国家顺序导入至榜单中
    for (int i = 0; i < len; i++)
    {
        if(i == 0)
        {
            cy[i].all_rank = rk;
        }
        else
        {
            if(fabs(cy[i].all_medal - cy[i-1].all_medal) < 0.00000001)
                cy[i].all_rank = cy[i-1].all_rank;
            else
            {
                cy[i].all_rank = rk;
            }
        }
        ++rk;
    }

    // 按照指定方法进行排序
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (cy[j].all_average - cy[j + 1].all_average < -0.00000001)
            {
                Country tt = cy[j];
                cy[j] = cy[j + 1];
                cy[j + 1] = tt;
            }
        }
    }

    rk = 1;

    // 将当前国家顺序导入至榜单中
    for (int i = 0; i < len; i++)
    {
        if(i == 0)
        {
            cy[i].aav_rank = rk;
        }
        else
        {
            if(fabs(cy[i].all_average - cy[i-1].all_average) < 0.00000001)
                cy[i].aav_rank = cy[i-1].aav_rank;
            else
            {
                cy[i].aav_rank = rk;
            }
        }
        ++rk;
    }

    // 按照指定方法进行排序
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (cy[j].gold_average - cy[j + 1].gold_average < -0.00000001)
            {
                Country tt = cy[j];
                cy[j] = cy[j + 1];
                cy[j + 1] = tt;
            }
        }
    }

    rk = 1;

    // 将当前国家顺序导入至榜单中
    for (int i = 0; i < len; i++)
    {
        if(i == 0)
        {
            cy[i].gav_rank = rk;
        }
        else
        {
            if(fabs(cy[i].gold_average - cy[i-1].gold_average) < 0.00000001)
                cy[i].gav_rank = cy[i-1].gav_rank;
            else
            {
                cy[i].gav_rank = rk;
            }
        }
        ++rk;
    } 

    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (cy[j].id > cy[j + 1].id)
            {
                Country tt = cy[j];
                cy[j] = cy[j + 1];
                cy[j + 1] = tt;
            }
        }
    }// 资料齐整

    //printf("%d<<<\n", cy[1].gold_rank);


    for (int i = 0; i < qn; i++)
    {
        int cid = cqlist[i]; // 获取请求信息
        int method = compare_r(cy[cid]);
        if (i == 0)
        {
            if (method == 1)
                printf("%d:%d", cy[cid].gold_rank, method);
            else if (method == 2)
                printf("%d:%d", cy[cid].all_rank, method);
            else if (method == 3)
                printf("%d:%d", cy[cid].gav_rank, method);
            else if (method == 4)
                printf("%d:%d", cy[cid].aav_rank, method);
        }
        else
        {
            if (method == 1)
                printf(" %d:%d", cy[cid].gold_rank, method);
            else if (method == 2)
                printf(" %d:%d", cy[cid].all_rank, method);
            else if (method == 3)
                printf(" %d:%d", cy[cid].gav_rank, method);
            else if (method == 4)
                printf(" %d:%d", cy[cid].aav_rank, method);
        }
        
    }

    return 0;
}

/*
3 3
44 44 44
44 44 44
33 33 1000
0 1 2

2 1
44 44 44
44 44 44
0
*/