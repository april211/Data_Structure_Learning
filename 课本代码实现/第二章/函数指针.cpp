#include <cstdio>
#include <cstdlib>

int Func (int x, int y)
{
    return 1114;
}



int main()
{
    int a = 11, b = 14, c = 28;
    int (*pt)(int, int);        // 定义一个函数指针
    pt = Func;
    c = (*pt)(a, b);            // 通过函数指针调用函数
    printf("%d\n", c);

}

