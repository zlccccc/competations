#include <sstream>
#include <fstream>
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

#define DEBUG
#ifdef DEBUG
#define dbg(x) cerr <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cerr <<#x<<" = "<<x<<endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#define dbg(x)
#define dbgln(x)
#endif // DEBUG
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=5000+7;
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

LL pre[1<<15|7],now[1<<15|7];
LL ans[17][17];
int getnext(int status,int pos,int n){
    while ((status>>pos)&1) pos++;
    if (pos==n) return -1;
    return status|(1<<pos);
}
void solve(int n){
    int i,j;
    memset(pre,0,sizeof(pre));
    pre[0]=1;
    FOR(i,1,n){
        int status,nextstatus;
        memset(now,0,sizeof(now));
        REP(status,(1<<n)) if (pre[status]){
            REP(j,n){
                nextstatus=getnext(status,j,n);
                if (nextstatus==-1) continue;
                now[nextstatus]+=pre[status];
            }
        }memcpy(pre,now,sizeof(now));
        REP(status,(1<<n))
            ans[n][i]+=now[status];
    }
//    FOR(i,1,n) printf("%lld ",ans[n][i]);puts("");
}
int main() {
    int i,j,k,t,q;
    FOR(i,1,10) solve(i);
    scanf("%d",&q);
    while (q--){
        int n,k;
        scanf("%d%d",&k,&n);
        LL ans1,ans2,gg;
        ans2=1;
        FOR(i,1,k) ans2*=n;
        ans1=ans2-ans[n][k];
//        printf("%lld / %lld\n",ans1,ans2);
        gg=gcd(ans1,ans2);
        if (ans1==0) puts("0/1");
        else printf("%lld/%lld\n",ans1/gg,ans2/gg);
    }
    return 0;
}
/*
*/
