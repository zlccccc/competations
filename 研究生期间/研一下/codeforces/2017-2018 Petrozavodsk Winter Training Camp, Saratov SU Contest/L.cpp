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
const LL maxn=1.2e6+107;
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

int ans[maxn];
vector<pair<pii,int> > initial[maxn];//v,dis,cost;
ll dis[maxn];
// copy from 板子(重写)
//lowlink是说,遇到的min
//无向图:
//u割点:low[v]>=dfn[u];(表示能到的点都在之后)
//u-v割边(桥):low[v]>dfn[u];(要在u-v处得到)
//块:low[u]==dfn[u];(最终从stack取出x)
//dfs时注意fa和重边处理
//有向图:
//DAG上的割边:u-v:cnt[u]*cnt[v]==cnt[t](mod?)
//DAG上的割边是固定的,也就是说求出来以后最短路是一样长的
//有环割边:将边变成点,然后跑支配树即可
//支配树:(注意,由于可能有到达不了的节点,初始化时注意答案更新)
//半必经点(semi=mindep{通过非树枝边fa})定理:(semi[x]=id[temp]),
//temp=min(temp,dfn[pre]),dfn[x]>dfn[pre](树枝边|前向边)
//temp=min{temp,dfn[semi[ancestor_pre(fa)]]}
//dfn[x]<dfn[pre](横叉边|后向边)
//必经点(idom)定理:y=id[min{dfn[z]}],z:semi_path上的点
//idom[x]=semi[x],semi[x]==semi[y]
//idom[x]=idom[y],semi[x]!=semi[y]
struct Edge {
    int to,next;
    Edge(int _to=0,int _next=-1):to(_to),next(_next) {};
} edge[maxn*4];
int head[maxn],pre[maxn],dom[maxn],etot; //edges
inline void addedge(int head[],int u,int v) {
    edge[++etot]=Edge(v,head[u]);
    head[u]=etot;
}
int dfn[maxn],tot,par[maxn]; //dfs-tree
int Fa[maxn],best[maxn]; //disjoint-set
int semi[maxn],id[maxn],idom[maxn]; //dom-tree
inline int getfa(int x) {
    if(Fa[x]==x) return x;
    int F=getfa(Fa[x]);
    if(dfn[semi[best[x]]]>dfn[semi[best[Fa[x]]]])
        best[x]=best[Fa[x]];
    return Fa[x]=F;
}
void dfs(int x) {
    dfn[x]=++tot;
    id[tot]=x;
    for(int i=head[x]; ~i; i=edge[i].next) {
        int v=edge[i].to;
        if(!dfn[v]) par[v]=x,dfs(v);
    }
}
void tarjan(int n) {
    int i;
    FOR(i,1,n) dom[i]=-1;
    FOR(i,1,n) best[i]=semi[i]=Fa[i]=i;
    rFOR(i,2,tot) {
        int x=id[i];
        for(int j=pre[x]; ~j; j=edge[j].next) {
            int v=edge[j].to;
            if(!dfn[v]) continue; //could not reach
            getfa(v); //pre_dfn:not changed
            if(dfn[semi[best[v]]]<dfn[semi[x]])
                semi[x]=semi[best[v]];
        }
        addedge(dom,semi[x],x);
        Fa[x]=par[x];
        x=id[i-1];
        for(int j=dom[x]; ~j; j=edge[j].next) { //path
            int v=edge[j].to;
            getfa(v); //id[min{dfn[z]}];
            if(semi[best[v]]==x) idom[v]=x;
            else idom[v]=best[v];
        }
    }
    FOR(i,2,tot) {
        int x=id[i];
        if(idom[x]!=semi[x]) idom[x]=idom[idom[x]];
    }
}
int CNT[maxn];
void solve() {
    int i;
    rFOR(i,2,tot) {
        int x=id[i];
        CNT[idom[x]]+=CNT[x];
    }
}

priority_queue<pair<ll,int> > Q;
int main() {
    int n,m,i;
    scanf("%d%d",&n,&m);
    FOR(i,1,m) {
        int u,v,c;
        scanf("%d%d%d",&u,&v,&c);
        initial[u].push_back(make_pair(make_pair(v,c),i));
        initial[v].push_back(make_pair(make_pair(u,c),i));
    } memset(dis,0x3f,sizeof(dis));
    Q.push(make_pair(0ll,1)); dis[1]=0;
    while (Q.size()) {
        auto now=Q.top(); Q.pop();
        if (dis[now.second]!=-now.first) continue;
        for (auto e:initial[now.second]) {
            ll dist=dis[now.second]+e.first.second; int v=e.first.first;
            if (dist<dis[v]) {
                dis[v]=dist;
                Q.push(make_pair(-dis[v],v));
            }
        }
    }
    // FOR(i,1,n) printf("%lld ",dis[i]); puts("<- dis");
    FOR(i,1,n+m) head[i]=pre[i]=-1;
    FOR(i,1,n+m) dfn[i]=id[i]=idom[i]=0;etot=tot=0;
    FOR(i,1,n) for (auto e:initial[i]) {
        if (dis[i]+e.first.second==dis[e.first.first]) {
            int u=i,v=e.second+n;
            addedge(head,u,v); addedge(pre,v,u);
            u=e.second+n; v=e.first.first;
            addedge(head,u,v); addedge(pre,v,u);
        }
    }
    dfs(1);
    tarjan(n+m);
    FOR(i,1,n) CNT[i]=1;
    solve();
    FOR(i,1,m) printf("%d\n",CNT[i+n]);
}
/*
*/