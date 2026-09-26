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

namespace LCA {//内部和外部dfn不同...
    vector<pii> edge[maxn];
    int fa[maxn];
    int uplen[maxn];
    int id[maxn],dfn[maxn],idtot;
    void addedge(int u,int v,int len=1) {
        edge[u].push_back({v,len});
    }
    int dep[maxn]; int len[maxn];
    int st_dfn[maxn],tot;
    int ST[maxn*2][22];//only L
    int t_t[maxn*2];
    void dfs(int x,int f,int depth,int length) {
        dep[x]=depth; len[x]=length;
        st_dfn[x]=++tot; ST[tot][0]=x;
        id[++idtot]=x; dfn[x]=idtot;
        for (pii e:edge[x]) {
            int v=e.first,l=e.second;
            if (v==f) continue;
            fa[v]=x; uplen[v]=l;
            dfs(v,x,depth+1,length+l);
            ST[++tot][0]=x;
        }
    }
    inline void initST(int n) {
        int i,j;
        FOR(i,1,n*2) t_t[i]=t_t[i>>1]+1;
        FOR(i,1,n*2) {
            rep(j,1,t_t[i]) {
                int u=ST[i][j-1],v=ST[i-(1<<(j-1))][j-1];
                ST[i][j]=dep[u]<dep[v]?u:v;
            }
        }
    }
    inline int lca(int x,int y) {
        x=st_dfn[x]; y=st_dfn[y];
        if (x>y) swap(x,y);
        int t=t_t[y-x+1]-1;
        x=ST[x+(1<<t)-1][t]; y=ST[y][t];
        return dep[x]<dep[y]?x:y;
    }
    inline int dis(int x,int y) {
        if (!x||!y) return 0;
        return len[x]+len[y]-2*len[lca(x,y)];
    }
    void init(int n) {
        int i;
        FOR(i,1,n) edge[i].clear();
        idtot=tot=0;
    }
}
vector<int> U[maxn];
pii P[maxn];
int dis[maxn],du[maxn];
int x,y;
int main() {
    int n,i;
    scanf("%d",&n);
    LCA::init(n);
    FOR(i,2,n) {
        int x; scanf("%d",&x);
        LCA::addedge(i,x,1); LCA::addedge(x,i,1);
        du[i]++; du[x]++;
    }
    LCA::dfs(1,0,0,0);
    LCA::initST(n);
    queue<int> Q;
    FOR(i,1,n) dis[i]=-1;
    FOR(i,1,n) if (du[i]==1) Q.push(i),dis[i]=0;
    while (Q.size()) {
        int x=Q.front(); Q.pop();
        U[dis[x]].push_back(x);
        for (pii e:LCA::edge[x]) {
            int v=e.first;
            if (dis[v]==-1) dis[v]=dis[x]+1,Q.push(v);
        }
    }
    rFOR(i,0,n) {
        P[i]=P[i+1];
        for (int v:U[i]) {
            int x=P[i].first,y=P[i].second;
            int vy=LCA::dis(v,y),vx=LCA::dis(v,x),xy=LCA::dis(x,y);
            if (vy>=max(xy,vx)) P[i]=make_pair(v,y);
            else if (vx>=max(xy,vy)) P[i]=make_pair(x,v);
        }
        // printf("i=%d\n",i);
        // for (int v:U[i]) printf("%d ",v); puts("");
        // printf("u,v=%d-%d\n",P[i].first,P[i].second);
    }
    int q,_; scanf("%d",&q);
    FOR(_,1,q) {
        int val,ans=0;
        scanf("%d",&val);
        FOR(i,0,n) {
            while (1) {
                auto x=P[i],y=P[max(0,ans-val-i)];
                int maxdis=0;
                max_(maxdis,LCA::dis(x.first,y.first));
                max_(maxdis,LCA::dis(x.second,y.first));
                max_(maxdis,LCA::dis(x.first,y.second));
                max_(maxdis,LCA::dis(x.second,y.second));
                if (maxdis>=ans) ans++;
                else break;
            }
            // for (int x:U[i]) {
            //     while (max(LCA::dis(x,P[max(0,ans-val-i)].first),LCA::dis(x,P[max(0,ans-val-i)].second))>=ans) ans++;
            // }
        }
        ans--;
        printf("%d\n",ans);
    }
}
/* 
1 4
*/