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
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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
 
 
int in[maxn],out[maxn],tot;//in->out: up-mindep
int MAX[maxn*4];//up-mindistance
void update(int x,int l,int r,int value,int L,int R) {
    if (l<=L&&R<=r) {MAX[x]=max(MAX[x],value); return;}
    int mid=(L+R)/2;
    if (l<=mid) update(x<<1,l,r,value,L,mid);
    if (mid<r) update(x<<1|1,l,r,value,mid+1,R);
}
int query(int x,int pos,int L,int R) {
    if (L==R) return MAX[x];
    int mid=(L+R)/2,ret=MAX[x];
    if (pos<=mid) max_(ret,query(x<<1,pos,L,mid));
    if (mid<pos) max_(ret,query(x<<1|1,pos,mid+1,R));
    return ret;
}
 
vector<pii> edge[maxn];
int fa[maxn],Fa[maxn][20],col[maxn],dep[maxn];
void dfs(int x,int fa,int color) {
    dep[x]=dep[fa]+1; col[x]=color;
    ::fa[x]=Fa[x][0]=fa;
    in[x]=++tot;
    int i; rep(i,1,20) Fa[x][i]=Fa[Fa[x][i-1]][i-1];
    for (auto e:edge[x]) if (e.first!=fa)
        dfs(e.first,x,color^e.second);
    out[x]=tot;
}
int lca(int x,int y) {
    int i;
    if (dep[x]<dep[y]) swap(x,y);
    rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=Fa[x][i];
    if (x==y) return x;
    rREP(i,20) if (Fa[x][i]!=Fa[y][i]) x=Fa[x][i],y=Fa[y][i];
    return Fa[x][0];
}
inline int getfa(int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int U[maxn*2],V[maxn*2],C[maxn*2];
int ans[maxn*2];
int main() {
    int n,q,i;
    scanf("%d%d",&n,&q);
    FOR(i,1,n) fa[i]=i;
    FOR(i,1,q) {
        scanf("%d%d%d",&U[i],&V[i],&C[i]);
        int x=getfa(U[i]),y=getfa(V[i]);
        if (x==y) continue; fa[x]=y;
        edge[U[i]].push_back(make_pair(V[i],C[i]));
        edge[V[i]].push_back(make_pair(U[i],C[i]));
        ans[i]=1;
    } FOR(i,1,n) if (!in[i]) dfs(i,0,0);
    FOR(i,1,q) if (!ans[i]) {
        int u=U[i],v=V[i];
        if (col[u]^col[v]^C[i]) {
            int f=lca(u,v);
            int du=query(1,in[u],1,n);
            int dv=query(1,in[v],1,n);
            // printf("query %d:%d; %d:%d; should %d:%d\n",u,du,v,dv,f,dep[f]);
            if (max(du,dv)<=dep[f]) {
                ans[i]=1;
                while (u!=v) {
                    if (dep[u]<dep[v]) swap(u,v);
                    // printf("%d->%d %d",in[u],out[u],dep[u]);
                    update(1,in[u],out[u],dep[u],1,n);
                    u=fa[u];
                }
            }
        }
    }
    FOR(i,1,q) puts(ans[i]?"YES":"NO");
}
/*
*/