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
int Partition(Type a[], int pivot, int r)
{
    int i = pivot, j = r+1;             // 这里默认的 pivot 元素是最左边的元素
    Type x = a[pivot];                  // 将 pivot 处的元素挖出来 
    while(1)
    {
        while(a[++i] < x && i < r);     // 保证 i 与 j 不会越界
        while(a[--j] > x);     
        if(i >= j) break;               // i 与 j 发生交叉，找到了基准元素应在的位置
        else Swap(a[i], a[j]);          // 未发生交叉，则应当交换这两个元素，使
    }
    a[pivot] = a[j];                    // 将占有 pivot 应当存放的位置上的元素挖出来，并填到现在 pivot 元素的位置
    a[j] = x;                           // 将之前挖出来的 pivot 元素填到上一步挖出来的坑上
    return j;                           // 返回此时 pivot 元素的下标
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
    int a[] = {2, 3, 7, 30, 4, 9, 0, -1};
    QuickSort(a, 0, 7);                 // 0 ~ N-1
    for(int i = 0; i< 8; i++)
    {
        printf("%d ", a[i]);
    }
}

