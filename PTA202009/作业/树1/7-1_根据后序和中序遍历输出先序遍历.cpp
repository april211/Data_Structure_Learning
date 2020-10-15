#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;

struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

typedef struct Elem
{
    int Data;  // 数据位
    bool used; // 是否已经被添加过
} Elem;

// 由后序遍历和中序遍历构造树
void Create_BT_From_PostIn(Elem *post_start, Elem *post_end, Elem *in_start, Elem *in_end, int N, BinTree &BT)
{
    if (post_start>post_end || in_start>in_end)
    {
        return;
    }

    BT = (TNode *)malloc(sizeof(TNode));
    BT->Data = post_end->Data;
    post_end->used = true;

    int root_val = BT->Data; // 当前从后序遍历序列中寻找到的根节点的编号
    int divider = -1;        // 在中序遍历序列中起到分割作用的元素的下标
    int left_n, right_n;
    // 到中序遍历序列中寻找该节点
    for (Elem* pt = in_start; pt <= in_end; pt++)
    {
        if (pt->Data == root_val)
        {
            divider = pt - in_start;
        }
    }
    left_n = divider;
    right_n = N - divider - 1;
    //printf("%d\n", divider);

    if ((right_n <= 0) || ((right_n > 0) && ((in_start + divider + 1)->used == true))) // 该根节点没有右孩子
    {
        BT->Right = NULL;
    }
    if ((left_n <= 0) || ((left_n > 0) && ((in_start + divider - 1)->used == true))) // 该根节点没有左孩子
    {
        BT->Left = NULL;
    }

    Create_BT_From_PostIn(post_start+N-1-right_n, post_end-1, in_end-right_n+1, in_end, right_n, BT->Right);
    Create_BT_From_PostIn(post_start,post_start + left_n-1, in_start, in_start+left_n-1, left_n, BT->Left);
}

// 前序遍历
void PreorderTraversal(BinTree BT)
{
    if (!BT)
        return;
    else
    {
        printf(" %d", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}

int main()
{
    int N = 0; // 树的节点总数（保证是正整数）
    BinTree BT = NULL;
    scanf("%d", &N);
    Elem *post_order = (Elem *)malloc(N * sizeof(Elem)); // 储存输入的后序遍历的结果
    Elem *in_order = (Elem *)malloc(N * sizeof(Elem));   // 储存输入的中序遍历的结果

    // 利用下标来存储输入的数字，数值为一个标记位
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &(post_order[i].Data));
        post_order[i].used = false;
    }
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &(in_order[i].Data));
        in_order[i].used = false;
    } // 输入完成

    Create_BT_From_PostIn(post_order, post_order + N - 1, in_order, in_order + N - 1, N, BT);
    printf("Preorder:");
    PreorderTraversal(BT);

    return 0;
}


/* 7-1 根据后序和中序遍历输出先序遍历 (25分)
本题要求根据给定的一棵二叉树的后序遍历和中序遍历结果，输出该树的先序遍历结果。

输入格式:
第一行给出正整数N(≤30)，是树中结点的个数。随后两行，每行给出N个整数，分别对应后序遍历和中序遍历结果，数字间以空格分隔。题目保证输入正确对应一棵二叉树。

输出格式:
在一行中输出Preorder:以及该树的先序遍历结果。数字间有1个空格，行末不得有多余空格。

输入样例:
7
2 3 1 5 7 6 4
1 2 3 4 5 6 7
输出样例:
Preorder: 4 1 3 2 6 5 7 */
