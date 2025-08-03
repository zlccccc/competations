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

int fa[maxn],Fa[maxn][20];
inline int getfa(int x){
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
//simple cycle... 不然就直接是并查集了
int val[maxn],dep[maxn];
vector<pii> edge[maxn];
int in[maxn],out[maxn],tot;
void dfs(int x,int fa,int value,int depth) {
    // printf("dfs %d %d %d %d\n",x,fa,value,depth);
    ::fa[x]=fa; val[x]=value; dep[x]=depth;
    in[x]=++tot; Fa[x][0]=fa; int i;
    rep(i,1,20) Fa[x][i]=Fa[Fa[x][i-1]][i-1];
    for (auto e:edge[x]) {
        if (e.first==fa) continue;
        dfs(e.first,x,value^e.second,depth+1);
    } out[x]=tot;
}
int MAX[maxn*4];
void update(int x,int l,int r,int val,int L,int R) {
    if (l<=L&&R<=r) {max_(MAX[x],val); return;}
    int mid=(L+R)/2;
    if (l<=mid) update(x<<1,l,r,val,L,mid);
    if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
}
int query(int x,int pos,int L,int R) {
    int ret=MAX[x];
    if (L==R) return ret;
    int mid=(L+R)/2;
    if (pos<=mid) max_(ret,query(x<<1,pos,L,mid));
    if (mid<pos) max_(ret,query(x<<1|1,pos,mid+1,R));
    return ret;
}
int lca(int x,int y) {
    int i;
    if (dep[x]<dep[y]) swap(x,y);
    rREP(i,20) if (dep[x]-dep[y]>=(1<<i)) x=Fa[x][i];
    if (x==y) return x;
    rREP(i,20) if (Fa[x][i]!=Fa[y][i]) x=Fa[x][i],y=Fa[y][i];
    return Fa[x][0];
}
int U[maxn],V[maxn],O[maxn],ans[maxn];
int main() {
    int n,i,q;
    scanf("%d%d",&n,&q);
    FOR(i,1,n) fa[i]=i;
    FOR(i,1,q) {
        scanf("%d%d%d",&U[i],&V[i],&O[i]);
        int x=getfa(U[i]),y=getfa(V[i]);
        if (x==y) continue; fa[x]=y;
        // printf("edge %d %d %d\n",U[i],V[i],O[i]);
        edge[U[i]].push_back({V[i],O[i]});
        edge[V[i]].push_back({U[i],O[i]});
        ans[i]=1;
    }
    FOR(i,1,n) if (!in[i]) dfs(i,0,0,1);
    FOR(i,1,q) {
        int u=U[i],v=V[i];
        if (val[u]^val[v]^O[i]) {
            int f=lca(u,v);
            int du=query(1,in[u],1,n);
            int dv=query(1,in[v],1,n);
            // printf("i=%d: u=%d; v=%d; dx=%d; dy=%d f=%d; dep[f]=%d\n",i,u,v,du,dv,f,dep[f]);
            if (max(du,dv)<=dep[f]) {
                ans[i]=1;
                while (u!=v) {
                    if (dep[u]<dep[v]) swap(u,v);
                    // printf("update %d dep=%d\n",u,dep[u]);
                    update(1,in[u],out[u],dep[u],1,n);
                    u=fa[u];
                }
            }
        }
    }
    FOR(i,1,q) if (ans[i]) puts("YES"); else puts("NO");
}
/*
*/