#include <sstream>
#include <fstream>
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
#include <functional>
#include <random>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
// ll M=1;
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

inline int lowbit(int x) {return x&-x;}
int val[20007][10007];
void update(int x,int y,int v) {
    // printf("update %d %d %d\n",x,y,v);
    for (int i=x;i<=2e4;i+=lowbit(i))
        for (int j=y;j<=1e4;j+=lowbit(j)) val[i][j]+=v;
}
int query(int x,int y) {
    int ret=0;
    for (int i=x;i;i-=lowbit(i))
        for (int j=y;j;j-=lowbit(j)) ret+=val[i][j];
    // printf("query %d %d ret = %d\n",x,y,ret);
    return ret;
}
int query(int xl,int xr,int yl,int yr) {
    // printf("query %d-%d, %d-%d\n",xl,xr,yl,yr);
    xl=max(xl,1); xr=min(xr,(int)2e4); yl=max(yl,1); yr=min(yr,(int)1e4);
    return query(xr,yr)-query(xl-1,yr)-query(xr,yl-1)+query(xl-1,yl-1);
}

array<int,2> A[maxn];
int main() {
    int n,k,q,i;
    ll ans=0;
    scanf("%d%d%d",&n,&k,&q);
    FOR(i,1,n) {
        scanf("%d%d",&A[i][0],&A[i][1]);
        if (A[i][0]<A[i][1]) swap(A[i][0],A[i][1]);
        int X=A[i][0]+A[i][1],Y=A[i][0]-A[i][1]+1;
        update(X,Y,1); ans+=query(X-k,X+k,Y-k,Y+k)-1;
        // printf("query=%d\n",query(X-k,X+k,Y-k,Y+k));
    }
    while (q--) {
        int op; scanf("%d",&op);
        if (op==1) printf("%lld\n",ans);
        else if (op==2) {
            int u; scanf("%d",&u);
            if (k>1e5) continue;
            k=min((ll)1e5,(ll)k*u);
            ans=0;
            FOR(i,1,n) {
                int X=A[i][0]+A[i][1],Y=A[i][0]-A[i][1]+1;
                ans+=query(X-k,X+k,Y-k,Y+k)-1;
            } ans/=2;
        } else {
            int o,x,y;
            scanf("%d%d%d",&o,&x,&y);
            int X,Y; if (x<y) swap(x,y);
            X=A[o][0]+A[o][1],Y=A[o][0]-A[o][1]+1;
            ans-=query(X-k,X+k,Y-k,Y+k)-1; update(X,Y,-1);
            A[o][0]=x; A[o][1]=y;
            X=A[o][0]+A[o][1],Y=A[o][0]-A[o][1]+1;
            update(X,Y,1); ans+=query(X-k,X+k,Y-k,Y+k)-1;
        }
    }
}
/*
*/