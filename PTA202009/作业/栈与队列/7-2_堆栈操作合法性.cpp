#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>



int main()
{
    char elem = NULL;
    int  cnt = 0, mca = 0, size = 0;
    scanf("%d%d", &cnt, &mca);
    getchar();
    for(int i = 0; i< cnt; i++)
    {
        int cflag = 0, eflag = 0;
        size = 0;
        while(size >= 0 && size <= mca && cflag == 0)
        {
            elem = getchar();
            switch (elem)
            {
            case 'S':
                if(size == mca)
                {
                    ++eflag;
                    break;
                }
                ++size;
                break;
            case 'X':
                if(size == 0)
                {
                    ++eflag;
                    break;
                }
                --size;
                break;
            default:    // 回车
                ++cflag;
                break;
            }
            //printf(">>>>>\n");
        }
        if(size != 0 || eflag != 0)
        {
            printf("NO\n");
        }
        else
        {
            printf("YES\n");
        }
    }


    return 0;
}


/* 7-2 堆栈操作合法性 (20分)
假设以S和X分别表示入栈和出栈操作。如果根据一个仅由S和X构成的序列，对一个空堆栈进行操作，相应操作均可行（如没有出现删除时栈空）且最后状态也是栈空，则称该序列是合法的堆栈操作序列。请编写程序，输入S和X序列，判断该序列是否合法。

输入格式:
输入第一行给出两个正整数N和M，其中N是待测序列的个数，M（≤50）是堆栈的最大容量。随后N行，每行中给出一个仅由S和X构成的序列。序列保证不为空，且长度不超过100。

输出格式:
对每个序列，在一行中输出YES如果该序列是合法的堆栈操作序列，或NO如果不是。

输入样例：
4 10
SSSXXSXXSX
SSSXXSXXS
SSSSSSSSSSXSSXXXXXXXXXXX
SSSXXSXXX
输出样例：
YES
NO
NO
NO */