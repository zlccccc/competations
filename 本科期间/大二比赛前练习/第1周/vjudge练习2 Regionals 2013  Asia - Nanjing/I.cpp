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
const ll M=1e6+3;
const ll maxn=1e5+7;
const int MAX=1e5+7;
const ll MOD=1e6+3;
const double eps=0.00000001;
ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a,ll b){
    ll ret=1;
    while (b){
        if (b&1) ret=ret*a%M;
        b>>=1;
        a=a*a%M;
    }
    return ret;
}
ll n;
ll num[2][MAX],tot;
ll fact[2005];
ll inv[2005];
ll an;
ll C(ll n,ll m)
{
    if(n==0&&m==0)
        return 1LL;
    return fact[n]*inv[n-m]%M*inv[m]%M;
}
int main()
{
    fact[0]=1LL;
    //inv[0]=1;
    fact[1]=1;
    for(ll i=2;i<=2002;i++)
    {
        fact[i]=i*fact[i-1]%MOD;
    }
    inv[2002]=powMM(fact[2002],MOD-2);
    for(ll i=2001;i>=1;i--)
    {
        inv[i]=inv[i+1]*(i+1)%MOD;
    }
    inv[0]=1LL;
//    printf("%lld\n",inv[0]);
//    inv[0]=1LL;
    while(~scanf("%lld",&n))
    {
        memset(num,0,sizeof(num));
        tot=0;
        for(ll i=1;i<=n;i++)
        {
            ll x,wei=0;
            scanf("%lld",&x);
            for(ll j=0;j<=32;j++)
            {
                if(x&1)
                    ++num[1][j];
                else
                    ++num[0][j];
                x/=2;
            }
//            tot=max(wei-1,tot);
        }
//        for(ll i=0;i<=tot;i++)
//            printf("%lld ",num[0][i]);
//        system("pause");
        an=0;
        for(ll z=1;z<=n;z++)
        {
            an=0;
            ll er_mi=1;
            for(ll i=0;i<=32;i++)
            {
                ll ling_min=max(0LL,z-num[1][i]);
                ll ling_max=num[0][i];
                ll yi_min=max(0LL,z-num[0][i]);
                ll yi_max=num[1][i];
                ll st=yi_min;
                if(st%2==0)
                    ++st;
//                printf("0min%lld 0max%lld 1min%lld 1max%lld\n",ling_min,ling_max,yi_min,yi_max);
                ll cnt=0;
//                printf("!!!!!%lld\n",i);
                for(ll j=st;j<=min(num[1][i],z);j+=2LL)//odd
                {
                    cnt=(cnt+C(yi_max,j)*C(ling_max,z-j))%M;
//                    printf("%lld %lld %lld %lld \n",yi_max,j,ling_max,z-j);
                }
                an=(an+er_mi*cnt%M)%M;
//                printf("~%lld %lld\n",er_mi,cnt);
                er_mi=er_mi*2LL%M;
                //system("pause");
            }
            if(z>1LL)
                printf(" ");
            printf("%lld",an);
        }
        printf("\n");
    }
    return 0;
}
