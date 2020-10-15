#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

typedef struct TNode
{
    char   name[265];       // 名称
    TNode* directory;       // 左子树存放目录信息
    TNode* document;        // 右子树存放文件信息
}TNode;

int main()
{
    int N = 0;
    char origin[300];
    
    scanf("%d", &N);
    for(int i = 0; i< N; i++)
    {
        memset(origin, 0, sizeof(origin));
        scanf("%s", origin);
        int len = strlen(origin);
        for(int j = 0; j< len; j++)
        {

        }
    }



    return 0;
}


