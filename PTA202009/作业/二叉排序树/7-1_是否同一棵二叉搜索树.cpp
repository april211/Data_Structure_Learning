#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using namespace std;
#define inf 0x3f3f3f3f

// 二叉树结点
typedef struct TNode
{
    int Data;
    TNode *Left;
    TNode *Right;
} TNode;
typedef TNode *BiTree;

bool isSameBiTree(BiTree p, BiTree q)
{
    if ((!p) && (!q))
        return true;
    else if (((!p) && q) || (p && (!q)))
        return false;
    else if (p->Data != q->Data)
        return false;
    else
        return isSameBiTree(p->Left, q->Left) && isSameBiTree(p->Right, q->Right);
}

// 按照规则向二叉树中插入一个节点
void InsertNode(BiTree &bt, int value) // 二叉树类型，N 个节点，要插入的结点的值
{
    TNode *pt = bt;
    if ((!(pt->Left)) && ((value) < (pt->Data))) // 如果左子树为空，并且新节点的值比此根节点的值小
    {
        BiTree add = (BiTree)malloc(sizeof(TNode));
        add->Data = value, add->Left = add->Right = NULL;
        pt->Left = add;
        return;
    }
    else if ((!(pt->Right)) && ((value) > (pt->Data)))
    {
        BiTree add = (BiTree)malloc(sizeof(TNode));
        add->Data = value, add->Left = add->Right = NULL;
        pt->Right = add;
        return;
    }
    else if ((value) < (pt->Data)) // 左右节点都不为空，需要递归求解
    {
        return InsertNode(pt->Left, value);
    }
    else
    {
        return InsertNode(pt->Right, value);
    }
}

void InitBiTree(BiTree &bt)
{
    int tt;
    scanf("%d", &tt);
    //printf("###########\n");
    bt->Data = tt;
    bt->Left = NULL;
    bt->Right = NULL;
}

int main()
{
    int N, L;
    scanf("%d", &N);
    //printf("###########\n");
    while (N)
    {
        scanf("%d", &L);
        BiTree origin;      // 初始插入序列形成的二叉树
        InitBiTree(origin); // 载入第一个元素
        
        printf("---------\n");
        for (int i = 1; i < N; i++)
        {
            int tt;
            scanf("%d", &tt);
            InsertNode(origin, tt); // 构造二叉树（还剩 N-1 个节点未加入）
        }
        for (int i = 0; i < L; i++) // L行
        {
            BiTree second; // 后插入序列形成的二叉树
            InitBiTree(second);
            for (int i = 1; i < N; i++)
            {
                int tt;
                scanf("%d", &tt);
                InsertNode(second, tt); // 构造二叉树（还剩 N-1 个节点未加入）
            }
            if (isSameBiTree(origin, second)) // 如果两个二叉树完全相同，则打印 Yes
                printf("Yes\n");
            else
                printf("No\n");
        }
        scanf("%d", &N); // 载入下一个 N，用于下一次的条件判断
    }

    return 0;
}
