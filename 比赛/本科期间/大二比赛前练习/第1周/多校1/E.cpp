#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <list>
#include <vector>
#include <stack>
#define mp make_pair
//#define P make_pair
#define MIN(a,b) (a>b?b:a)
//#define MAX(a,b) (a>b?a:b)
typedef long long ll;
typedef unsigned long long ull;
const int MAX=1e6+5;
const int INF=1e8+5;
using namespace std;
const ll MOD=1e9+7;
typedef pair<ll,int> pii;
const double eps=0.00000001;
int n,m;
int a[MAX],b[MAX];
bool via[MAX],vib[MAX];
int len;
int num=0;
map<int,int> ring_b;
int dfs_a(int i,int len)
{
    via[i]=true;
    if(via[a[i]])
    {
        return len;
    }
    else
        return dfs_a(a[i],len+1);
}
void dfs_b(int i,int len)
{
    vib[i]=true;
    if(vib[b[i]])
        ++ring_b[len];
    else
        dfs_b(b[i],len+1);
}
ll an=0;
bool st;
int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        st=false;
        ++num;
        an=1;
        ring_b.clear();
        memset(via,false,sizeof(via));
        memset(vib,false,sizeof(vib));
        for(int i=0;i<n;i++)
            scanf("%d",&a[i]);
        for(int i=0;i<m;i++)
            scanf("%d",&b[i]);
        for(int i=0;i<m;i++)
        {
            if(!vib[i])
                dfs_b(i,1);
        }
        for(int i=0;i<n;i++)
        {
            if(!via[i])
            {
                ll tem=(ll)dfs_a(i,1);
                ll oh=0;
                for(ll i=1;i<=tem;i++)
                {
                    if(ring_b[i]&&tem%i==0)
                    {
                        st=true;
                        oh=(oh+ring_b[i]%MOD*i%MOD)%MOD;
                    }
                }
                an=an*oh%MOD;
            }
        }
        while(an<0)
            an+=MOD;
        if(st)
            printf("Case #%d: %lld\n",num,an%MOD);
        else
            printf("Case #%d: %lld\n",num,0);
    }
    return 0;
}


