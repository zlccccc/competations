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
#define mod 998244353
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3000+7;
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

LL A[maxn];
LL Rsum[maxn];
LL f[maxn][maxn],g[maxn];
int main() {
    int n,i,j;
    freopen("ebola.in","r",stdin);
    freopen("ebola.out","w",stdout);
    while(scanf("%d",&n)!=EOF&&n){
        FOR(i,1,n) scanf("%I64d",&A[i]);
        FOR(i,1,n+1) FOR(j,1,n+1) f[i][j]=0;
        FOR(i,1,n+1) g[i]=Rsum[i]=0;
        FOR(j,1,n){
            LL R=0,sum=0;
            rFOR(i,1,j){
                f[i][j]=f[i+1][j]+sum+min(sum,A[i]*R);
                R+=3;sum+=A[i];
            }
        }
//        FOR(i,1,n){
//            FOR(j,i,n) printf("%I64d ",f[i][j]);
//            puts("");
//        }
        rFOR(i,1,n) Rsum[i]=Rsum[i+1]+A[i];
        FOR(i,1,n) {
            g[i]=INFF;
            LL sum=0;
            rFOR(j,1,i){
                g[i]=min(g[i],g[j-1]+f[j][i]+((i-j)*4+2)*Rsum[i+1]);
            }
        }printf("%I64d\n",g[n]);
//        FOR(i,1,n) printf("%I64d ",Rsum[i]);puts("");
//        FOR(i,1,n) printf("%I64d ",g[i]);
    }
    return 0;
}
/*
*/
