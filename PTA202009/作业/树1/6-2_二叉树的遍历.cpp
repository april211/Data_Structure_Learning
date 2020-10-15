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
void InorderTraversal(BinTree BT);
void PreorderTraversal(BinTree BT);
void PostorderTraversal(BinTree BT);
void LevelorderTraversal(BinTree BT);

int main()
{
    BinTree BT;
    CreatBinTree(&BT);
    printf("Inorder:");
    InorderTraversal(BT);
    printf("\n");
    printf("Preorder:");
    PreorderTraversal(BT);
    printf("\n");
    printf("Postorder:");
    PostorderTraversal(BT);
    printf("\n");
    printf("Levelorder:");
    LevelorderTraversal(BT);
    printf("\n");
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
        CreatBinTree(&((*bt)->Left)); // 注意：参数是指向指针的指针（指针的地址）
        CreatBinTree(&((*bt)->Right));
    }
    return 0;
}

// 中序遍历
void InorderTraversal(BinTree BT)
{
    if (!BT)
        return;
    else
    {
        InorderTraversal(BT->Left);
        printf(" %c", BT->Data);
        InorderTraversal(BT->Right);
    }
}

// 前序遍历
void PreorderTraversal(BinTree BT)
{
    if (!BT)
        return;
    else
    {
        printf(" %c", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}

// 后序遍历
void PostorderTraversal(BinTree BT)
{
    if (!BT)
        return;
    else
    {
        PostorderTraversal(BT->Left);
        PostorderTraversal(BT->Right);
        printf(" %c", BT->Data);
    }
}

// 层序遍历（模拟队列实现）
void LevelorderTraversal(BinTree BT)
{
    if (!BT)
        return;
    BinTree temp[400];  // 顺序队列（图省事，题目限定编译头，且不让用 C++）
    int in = 0;
    int out = 0;

    temp[in++] = BT; // root

    while (in > out)    // 队列为空时，树就遍历完了
    {
        if (temp[out])  // 该指针不是空的，输出它所指向的节点的值，并把他的左右孩子入队列
        {
            printf(" %c", temp[out]->Data);
            temp[in++] = temp[out]->Left;
            temp[in++] = temp[out]->Right;
        }
        out++;          // 原节点出队列
    }
}


/* ABDH  I  EJ  K  CFL  M  GN  O  
Inorder: H D I B J E K A L F M C N G O
Preorder: A B D H I E J K C F L M G N O
Postorder: H I D J K E B L M F N O G C A
Levelorder: A B C D E F G H I J K L M N O */

/* 6-2 二叉树的遍历 (25分)
本题要求给定二叉树的4种遍历。

函数接口定义：
void InorderTraversal( BinTree BT );
void PreorderTraversal( BinTree BT );
void PostorderTraversal( BinTree BT );
void LevelorderTraversal( BinTree BT );
其中BinTree结构定义如下：

typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};
要求4个函数分别按照访问顺序打印出结点的内容，格式为一个空格跟着一个字符。

裁判测试程序样例：
#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree(); */ /* 实现细节忽略 */
/* void InorderTraversal( BinTree BT );
void PreorderTraversal( BinTree BT );
void PostorderTraversal( BinTree BT );
void LevelorderTraversal( BinTree BT );

int main()
{
    BinTree BT = CreatBinTree();
    printf("Inorder:");    InorderTraversal(BT);    printf("\n");
    printf("Preorder:");   PreorderTraversal(BT);   printf("\n");
    printf("Postorder:");  PostorderTraversal(BT);  printf("\n");
    printf("Levelorder:"); LevelorderTraversal(BT); printf("\n");
    return 0;
} */
/* 你的代码将被嵌在这里 */
/* 输出样例（对于图中给出的树）：


Inorder: D B E F A G H C I
Preorder: A B D F E C G H I
Postorder: D E F B H G I C A
Levelorder: A B C D F G I E H
作者
陈越
单位
浙江大学
代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB
 */
