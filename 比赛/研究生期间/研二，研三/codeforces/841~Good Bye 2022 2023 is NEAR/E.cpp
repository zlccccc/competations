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

int dep[maxn];
ll val[maxn]; // toward
int sz[maxn];
vector<int> edge[maxn];
void dfs(int x,int fa) {
    // printf("dfs %d %d\n",x,fa);
    for (int v:edge[x]) {
        if (v==fa) continue;
        dep[v]=dep[x]+1;
        dfs(v,x);
        sz[x]+=sz[v];
    }
}
struct edge{
    int u,v;
}e[maxn];
void solve() {
    int n,k,i;
    scanf("%d%d",&n,&k);
    FOR(i,1,n) edge[i].clear();
    memset(val,0,sizeof(val));
    memset(sz,0,sizeof(sz));
    int x;
    FOR(i,1,k) scanf("%d",&x),sz[x]++,val[x]++;
    FOR(i,1,n-1) {
        scanf("%d%d",&e[i].u,&e[i].v);
        edge[e[i].u].push_back(e[i].v);
        edge[e[i].v].push_back(e[i].u);
        // printf("%d - %d\n",e[i].u,e[i].v);
    }
    dfs(1,0);
    // FOR(i,1,n) printf("%d ",sz[i]); puts("<- sz[i]");
    ll ans=0;
    FOR(i,1,n-1) {
        int x=e[i].u,y=e[i].v;
        if (dep[x]>dep[y]) swap(x,y);
        ll dy=sz[y],dx=k-sz[y];
        // x is the father of y
        // y->x, x->y
        ll now=0;
        now+=((1-val[x]+M)*(1-val[y]+M)+val[x]*val[y])%M*2*dx%M*dy%M; now%=M; // 走不过去, thisitem
        now+=val[x]*(1-val[y]+M)%M*((dx-1)*(dy+1)%M+dx*dy%M)%M; // 走的过去
        now+=val[y]*(1-val[x]+M)%M*((dy-1)*(dx+1)%M+dx*dy%M)%M; // 走的过去
        now%=M; now+=M; now%=M;
        now=now*powMM(2,M-2)%M; ans=(ans+now)%M;
        // val[x]=val[y]=(val[x]+val[y])*powMM(2,M-2)%M;
        ll nxty=val[y]*(1+val[x])+val[x]*(1+M-val[y]); nxty%=M;
        ll nxtx=val[x]*(1+val[y])+val[y]*(1+M-val[x]); nxtx%=M;
        val[y]=nxty*powMM(2,M-2)%M;
        val[x]=nxtx*powMM(2,M-2)%M; // towards
    }
    ans=ans*powMM((ll)k*(k-1)/2%M,M-2)%M; ans+=M; ans%=M;
    printf("%lld\n",ans);
    // printf("%lld\n",ans*4%M);
}
int main() {
    int T,_; T=1;
    // scanf("%d",&T);
    FOR(_,1,T) solve();
}
/*

*/