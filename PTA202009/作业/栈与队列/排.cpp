#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;
struct Node
{
    int T;
    int P;
};
Node q[1005];
int main()
{
    int N,hNode=0,tNode=0,i,K;//head,tail
    cin>>N;
    for(i=0;i<N;i++)
    {
        cin>>q[tNode].T>>q[tNode].P;
         if(q[tNode].P > 60) q[tNode].P = 60;
        tNode++;
    }
    cin>>K;
    int sumwait=0,maxwait=0,wait=0;//总等待，最长等待，单次等待
    int sum[15]={0},people[15]={0};
    while(hNode<tNode)
    {
        int f = 0,minn=9999,imin=0;
        for(i=0;i<K;i++)
        {
            if(sum[i]<=q[hNode].T)
            {
                sum[i]=q[hNode].T+q[hNode].P;
                people[i]++;//窗口人数加一
                f= 1;//标记一下，代表不需要等待
                hNode++;//队列首位除去
                break;//退出循环
            }
            if(minn>sum[i])
            {
                minn=sum[i];
                imin = i;
            }
        }
         if(!f)//需要等待
        {
            wait = minn - q[hNode].T;//等待的时间，最快完成的时间减去队列第一个人到达的时间
            if(maxwait < wait) maxwait = wait;//不断更新等待的最长时间
            sumwait += wait;//求等待时间的和
            sum[imin] = minn + q[hNode].P;//更新对应窗口的完成时间
            people[imin]++;//对应窗口人数++
            hNode++;//队列删除首位
        }
    }
    int last = 0;
    for(i = 0; i < K; i++)
    {
        if(last < sum[i]) last = sum[i];//求最大完成时间
    }
    printf("%.1lf %d %d\n", 1.0 * sumwait / N, maxwait, last);//输出，平均等待时间， 最长等待时间， 最后完成时间
    for(i = 0; i < K; i++)
    {
        printf("%d", people[i]);//输出各个窗口的人数
        if(i == K - 1) printf("\n");
        else printf(" ");
    }
 
    return 0;
}