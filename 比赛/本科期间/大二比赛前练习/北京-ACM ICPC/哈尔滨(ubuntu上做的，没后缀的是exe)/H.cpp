#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <string>
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;
const int INF=0x3f3f3f3;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const int maxn=1e5+7;
typedef long long ll;
int t,n;
int a[maxn];
int prime[maxn+1];
ll sum,dive,an;
ll check(ll who)
{
    ll he=0;
    for(int i=1;i<=n;i++)
        he+=min(a[i]%who,who-a[i]%who);
    return he/2;
}
void getPrime()
{
    for(int i=2;i<=100000;i++)
    {
        if(!prime[i])
        prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&prime[j]<=100000/i;j++)
        {
            prime[prime[j]*i]=1;
            if(i%prime[j]==0)break;
        }

    }
}
int main()
{
    scanf("%d",&t);
    getPrime();
    while(t--)
    {
        sum=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&a[i]);
            sum+=a[i];
        }
        dive=1;
        an=INFF;
        while(sum>1&&sum>=prime[dive]&&dive<=prime[0])
        {
            ll who=prime[dive];
            if(sum%who==0)
                an=min(an,check(who));
            while(sum%who==0)
                sum/=who;
            dive++;
        }
        if(sum>1)
            an=min(an,check(sum));
        printf("%lld\n",an);
    }
	return 0;
}

