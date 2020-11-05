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
int Partition(Type a[], int p, int r)
{
    int i = p, j = r+1;
    Type x = a[p];
    while(1)
    {
        while(a[++i] < x && i < r);
        while(a[--j] > x);
        if(i >= j) break;
        Swap(a[i], a[j]);
    }
    a[p] = a[j];
    a[j] = x;
    return j;
}

template<class Type>
void QuickSort(Type a[], int p, int r)
{
    if(p < r)
    {
        int q = Partition(a, p, r);
        QuickSort(a, p, q-1);
        QuickSort(a, q+1, r);
    }
}


int main()
{
    int a[] = {2, 3, 7, 4, 9, 0, 1};
    QuickSort(a, 0, 6);
    for(int i = 0; i< 7; i++)
    {
        printf("%d ", a[i]);
    }
}

