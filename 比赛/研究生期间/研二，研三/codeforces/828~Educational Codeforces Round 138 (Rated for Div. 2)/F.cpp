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
const LL maxn=2e5+107;
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

struct BIT{
    int T[maxn];
    BIT() {memset(T,0,sizeof(T));}
    inline int lowbit(int x) {return x&-x;}
    void update(int x,int v) {
        for (;x<=200030;x+=lowbit(x)) T[x]+=v;
    }
    int query(int x) {
        if (x<=0) return 0;
        int ret=0;
        for (;x;x-=lowbit(x)) ret+=T[x];
        return ret;
    }
    int query(int l,int r) {
        return query(r)-query(l-1);
    }
}T[21];

// 和u->v距离<=d
// 等价于和u+1->v距离=d + 和u距离<=d
// 和u距离<=d 等价于和fa[u]距离<=d-1 + 和u距离=d或d-1
// d[pos,u->v] <= dis
// u+1->v: dis==d; + u:dis<=d
vector<int> edge[maxn];
int son[maxn],sz[maxn],fa[maxn],tot=0;
int top[maxn],id[maxn],dep[maxn],out[maxn];
void dfs1(int u,int father,int depth) {
    int mx=-1; fa[u]=father;
    sz[u]=1; dep[u]=depth; son[u]=0;
    for (int v:edge[u]) {
        if (v==fa[u]) continue;
        dfs1(v,u,depth+1);
        sz[u]+=sz[v];
        if (sz[v]>mx) mx=sz[v],son[u]=v;
    }
}
void dfs2(int u,int x) {
    top[u]=x; id[u]=++tot;
    if (son[u]) dfs2(son[u],x);
    for (int v:edge[u]) {
        if (v==fa[u]||v==son[u]) continue;
        dfs2(v,v);
    } out[u]=tot;
}
ll D[maxn][21];
void update(int x,int y,int d,int val) {
    T[d].update(id[x],val);
    T[d].update(id[y],val);
    while (top[x]!=top[y]) {
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        x=fa[top[x]];
    }
    if (dep[x]>dep[y]) swap(x,y); // x is lca
    T[d].update(id[x],-2*val);
    // more
    while (d) {
        D[x][d]+=val; D[x][d-1]+=val;
        d--; x=fa[x];
    } D[x][d]+=val;
}
const int DEP=22;
int main() {
    int i,n;
    scanf("%d",&n);
    FOR(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    FOR(i,1,DEP) edge[n+i].push_back(n+i-1); n+=DEP;
    dfs1(n,0,0);
    dfs2(n,n);
    int q;
    scanf("%d",&q);
    FOR(i,1,q) {
        int op; scanf("%d",&op);
        if (op==1) {
            int x,ans=0,i; scanf("%d",&x);
            FOR(i,0,20) {
                ans+=T[i].query(id[x],out[x])+D[x][i];
                x=fa[x]; // distance=i
            }
            printf("%d\n",ans);
        } else {
            int u,v,k,d;
            scanf("%d%d%d%d",&u,&v,&k,&d);
            update(u,v,d,k);
        }
    }
}
/*
*/