#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
char ans[100001];
int sa[100001],rk[100001],father[100001];
int ma[200001];
vector<int> mp[100001];
int findfather(int x)
{
    if(x==father[x])
        return x;
    else return father[x]=findfather(father[x]);
}
int main()
{
    int T,kase=0,N,cur,id,mx,left,right;
    bool fail;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        for(int i=0;i<N;i++)
        {
            scanf("%d",&sa[i]);
            rk[sa[i]]=i;
            father[i]=i;
        }
        rk[N]=-1;
        for(int i=0;i<N-1;i++)
            if(rk[sa[i]+1]>rk[sa[i+1]+1])
                mp[i+1].push_back(i);
        ma[0]=0;
        ma[2*N]=0;
        for(int i=1;i<2*N;i++)
            scanf("%d",&ma[i]);
        fail=false;
        id=0;
        mx=1;
        for(int i=1;i<2*N&&!fail;i++)
        {
            if(i<mx)
                cur=min(mx-i,ma[id*2-i]+1);
            else cur=1;
            if(ma[i]<cur-1||i-ma[i]<0||i+ma[i]>2*N)
                fail=true;
            for(left=i-cur,right=i+cur;right<=i+ma[i]&&!fail;left--,right++)
            {
                if(left&1)
                {
                    int u=rk[left/2],v=rk[right/2];
                    if(u>v)
                        swap(u,v);
                    for(u=findfather(u);u<v&&!fail;v--)
                    {
                        v=findfather(v);
                        if(u>=v)
                            break;
                        for(int j=0;j<mp[v].size();j++)
                            if(mp[v][j]>=u)
                            {
                                fail=true;
                                break;
                            }
                        father[v]=u;
                    }
                }
            }
            if(left>=1&&right<=2*N-1&&((left&1)^1))
                fail=true;
            if(!fail&&left>=1&&right<=2*N-1)
            {
                int u=rk[left/2],v=rk[right/2];
                u=findfather(u);
                v=findfather(v);
                if(u>v)
                    swap(u,v);
                mp[v].push_back(u);
            }
            if(i+ma[i]+1>mx)
            {
                mx=i+ma[i]+1;
                id=i;
            }
        }
        char pre='a';
        for(int i=0,j=0;i<N&&!fail;i=j)
        {
            char curr=pre;
            while(j<N&&findfather(j)==findfather(i))
                j++;
            for(int k=i;k<j;k++)
            {
                for(int it=0;it<mp[k].size()&&!fail;it++)
                    if(findfather(mp[k][it])==findfather(i))
                        fail=true;
                    else curr=max(int(curr),ans[sa[mp[k][it]]]+1);
            }
            if(curr>'z')
                fail=true;
            else
            {
                for(;i<j;i++)
                    ans[sa[i]]=curr;
                pre=curr;
            }
        }
        ans[N]='\0';
        if(fail)
            printf("Case #%d: Wrong calculation!\n",++kase);
        else printf("Case #%d: %s\n",++kase,ans);
        for(int i=0;i<N;i++)
            mp[i].clear();
    }
    return 0;
}
