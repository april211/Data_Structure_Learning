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
int Partition(Type a[], int l, int r)
{
    int i = l, j = r+1;       
    Type x = a[r];                  
    while(1)
    {
        while(a[++i] < x && i < r);   
        while(a[--j] > x);   
        printf("...........\n");   
        if(i >= j) break;               
        else Swap(a[i], a[j]);     
            
    }
    a[r] = a[j];                    
    a[j] = x;              
    printf("############\n");          

    return j;                          
}

template<class Type>
void QuickSort(Type a[], int l, int r)
{
    if(l < r)       
    {
        int q = Partition(a, l, r);
        QuickSort(a, l, q-1);
        QuickSort(a, q+1, r);
    }
}


int main()
{
    int a[] = {5, 2, 6};
    int N = sizeof(a)/sizeof(int);
    QuickSort(a, 0, N-1);                 // 0 ~ N-1
    for(int i = 0; i< N; i++)
    {
        printf("%d ", a[i]);
    }       // 不会发生任何变化
}

/*     for(int i = 0; i <= r; i++)      // 这是供检查使用的代码，可以拷贝到 Partition 函数的特定位置来检查变化
    {
        printf("%d ", a[i]);
    }
    printf("\n"); */
    