#include <cstdio>
#include <algorithm>
using namespace std;
typedef struct edge
{
    int u;
    int v;
    int c;
}edge;
int father[100001];
edge e[100001];
int N,M;
int findfather(int x)
{
    if(x==father[x])
        return x;
    else return father[x]=findfather(father[x]);
}
int Kruskal()
{
    int fa,fb,ret=0;
    for(int i=1;i<=N;i++)
        father[i]=i;
    for(int i=0;i<M;i++)
    {
        fa=findfather(e[i].u);
        fb=findfather(e[i].v);
        if(fa!=fb)
        {
            ret+=e[i].c;
            father[fb]=fa;
        }
    }
    int cnt=0;
    for (int i=1;i<=N;i++) if (findfather(i)!=i) cnt++;
    if (cnt==N-1) return ret;
    return 0;
}
bool cmp(edge a,edge b)
{
    return a.c<b.c;
}
int fibo[100001];
int main()
{
    int T,kase=0,minn,maxx,ed,le,ri;
    scanf("%d",&T);
    fibo[0]=1;
    fibo[1]=2;
    for(int i=2;;i++)
    {
        fibo[i]=fibo[i-1]+fibo[i-2];
        if(fibo[i]>500000)
        {
            ed=i+1;
            break;
        }
    }
    while(T--)
    {
        scanf("%d%d",&N,&M);
        for(int i=0;i<M;i++)
            scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].c);
        sort(e,e+M,cmp);
        minn=Kruskal();
        reverse(e,e+M);
        maxx=Kruskal();
        bool mark=0;
        for (int i=0;i<ed;i++) if (minn<=fibo[i]&&fibo[i]<=maxx) mark=1;
        printf("Case #%d: ",++kase);
        if(mark) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
/*
*/ 
