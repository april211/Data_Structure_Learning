#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int mm[10011][10011];

struct TNode
{
    int space;
    int prior;               
    char name[261];          
    struct TNode *son, *sib; 
};

int cmp(struct TNode *p, struct TNode *q)
{
    if (p->prior > q->prior)
        return 1;
    if (p->prior == q->prior)
    {
        if (strcmp(p->name, q->name) < 0)
            return 1;
        if (strcmp(p->name, q->name) == 0)
            return -1;
    }
    return 0;
}

struct TNode *NewNode(struct TNode *root, char *name, int prior)
{ 
    struct TNode *node;
    node = (struct TNode *)malloc(sizeof(struct TNode));
    strcpy(node->name, name);
    node->sib = node->son = NULL;
    node->prior = prior;
    node->space = root->space + 2;
    return node;
}

struct TNode *Add(struct TNode *root, char *name, int prior)
{
    struct TNode *p = root;
    struct TNode *node = NewNode(root, name, prior);
    if (p->son == NULL)
    {
        p->son = node;
        return p->son;
    }
    else
    {
        if (cmp(node, p->son) == 1)
        { 
            node->sib = p->son;
            p->son = node;
            return p->son;
        }
        else if (cmp(node, p->son) == -1)
        { 
            return p->son;
        }
        else
        {
            p = p->son;
            while (p->sib)
            {
                if (cmp(node, p->sib) == 1)
                { 
                    node->sib = p->sib;
                    p->sib = node;
                    return p->sib;
                }
                else if (cmp(node, p->sib) == -1)
                { 
                    return p->sib;
                }
                p = p->sib;
            }
            if (!p->sib)
            {
                p->sib = node;
                return p->sib;
            }
        }
    }
}

int IsChar(char c)
{ 
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    return 0;
}


void Out(struct TNode *root)
{
    int i;
    if (root)
    {
        for (i = 0; i < root->space; i++)
        {
            printf(" ");
        }
        printf("%s\n", root->name);
        Out(root->son);
        Out(root->sib);
    }
}


int main()
{
    struct TNode *root = (struct TNode *)malloc(sizeof(struct TNode));
    root->sib = root->son = NULL;
    root->space = 0;
    root->prior = 1;
    strcpy(root->name, "root");
    char input[261];
    int n = -1;
    scanf("%d", &n);
    int i = -1;
    for (i = 0; i < n; i++)
    {
        scanf("%s", input);
        int j = -1, k = 0, prior = 0;
        char name[261];
        struct TNode *p = root;
        for (j = 0; input[j] != '\0'; j++)
        {
            if (IsChar(input[j]))
                name[k++] = input[j];
            else if (input[j] == '\\')
            {
                name[k] = '\0';
                prior = 1;
                p = Add(p, name, prior);
                k = 0;
            }
        }
        if (input[j] == '\0' && IsChar(input[j - 1]))
        {
            name[k] = '\0';
            prior = 0;
            p = Add(p, name, prior);
        }
    }
    Out(root);
    return 0;
}
