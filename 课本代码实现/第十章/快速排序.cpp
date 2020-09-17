#include <cstdio>
#include <cmath>
#include <cstdlib>

// 分治法 + 挖坑填坑
int Partition(int *raw, int low, int high)
{
    int pivot = raw[low];                       // 设置基点值
    while(low < high)
    {
        while(low < high && raw[high] >= pivot) // 元素不需要改变位置
            --high;
        raw[low] = raw[high];
        while(low < high && raw[low]  <= pivot) // 元素不需要改变位置
            ++low;
        raw[high] = raw[low];
    }
    raw[low] = pivot;
    return low;
}

void QSort(int *raw, int low, int high)
{
    if(low >= high) return;                            // 指定长度非法
    int pivot_location = Partition(raw, low, high);    // 将数组一分为二
    QSort(raw, low, pivot_location - 1);               // 低子表递归
    QSort(raw, pivot_location + 1, high);              // 高子表递归
}

int main()
{
    int *raw = (int*)malloc(5* sizeof(int));
    raw[0] = 3;
    raw[1] = 100;
    raw[2] = 99;
    raw[3] = 44;
    raw[4] = 1000;

    QSort(raw, 0, 4);

    for(int i = 0; i< 5; i++)
    {
        printf("%d\n", raw[i]);
    }

    return 0;
}

// 推荐博文：https://blog.csdn.net/morewindows/article/details/6684558
