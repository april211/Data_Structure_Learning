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
    bt = (BiTree)malloc(sizeof(TNode));
    bt->Data = tt;
    bt->Left = NULL;
    bt->Right = NULL;
}

int main()
{
    int N, L;
    scanf("%d", &N);
    while (N)
    {
        scanf("%d", &L);
        BiTree origin;      // 初始插入序列形成的二叉树
        InitBiTree(origin); // 载入第一个元素
        
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


/* 7-1 是否同一棵二叉搜索树 (25分)
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

输入格式:
输入包含若干组测试数据。每组数据的第1行给出两个正整数N (≤10)和L，分别是每个序列插入元素的个数和需要检查的序列个数。第2行给出N个以空格分隔的正整数，作为初始插入序列。最后L行，每行给出N个插入的元素，属于L个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。

输出格式:
对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。

输入样例:
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0
输出样例:
Yes
No
No
鸣谢青岛大学周强老师补充测试数据！ */
