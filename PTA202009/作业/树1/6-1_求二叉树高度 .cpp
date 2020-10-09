#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;

struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

int CreatBinTree(BinTree *bt);
int GetHeight(BinTree BT);

int main()
{

    BinTree BT;
    CreatBinTree(&BT);
    printf("%d\n", GetHeight(BT));
    return 0;
}

// 按照前序遍历规则创建二叉树（bt: 指向 TNode指针的指针）
// 如果这里的参数不是引用（Cpp才可以用）或者此形式，将会丢失递归时分配的空间（传参拷贝）
int CreatBinTree(BinTree *bt)   
{
    char ch;
    scanf("%c", &ch); // 不能以回车结束，字母之间不能有多余空格
    if (ch == ' ')
    {
        *bt = NULL;
    }
    else
    {
        *bt = (TNode *)malloc(sizeof(TNode));
        if (!(*bt))
            exit(-2);
        (*bt)->Data = ch;
        CreatBinTree(&((*bt)->Left));   // 注意：参数是指向指针的指针（指针的地址）
        CreatBinTree(&((*bt)->Right));
    }
    return 0;

/*     bt = (TNode*)malloc(sizeof(TNode));
    bt->Data = 'A';
    bt->Left = (TNode*)malloc(sizeof(TNode));
    bt->Right = NULL;
    bt->Left->Right = NULL;
    bt->Left->Left = NULL;
    bt->Left->Data = 'B';
    return bt; */
}
int GetHeight(BinTree BT)
{
    int depth;

    if (BT == NULL)
    {
        depth = 0;
    }
    else
    {
        // 必须选择后序遍历以获取左右子树深度的最大值
        //printf("<<<<<<\n");
        int d1 = GetHeight(BT->Left);
        int d2 = GetHeight(BT->Right);
        depth = ((d1 > d2) ? d1 : d2) + 1;
    }
    return depth;
}

//ABC  DE G  F   */