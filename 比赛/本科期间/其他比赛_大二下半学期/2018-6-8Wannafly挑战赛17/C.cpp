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
const LL M=998244353;
const LL maxn=1<<20|7;
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

inline int lowbit(int x){return x&-x;}
int n;
int bit[maxn],h[maxn];
LL mask[maxn][27];
LL ans[maxn];
int edge[27][27];
int main() {
    int i,j,k,n,m,p;
    rep(i,2,(1<<20)) h[i]=h[i>>1]+1;
    rep(i,1,(1<<20)) bit[i]=bit[i>>1]+(i&1);
    scanf("%d%d%d",&n,&m,&p);
    REP(i,m) {
        int u,v;
        scanf("%d%d",&u,&v);u--;v--;
        edge[u][v]=edge[v][u]=1;
    }
    REP(i,n) mask[1<<i][i]=1;//插头i
    REP(i,(1<<n)){
        int low=h[lowbit(i)];
        rep(j,low,n) if (mask[i][j]){
            if (edge[low][j]&&bit[i]>2) {
                ans[bit[i]%p]+=mask[i][j];
//                rREP(k,n) debug("%d",(i>>k)&1);debug("  (%d)\n",bit[i]);
            }
            rep(k,low,n) if (!((i>>k)&1)&&edge[j][k])
                mask[i|(1<<k)][k]+=mask[i][j];
        }
    }REP(i,p) printf("%lld\n",(ans[i]/2)%M);
    return 0;
}
/*
8 28 20
1 2
1 3
1 4
1 5
1 6
1 7
1 8
2 3
2 4
2 5
2 6
2 7
2 8
3 4
3 5
3 6
3 7
3 8
4 5
4 6
4 7
4 8
5 6
5 7
5 8
6 7
6 8
7 8

*/
