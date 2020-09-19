#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

// 二叉树的三叉链表表示 + Huffman 算法

typedef struct HFNode
{
    int weight;                 // 数据域
    struct HFNode *lchild;     // 左子树指针
    struct HFNode *rchild;     // 右子树指针
    struct HFNode *parent;     // 双亲指针
}HFNode, *HFTree;

bool compare_t(int x, int y)
{
    return x<y;
}

HFTree CreateHFtree(int* elarray, int n)
{




}

int main()
{
    int n = 0;
    scanf("%d", &n);
    int *elarray = (int*)malloc(n* sizeof(int));
    for (int i = 0; i< n; i++)
    {
        scanf("%d", &(elarray[i]));
    }// 输入结束
    sort(elarray, elarray + n, compare_t);




    return 0;
}