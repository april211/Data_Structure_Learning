#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <iostream>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

int main()
{
    int base = 1;
    vector<int> array;
    for(int i = 0; i< 1009; i++)
    {
        array.push_back(1 * base* base);
        array.push_back(-1* base* base);
        ++base;
    }
    for(int i = 0; i< 100; i++)
    {
        printf("%d ", array[i]);
    }

    return 0;
}