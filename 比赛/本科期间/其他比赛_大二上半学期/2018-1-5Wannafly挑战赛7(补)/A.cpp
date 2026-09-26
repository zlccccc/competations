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
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

LL n,m,R,C,K;
LL ans;
inline LL solve(int n,int m){
    if (n==0||m==0) return 0;
    if (n<K||m<K) return INFF/4;
    return ((n+K-1)/K)*((m+K-1)/K);
}
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
        scanf("%lld%lld%lld%lld%lld",&n,&m,&R,&C,&K);
        ans=0;
        ans+=solve(R-1,C-1);
        ans+=solve(R-1,m-C);
        ans+=solve(n-R,C-1);
        ans+=solve(n-R,m-C);
        if (ans>INFF/5) puts("-1");
        else printf("%lld\n",ans);
    }
}
/*
3
1 1 1 1 2
2 2 1 1 2
3 3 2 2 2
*/
