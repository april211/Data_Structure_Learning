#include <cstdio>
#include <iostream>
#include <queue>

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

// 按照规则向二叉树中插入一个节点
void InsertNode(BiTree &bt, int value) // 二叉树类型，N 个节点，要插入的结点的值
{
    TNode *pt = bt;
    if ((!(pt->Left)) && ((value) > (pt->Data))) // 如果左子树为空，并且新节点的值比此根节点的值小
    {
        BiTree add = (BiTree)malloc(sizeof(TNode));
        add->Data = value, add->Left = add->Right = NULL;
        pt->Left = add;
        return;
    }
    else if ((!(pt->Right)) && ((value) < (pt->Data)))
    {
        BiTree add = (BiTree)malloc(sizeof(TNode));
        add->Data = value, add->Left = add->Right = NULL;
        pt->Right = add;
        return;
    }
    else if ((value) > (pt->Data)) // 左右节点都不为空，需要递归求解
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

void LevelorderTraversal(const BiTree &bt, int &cnt)
{
    if (!bt)
        return;
    queue<BiTree> lrtree;
    lrtree.push(bt);
    int flag = 0, ff = 0;
    while (!lrtree.empty())
    {
        BiTree tt = lrtree.front();
        if (tt) // 非空执行
        {
            if (flag == 0)
            {
                printf("%d", tt->Data);
                flag++;
            }
            else
            {
                printf(" %d", tt->Data);
            }

            if (ff == 0)
            {
                cnt++;      // 计算遇到空节点前遍历的节点总数目
            }

            lrtree.push(tt->Left);
            lrtree.push(tt->Right);
        }
        else        // 遇到空节点
        {
            ff++;   // 停止计数
        }

        lrtree.pop();
    }
}

int main()
{
    int N, cnt = 0;
    scanf("%d", &N);
    BiTree bt;
    InitBiTree(bt);

    for (int i = 1; i < N; i++)
    {
        int tt;
        scanf("%d", &tt);
        InsertNode(bt, tt); // 构造二叉树（还剩 N-1 个节点未加入）
    }

    LevelorderTraversal(bt, cnt);
    if (cnt == N)
        printf("\nYES");            // 这里注意和第一个题不一样，字母都是大写！！！！啊啊啊卡了好久！！
    else
        printf("\nNO");

    return 0;
}



/* 7-2 是否完全二叉搜索树 (30分)
将一系列给定数字顺序插入一个初始为空的二叉搜索树（定义为左子树键值大，右子树键值小），你需要判断最后的树是否一棵完全二叉树，并且给出其层序遍历的结果。

输入格式：
输入第一行给出一个不超过20的正整数N；第二行给出N个互不相同的正整数，其间以空格分隔。

输出格式：
将输入的N个正整数顺序插入一个初始为空的二叉搜索树。在第一行中输出结果树的层序遍历结果，数字间以1个空格分隔，行的首尾不得有多余空格。第二行输出YES，如果该树是完全二叉树；否则输出NO。

输入样例1：
9
38 45 42 24 58 30 67 12 51
输出样例1：
38 45 24 58 42 30 12 67 51
YES
输入样例2：
8
38 24 12 45 58 67 42 51
输出样例2：
38 45 24 58 42 12 67 51
NO */
