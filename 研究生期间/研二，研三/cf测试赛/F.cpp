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
const LL M=1e9+7;
// const LL M=998244353;
// ll M=1;
const LL maxn=5e5+107;
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

vector<int> edge[maxn];
int fa[maxn][20],dep[maxn];
ll upp[maxn][20],A[maxn]; // upp:upp_and
int faupp[maxn][20];
void dfs(int x,int father,int depth) {
    int i;
    fa[x][0]=father; dep[x]=depth;
    rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
    upp[x][0]=A[x];
    rep(i,1,20) upp[x][i]=upp[x][i-1]&upp[fa[x][i-1]][i-1];
    ll all=-1; int y=x;
    rREP(i,20) if (upp[y][i]&all&A[fa[y][i]]) all&=upp[y][i],y=fa[y][i];
    faupp[x][0]=y;
    rep(i,1,20) faupp[x][i]=faupp[faupp[x][i-1]][i-1];
    // printf("faupp[%d]=%d\n",x,y);
    // REP(i,5) printf("%d ",faupp[x][i]); puts("<- faupp");
    for (int v:edge[x]) {
        if (v==father) continue;
        dfs(v,x,depth+1);
    }
}
int lca(int x,int y) {
    int i;
    if (dep[x]<dep[y]) swap(x,y);
    rREP(i,20) if ((dep[x]-(1<<i))>=dep[y]) x=fa[x][i];
    if (x==y) return x;
    rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
// nlogn
int main() {
    int n,i,q;
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%lld",&A[i]);
    FOR(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1,0,1);
    while (q--) {
        int u,v;
        scanf("%d%d",&u,&v);
        int f=lca(u,v);
        int ans=dep[u]+dep[v]-dep[f]*2; ll alland=A[f];
        // u->f: &!=0
        // printf("ans=%d; u=%d v=%d; f=%d\n",ans,u,v,f);
        rREP(i,20) if (dep[faupp[u][i]]>dep[f]) u=faupp[u][i],ans+=1<<i;
        // printf("1 ans=%d; u=%d v=%d; f=%d\n",ans,u,v,f);
        rREP(i,20) if (dep[u]-(1<<i)>=dep[f]) alland&=upp[u][i],u=fa[u][i];
        // printf("2 ans=%d; u=%d v=%d; f=%d\n",ans,u,v,f);
        // printf("alland=%d\n",alland);
        swap(u,v);
        rREP(i,20) if (dep[faupp[u][i]]>dep[f]) u=faupp[u][i],ans+=1<<i;
        // printf("3 ans=%d; u=%d v=%d; f=%d\n",ans,u,v,f);
        rREP(i,20) if (dep[u]-(1<<i)>=dep[f]) alland&=upp[u][i],u=fa[u][i];
        // printf("4 ans=%d; u=%d v=%d; f=%d\n",ans,u,v,f);
        // printf("alland=%d\n",alland);
        // // v->f: &!=0
        // rREP(i,20) if (dep[faupp[v][i]]>=dep[f]) v=upp[v][i],ans+=1<<i;
        // rREP(i,20) if (dep[v]-(1<<i)>=dep[f]) alland&=upp[v][i],v=fa[v][i];
        if (!alland) ans++;
        if (ans>n+n) puts("-1");
        else printf("%d\n",ans);
    }
}
/*
10 500000
1 15 10 6 0 14 13 3 5 3
2 1
2 3
4 2
3 5
4 6
7 6
8 6
7 9
8 10

10 7
*/