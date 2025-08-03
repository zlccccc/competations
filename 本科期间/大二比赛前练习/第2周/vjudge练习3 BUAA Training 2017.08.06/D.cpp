#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ull;
typedef long long ll;
const int INF=0x3f3f3f3f;
const ll INFF=0x3f3f3f3f3f3f3f3fll;
const ll M=1e9+7;
const ll maxn=1e5+7;
const int MAXN=1005;
const int MAX=2e3+5;
const int MAX_N=MAX;
const ll MOD=1e9+7;
//const double eps=0.00000001;
//ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a,ll b,ll M){
    ll ret=1;
    a%=M;
//    b%=M;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
}
ll dp[MAX][MAX];
int t[MAX];
int sum[MAX];//Ç°×ººÍ
int Case;
int n;
ll dfs(int lo,int yu)
{
//    printf("lo=%d yu=%d\n",lo,yu);
    if(dp[lo][yu]>=0LL)
        return dp[lo][yu];
    if(yu<lo||yu>sum[lo]+lo)
        return dp[lo][yu]=0LL;
    if(lo==1)
        return dp[lo][yu]=1;
    ll re=0;
    for(int i=1;i<=t[lo]+1;i++)
    {
        re=(re+dfs(lo-1,yu-i))%MOD;
//        printf("re=%lld\n",re);
    }
    return dp[lo][yu]=re;
}
int main()
{
    scanf("%d",&Case);
    while(Case--)
    {
        memset(dp,-1,sizeof(dp));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&t[i]);
        sort(t+1,t+1+n);
        for(int i=1;i<=n;i++)
            sum[i]=sum[i-1]+t[i];
//        printf("sum[n]=%d\n",sum[n]);
//        sum[n+1]=sum[n]+1;
//        t[n+1]=0;
        printf("%lld\n",dfs(n,(sum[n]+1)/2+n));
    }
}
/*
2
10
100 100 1000 100 100 100 100 100 100 100
*/
