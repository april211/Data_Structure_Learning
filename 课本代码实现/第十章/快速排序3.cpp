#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

template<class Type>
void Swap(Type &a, Type &b)
{
    Type tt = a;
    a = b;
    b = tt;
}

template<class Type>
int Partition(Type a[], int l, int pivot)
{
    // 选取最右端点为基准元素，并且从大到小排序
    int i = l-1, j = pivot;             
    Type x = a[pivot];                      
    while(1)
    {
        while(a[++i] > x && i < pivot);     // 保证 i 与 j 不会越界
        while(a[--j] < x);     
        if(i >= j) break;                   // i 与 j 发生交叉，找到了基准元素应在的位置
        else Swap(a[i], a[j]);              // 未发生交叉，则应当交换这两个元素，使
    }
    a[pivot] = a[i];                        // 将占有 pivot 应当存放的位置上的元素挖出来，并填到现在 pivot 元素的位置
    a[i] = x;                               // 将之前挖出来的 pivot 元素填到上一步挖出来的坑上

    return i;                           // 返回此时 pivot 元素的下标
}

template<class Type>
void QuickSort(Type a[], int l, int r)
{
    if(l < r)       // 保证符合实际意义，不符合时 “什么也不做 ”（相当于 return）
    {
        int q = Partition(a, l, r);
        QuickSort(a, l, q-1);
        QuickSort(a, q+1, r);
    }
}


int main()
{
    int a[] = {5, 2, -1, -3,-2, 0, 6};
    int N = sizeof(a)/sizeof(int);
    QuickSort(a, 0, N-1);                 // 0 ~ N-1
    for(int i = 0; i< N; i++)
    {
        printf("%d ", a[i]);
    }
}

/*     for(int k = 0; k <= r; k++)      // 这是供检查使用的代码，可以拷贝到 Partition 函数的特定位置来检查变化
    {
        printf("%d ", a[i]);
    }
    printf("\n"); */
    