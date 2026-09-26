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
const LL M=1e9+7;
const LL maxn=1e6+107;
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

inline int lowbit(int x) {return x&-x;}
inline void update(int A[],int pos,int val){
    for (;pos<=1e6;pos+=lowbit(pos)) A[pos]+=val;
}
inline void update(int A[],int l,int r,int val) {
    update(A,l,val); update(A,r+1,-val);
}
inline int query(int A[],int pos){
    int ret=0;
    for (;pos;pos-=lowbit(pos)) ret+=A[pos];
    return ret;
}
int A[maxn]; //B[x]+=A[x-1]; 分开维护
int C[maxn];
vector<int> edge[maxn];
int son[maxn],sz[maxn],top[maxn],tot,dep[maxn],id[maxn];
int fa[maxn],rid[maxn];
void dfs1(int x,int father,int depth) {
    int mx=-1; fa[x]=father;
    sz[x]=1; dep[x]=depth; son[x]=0;
    for (int v:edge[x]) if (v!=father) {
        dfs1(v,x,depth+1);
        sz[x]+=sz[v];
        if (sz[v]>mx) mx=sz[v],son[x]=v;
    }
}
void dfs2(int x,int Top) {
    top[x]=Top; id[x]=++tot; rid[tot]=x; C[tot]=A[x];
    if (son[x]) dfs2(son[x],Top);
    // if (son[x]) dfs2(son[x],son[x]);
    for (int v:edge[x]) {
        if (v==fa[x]||v==son[x]) continue;
        dfs2(v,v);
    }
}
ll val[maxn];
int Count[2][maxn]; //0:from left; 1: from right
inline int Update(int x,int y){
    int o=1,ret=0; // o: up(x)
    vector<pii> solve[2];
    while (top[x]!=top[y]){//up(1)的更新应该是倒着的
        if (dep[top[x]]<dep[top[y]]) swap(x,y),o^=1;
        solve[o].push_back(make_pair(id[top[x]],id[x]));//1:x_up; 0：x_down
        x=fa[top[x]];
    }
    if (dep[x]>dep[y]) swap(x,y),o^=1; o^=1;
    solve[o].push_back(make_pair(id[x],id[y]));
    reverse(solve[0].begin(),solve[0].end());
    int prev=0;
    // for (auto now:solve[0]) printf("%d-%d, ",now.first,now.second); puts("<- zero");
    // for (auto now:solve[1]) printf("%d-%d, ",now.first,now.second); puts("<- one");
    for (auto now:solve[1]) {
        int x=now.first,y=now.second;
        val[y]+=prev; prev=C[x];
        if (x==y) continue;
        update(Count[1],x,y-1,1);
    }
    for (auto now:solve[0]) {
        int x=now.first,y=now.second;
        val[x]+=prev; prev=C[y];
        if (x==y) continue;
        update(Count[0],x+1,y,1);
    }
    return ret;
}
int main() {
    int i,n,m;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n-1) {
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    } dfs1(1,0,0);
    dfs2(1,1);
    // FOR(i,1,n) printf("%d ",id[i]); puts("<- dfn");
    FOR(i,1,m) {
        int op; scanf("%d",&op);
        if (op==1) {
            int x,y;
            scanf("%d%d",&x,&y);
            Update(x,y);
        } else {
            int x; scanf("%d",&x);
            ll ans=val[id[x]];
            ans+=(ll)query(Count[0],id[x])*C[id[x]-1];
            ans+=(ll)query(Count[1],id[x])*C[id[x]+1];
            // printf("id=%d; val[x]=%lld,count0=%d,count1=%d\n",id[x],val[x],query(Count[0],id[x]),query(Count[1],id[x]));
            printf("%lld\n",ans);
        }
    }
}
/*
6 10000
100000000 10000000 1000000000 1000 10000 100000
1 2
1 3
2 4
2 5
3 6
1 4 6
1 6 5
1 4 6
1 6 5
1 4 6
1 6 5
2 1
2 2
2 3
2 4
2 5
2 6
*/