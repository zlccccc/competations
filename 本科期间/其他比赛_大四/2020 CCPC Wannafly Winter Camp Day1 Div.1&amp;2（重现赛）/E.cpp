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
const LL maxn=3e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

// contribution: len-1, len-3 ... = len-2x(to leaf)+1
// contribution->edge(son)
vector<int> edge[maxn];
int fa[maxn][20],dep[maxn];
void dfs_lca(int x,int father) {
    fa[x][0]=father; dep[x]=dep[father]+1; int i;
    rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
    for (int v:edge[x]) if (v!=father) dfs_lca(v,x);
}
int lca(int x,int y) {
    int i;
    if (dep[x]<dep[y]) swap(x,y);
    rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
    if (x==y) return x;
    rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
ll ans[maxn];
ll A[maxn],B[maxn];
void dfs(int x,int father) {//subtree
    // printf("init %d : %lld %lld\n",x,A[x],B[x]);
    for (int v:edge[x]) if (v!=father) {
        dfs(v,x);
        A[x]+=A[v]; B[x]+=B[v];
        // printf("%d -> %d\n",x,v);
    }
    // printf("%d : %lld %lld\n",x,A[x],B[x]);
}
void dfs2(int x,int father) {
    for (int v:edge[x]) if (v!=father) {
        ans[v]=ans[x]-A[v]*dep[x]-B[v];
        dfs2(v,x);
    }
}
int main() {
    int n,m,i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n-1) {
        int u,v; scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    } dfs_lca(1,0);
    FOR(i,1,m) {
        int u,v; scanf("%d%d",&u,&v);
        int f=lca(u,v);
        int len=dep[u]+dep[v]-2*dep[f];
        A[u]+=2; B[u]+=len+1-2*dep[u]; A[f]-=2; B[f]-=len+1-2*dep[u];
        A[v]+=2; B[v]+=len+1-2*dep[v]; A[f]-=2; B[f]-=len+1-2*dep[v];
        ans[1]+=(ll)(dep[u]-dep[f])*(dep[v]-dep[f]);
        // printf("lca=%d\n",lca(u,v));
    } dfs(1,0);
    dfs2(1,0);
    FOR(i,1,n) printf("%lld\n",ans[i]);
}
/*
6 1
1 2
2 3
3 4
2 5
2 6
4 6
*/