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
const int MAX=5e4+7;
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
int n,k;
int dp[MAX][205];
int a[MAX];
int mi[(int)2e5+5];
int len[MAX];
ll an;
int he;//从前到现在的和
int mihe;
int shige,nowhe;

int mod_cnt[205];
int mod_an[MAX];
int main()
{
//    freopen("out.txt","r",stdin);
//    freopen("not.txt","w",stdout);
    while(scanf("%d%d",&n,&k)!=EOF)
    {
        he=mihe=0;
        int i,j,s;
        mi[0]=1%k;
        FOR(i,1,4*n+2)
            mi[i]=10*mi[i-1]%k;
        memset(dp[0],0,201*sizeof(int));
        memset(mod_cnt,0,sizeof(mod_cnt));
        memset(mod_an,0,sizeof(mod_an));
        REP(i,n)
        {
            scanf("%d",&a[i]);
            len[i]=1+log10(a[i])+eps;
        }
        shige=0;nowhe=0;
        for(i=n-1;i>=0;i--)
        {
            nowhe=(a[i]*mi[shige]%k+nowhe)%k;
            mod_an[i]=nowhe;
            shige+=len[i];
            ++mod_cnt[nowhe];
        }
        an=0;
        REP(i,n)
        {
            memset(dp[i],0,201*sizeof(int));
            --mod_cnt[mod_an[i]];
            mihe+=len[i];
            he=(he*mi[len[i]]%k+a[i])%k;//从0到现在的数
            int tem=a[i]%k;
            ++dp[i][tem];
            if(!i)
            {
                FOR(j,0,k-1)
                {
                    if((j*mi[mihe]%k+he)%k==0)
                    {
//                        if(mod_cnt[j])
//                        printf("!!\n");
                            an+=mod_cnt[j];
                    }
                }
                continue;
            }
            FOR(j,0,k-1)
            {
                int l=len[i];
                int now=(j*mi[l]%k+tem)%k;
                dp[i][now]+=dp[i-1][j];
                if((j*mi[mihe]%k+he)%k==0)
                {
                    an+=mod_cnt[j];
                }
            }
        }
        FOR(i,0,n-1)
        {
//            if(dp[i][0])
//                printf("%d\n",i);
            an+=dp[i][0];
        }
        printf("%lld\n",an);
    }
    return 0;
}
/*
1 4
481 361 465 467
*/
