#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=100+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

LL f[107][107],g[107][107],h[107][107][107];
LL w[107],t[107];
LL dp[107][107][107];
LL ver[107];
int main() {
    LL x[107],y[107];
    int a,b,c,n;
    int i,j,k,_i,_j;
    scanf("%d%d%d%d",&a,&b,&c,&n);
    FOR(i,1,a) scanf("%lld",&x[i]);
    FOR(i,1,b) scanf("%lld",&y[i]);
    FOR(i,1,a) FOR(j,1,a) scanf("%lld",&f[i][j]);
    FOR(i,1,a) assert(f[i][i]==0);
    FOR(i,1,b) FOR(j,1,b) scanf("%lld",&g[i][j]);
    FOR(i,1,b) assert(g[i][i]==0);
    FOR(k,1,c) FOR(i,1,a) FOR(j,1,b) scanf("%lld",&h[k][i][j]);
    FOR(i,1,n) scanf("%lld",&w[i]),assert(w[i]>0);
    FOR(i,1,n) scanf("%lld",&t[i]),assert(t[i]<=c);
    FOR(k,1,a) FOR(i,1,a) FOR(j,1,a)
        f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
    FOR(k,1,b) FOR(i,1,b) FOR(j,1,b)
        g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
    memset(dp,0x3f,sizeof(dp));
    FOR(i,1,a) FOR(j,1,b) dp[0][i][j]=x[i]+y[j];
    FOR(k,1,n){
        FOR(i,1,a){
            memset(ver,0x3f,sizeof(ver));
            FOR(j,1,b){
                FOR(_i,1,a){
                    ver[j]=min(ver[j],dp[k-1][_i][j]+f[_i][i]);
                }
            }FOR(j,1,b){
                FOR(_j,1,b){
                    dp[k][i][j]=min(dp[k][i][j],ver[_j]+g[_j][j]);
                }
                dp[k][i][j]+=(w[k]+h[t[k]][i][j]-1)/h[t[k]][i][j];
            }
        }
    }LL ans=INFF;
    FOR(i,1,a) FOR(j,1,b) ans=min(ans,dp[n][i][j]);
    assert(ans!=INFF);
    printf("%lld\n",ans);
    return 0;
}
/*
*/
