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
const LL maxn=1e6+107;
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
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

int c[maxn],A[maxn];
ll e[47];
int v1[1<<20|7],v2[1<<20|7],p[1<<20|7];
ll adj1[1<<20|7],adj2[1<<20|7];
inline int lowbit(int x) {return x&-x;}
void solve() {
    int n,m,i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) {
        scanf("%d",&A[i]); A[i]--;
        if (i>=1) e[A[i-1]]|=1ll<<A[i],e[A[i]]|=1ll<<A[i-1];
    }
    REP(i,m) scanf("%d",&c[i]);
    e[A[1]]|=1ll<<A[1]; e[A[n]]|=1ll<<A[n];
    REP(i,20) v1[1<<i]=c[i],adj1[1<<i]=e[i];
    rep(i,20,40) v2[1<<(i-20)]=c[i],adj2[1<<(i-20)]=e[i];
    REP(i,(1<<20)) {
        int low=lowbit(i);
        v1[i]=v1[i^low]+v1[low];
        v2[i]=v2[i^low]+v2[low];
        adj1[i]=adj1[i^low]|adj1[low];
        adj2[i]=adj2[i^low]|adj2[low];
    }
    memset(p,0x3f,sizeof(p));
    REP(i,(1<<20)) {
        ll mask=((1<<20)-1)^i;
        if ((adj1[mask]&mask)) continue;
        p[i]=v1[i]; // must choose
    }
    int ans=INF;
    rREP(i,(1<<20)) REP(j,20) if ((i>>j)&1) min_(p[i^(1<<j)],p[i]);
    REP(i,(1<<20)) {
        ll mask=((1<<20)-1)^i;
        if ((adj2[mask]&(mask<<20))) continue; // adj2: mustchoose
        min_(ans,v2[i]+p[adj2[mask]&((1<<20)-1)]);
    }
    printf("%d\n",ans);
}
int main() {
    int T,_; T=1;
    // scanf("%d",&T);
    FOR(_,1,T) solve();
}
/*

*/