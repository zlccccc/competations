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
#include <unordered_set>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

// #define DEBUG
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
const LL maxn=4e5+107;
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
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

int n,more;
vector<pii> ox_edge[maxn*2];
int sz[maxn*2];
// https://codeforces.com/contest/1389/problem/G
// 原题题意略过, 知道这个板子是用来建树的即可
struct edges {
    int u,v,len;
} e[maxn];
int id[maxn];
// vector<edges> E;
namespace tarjan { // 边双连通分量, 这里是在做仙人掌
    struct Edge {
        int to,next,id;
        Edge(int _to=0,int _next=-1,int _id=0):to(_to),next(_next),id(_id) {};
    } edge[maxn*2];
    int head[maxn],etot;
    inline void addedge(int u,int v,int id) {
        edge[++etot]=Edge(v,head[u],id); head[u]=etot;
    }
    int dfn[maxn],low[maxn],tot;
    bool vis[maxn],used[maxn];
    int S[maxn],top;
    int value[maxn];//to_lower
    void tarjan(int x,int fa) {
        low[x]=dfn[x]=++tot; vis[x]=1;
        value[x]=1;
        for (int i=head[x]; ~i; i=edge[i].next) {
            int v=edge[i].to;
            if (used[edge[i].id]) continue;
            if (v==fa) continue;
            S[++top]=edge[i].id;
            used[edge[i].id]=1;
            if (!dfn[v]) {
                tarjan(v,x);
                low[x]=min(low[x],low[v]);
                if (dfn[x]<=low[v]) { //割边和边双联通
                    vector<int> eid,pid,basp;
                    // int nowid=x;
                    while (1) {
                        int id=S[top--];
                        eid.push_back(id);
                        // nowid^=e[id].u^e[id].v; //only for 仙人掌
                        pid.push_back(e[id].u);//last
                        pid.push_back(e[id].v);//last
                        // debug("mapping: (%d,%d) (maybe not a circle)\n",e[id].u,e[id].v);
                        if (id==edge[i].id) break;
                    } sort(pid.begin(),pid.end());
                    pid.erase(unique(pid.begin(),pid.end()),pid.end());
                    if (low[v]==dfn[x]) { //双联通, 在这里dp
                        deputs(" circle :");//环, eid; pid
                        int nowid=n+(++more);
                        for (int v:pid) debug("%d ",v); deputs(" <- link");
                        for (int v:pid) id[v]=nowid;
                        for (int v:pid) {
                            for (int j=head[v]; ~j; j=edge[j].next) {
                                if (id[edge[j].to]==nowid) sz[nowid]++;
                                // if (edge[j].to==x||low[edge[j].to]==dfn[x]) {
                                //     sz[nowid]++; printf("ins %d -> %d\n",v,edge[j].to);
                                // }
                            }
                            ox_edge[nowid].push_back(make_pair(0,v));
                            ox_edge[v].push_back(make_pair(0,nowid));
                        }
                        sz[nowid]/=2;
                    } else {
                        deputs(" tree :");
                        for (int _=0; _<(int)eid.size(); _++) {
                            int noweid=eid[_];
                            edges nowe=e[noweid];
                            debug("e: (%d-%d) %d : %d\n",nowe.u,nowe.v,pid[_],nowe.len);
                            ox_edge[nowe.u].push_back(make_pair(nowe.len,nowe.v));
                            ox_edge[nowe.v].push_back(make_pair(nowe.len,nowe.u));
                        }
                    }
                    debug("low and dfn x=[%d]: %d %d\n",x,low[v],dfn[x]);
                }
            } else if (vis[v])
                low[x]=min(low[x],dfn[v]);
        }
    }
    void init(int n,int m) {
        int i;
        FOR(i,1,m) used[i]=0;
        FOR(i,1,n) head[i]=-1,dfn[i]=0; etot=tot=0;
        FOR(i,1,m) addedge(e[i].u,e[i].v,i),addedge(e[i].v,e[i].u,i);
        FOR(i,1,n) if (!dfn[i]) tarjan(i,0);
    }
}
inline int isRect(int x) {return x>n;}

int fa[maxn*2][21],dep[maxn*2];
void dfs(int x,int father,int depth) {
    dep[x]=depth;
    sz[x]+=sz[father];
    fa[x][0]=father; int i;
    rep(i,1,21) fa[x][i]=fa[fa[x][i-1]][i-1];
    for (auto p:ox_edge[x]) {
        int v=p.second;
        if (v==father) continue;
        dfs(v,x,depth+1);
        // printf("edge %d -> %d\n",x,v);
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
int main() {
    int m,i;
    scanf("%d%d",&n,&m);
    FOR(i,1,m) scanf("%d%d",&e[i].u,&e[i].v),e[i].len=1;
    tarjan::init(n,m);
    dfs(n+1,0,0);
    int q; scanf("%d",&q);
    FOR(i,1,q) {
        int x,y;
        scanf("%d%d",&x,&y);
        int f=lca(x,y);
        printf("%d\n",sz[x]+sz[y]-sz[f]-sz[fa[f][0]]);
    }
}
/*
*/