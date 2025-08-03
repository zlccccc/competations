// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
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
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)

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
// const LL M=1e9+7;
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
typedef array<int,2> ar2;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

vector<pii> edge[maxn];
int eid[maxn];
int son[maxn],sz[maxn],fa[maxn];//changes
int top[maxn],id[maxn],dep[maxn],tot;
void dfs1(int u,int father,int depth){
    int mx=-1; fa[u]=father;
    sz[u]=1; dep[u]=depth; son[u]=0;
    for (pii e:edge[u]) {
        int v=e.first;
        if (father==v) continue; 
        dfs1(v,u,depth+1);
        sz[u]+=sz[v];
        if (sz[v]>mx) mx=sz[v],son[u]=v;
    }
}
void dfs2(int u,int x){
    top[u]=x; id[u]=++tot;
    if (son[u]) dfs2(son[u],x);
    for (pii e:edge[u]){
        int v=e.first,idx=e.second;
        if (fa[u]==v) {eid[idx]=id[u]; continue;}
        if (v==son[u]) continue;
        dfs2(v,v); 
    }
}
ll SUM[maxn*4];
void update(int x,int pos,int val,int L,int R) {
    if (L==R) {SUM[x]=val; return;}
    int MID=(L+R)/2;
    if (pos<=MID) update(x<<1,pos,val,L,MID);
    if (MID<pos) update(x<<1|1,pos,val,MID+1,R);
    SUM[x]=SUM[x<<1]+SUM[x<<1|1]; 
}
ll query(int x,int l,int r,int L,int R) {
    // printf("query %d %d->%d: %lld\n",x,l,r,SUM[x]);
    if (l<=L&&R<=r) return SUM[x];
    int MID=(L+R)/2; ll ret=0;
    if (l<=MID) ret+=query(x<<1,l,r,L,MID);
    if (MID<r) ret+=query(x<<1|1,l,r,MID+1,R);
    return ret;
}
inline ll Query(int x,int y){
    ll ret=0; // o: up(x)
    while (top[x]!=top[y]){//up(1)的更新应该是倒着的
        if (dep[top[x]]<dep[top[y]]) swap(x,y);
        ret+=query(1,id[top[x]],id[x],1,tot);//x_up
        x=fa[top[x]];
    }
    if (dep[x]>dep[y]) swap(x,y);
    if (son[x]) {
        ret+=query(1,id[son[x]],id[y],1,tot);//y_up
    } return ret;
}
int w[maxn];
int main() {
    int n;
    scanf("%d",&n);
    FOR_(i,1,n-1) {
        int x,y;
        scanf("%d%d%d",&x,&y,&w[i]);
        edge[x].push_back({y,i});
        edge[y].push_back({x,i});
    }
    dfs1(1,0,0);
    dfs2(1,1);
    FOR_(i,1,n-1) update(1,eid[i],w[i],1,n);
    int q;
    scanf("%d",&q);
    FOR_(_,1,q) {
        int op,x,y;
        scanf("%d%d%d",&op,&x,&y);
        if (op==1) update(1,eid[x],y,1,n);
        else printf("%lld\n",Query(x,y));
    }
}