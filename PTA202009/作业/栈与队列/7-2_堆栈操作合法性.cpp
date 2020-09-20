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