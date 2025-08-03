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
const LL maxn=1e5+207;
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

int dep[maxn];
vector<int> edge[maxn];
int fa[maxn][20],depth;
void dfs(int x,int father,int depth) {
    int i; fa[x][0]=father; dep[x]=depth;
    rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
    for (int v:edge[x]) {
        if (v==father) continue;
        dfs(v,x,depth+1);
    }
}
int lca(int x,int y) {
    int i;
    if (dep[x]<dep[y]) swap(x,y);
    rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
    if (x==y) return x;
    rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int dis(int x,int y) {
    return dep[x]+dep[y]-2*dep[lca(x,y)];
}
// int A[maxn];
// int getBottom(int x,int color) {
//     int i;
//     rREP(i,20) if (fa[x][i]&&A[fa[x][i]]==color) x=fa[x][i];
//     return fa[x][0];
// }
// int getTop(int x,int color,int depth) {
//     int i;
//     rREP(i,20) if (fa[x][i]&&dep[fa[x][i]]>=depth&&A[fa[x][i]]!=color) x=fa[x][i];
//     return x;
// }
vector<pair<pii,pii> > P;
vector<int> idx[maxn];
pii e[maxn];
int D[maxn*21];
int pid[maxn][20];//the id of pow
vector<int> E[maxn*21];
void addedge(int x,int y) {
    // printf("   addedge:%d %d\n",x,y);
    E[x].push_back(y); D[y]++;
}
void update(int x,int length,int id) {
    // printf(" update: %d %d\n",x,length);
    int i;
    rREP(i,20) if (length>=1<<i) {
        addedge(id,pid[x][i]); x=fa[x][i]; length-=1<<i;
    }
}
void add_x2y(int x,int y,int id) {
    // printf("add_x2y %d %d %d\n",x,y,id);
    if (x==y) return;
    int f=lca(x,y); if (dep[x]<dep[y]) swap(x,y);
    x=fa[x][0];
    update(x,dep[x]-dep[f],id);
    if (f!=y)  {
        y=fa[y][0];
        update(y,dep[y]-dep[f]+1,id);
    }
}
int main(){
    int n,m,i,k;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) {
        int x; scanf("%d",&x);
        idx[x].push_back(i);
    }
    FOR(i,1,n-1) {
        int u,v; scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    } dfs(1,0,0);
    int tot=m;
    FOR(i,1,n) REP(k,20) pid[i][k]=++tot;
    FOR(i,1,n) {
        rep(k,1,20) {
            addedge(pid[i][k],pid[i][k-1]);
            addedge(pid[i][k],pid[fa[i][k-1]][k-1]);
        }
    }
    FOR(i,1,m) {
        if (!idx[i].size()) {
            printf("%d 1 1\n",i);
            continue;
        } int px=idx[i][0],py,_;
        vector<pair<int,int> > pl;
        for (int v:idx[i]) if (dep[v]>dep[px]) px=v;
        for (int v:idx[i]) pl.push_back(make_pair(dis(px,v),v));
        sort(pl.begin(), pl.end());
        py=pl.rbegin()->second;
        e[i]=make_pair(px,py);
        for (int v:idx[i]) addedge(pid[v][0],i);
        REP(_,(int)pl.size()-1) add_x2y(pl[_].second,pl[_+1].second,i);
    } queue<int> Q;
    FOR(i,1,tot) if (!D[i]) Q.push(i);
    while (Q.size()) {
        int x=Q.front(); Q.pop();
        // printf("Q:%d\n",x);
        if (x<=m&&idx[x].size()) printf("%d %d %d\n",x,e[x].first,e[x].second);
        for (int v:E[x]) {
            D[v]--; if (!D[v]) Q.push(v);
        }
    }
}
/*
6 3 
1 3 2 1 1 2 
1 4 
2 4 
3 4 
4 5 
5 6

5 3
3 2 1 2 1
1 2
1 3
1 4
4 5

6 3 
1 2 1 1 1 2 
1 4 
2 4 
3 5 
4 5 
5 6

6 3 
2 1 1 1 1 2 
1 4 
2 4 
3 5 
4 5 
5 6
*/ 