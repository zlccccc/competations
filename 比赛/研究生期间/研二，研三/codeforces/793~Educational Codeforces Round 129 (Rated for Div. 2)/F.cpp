#include <bits/stdc++.h>
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
typedef array<int,3> ar3;
typedef array<int,4> ar4;
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

int sz[maxn];
struct Edges {
    int to; int len; int next;
    Edges(int _to=0,int _len=0,int _next=0):to(_to),len(_len),next(_next) {}
} edge[maxn*2]; int etot;
int head[maxn];
int fa[maxn];
int uplen[maxn];
int id[maxn],dfn[maxn],idtot;
inline void addedge(int u,int v,int len) {
    edge[++etot]=Edges(v,len,head[u]); head[u]=etot;
    edge[++etot]=Edges(u,len,head[v]); head[v]=etot;
}
namespace LCA {//内部和外部dfn不同...
    int dep[maxn]; int len[maxn];
    int st_dfn[maxn],tot;
    int ST[maxn*2][22];//only L
    void dfs(int x,int f,int d,int l) {
        int i; dep[x]=d; len[x]=l;
        st_dfn[x]=++tot; ST[tot][0]=x;
        ::id[++idtot]=x; ::dfn[x]=idtot;
        for (i=head[x]; ~i; i=edge[i].next) if (edge[i].to!=f) {
                int v=edge[i].to;
                ::fa[v]=x; ::uplen[v]=edge[i].len;
                dfs(v,x,d+1,l+edge[i].len);
                ST[++tot][0]=x;
                sz[x]+=sz[v];
            }
    }
    int t_t[maxn*2];
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
        return len[x]+len[y]-2*len[lca(x,y)];
    }
    void init(int n) {
        memset(head+1,0xff,n*sizeof(int));
        etot=idtot=tot=0;
    }
}

namespace vtree {
    int S[maxn],top;
    int pid[maxn],mark[maxn];
    int vid[maxn],vfa[maxn];
    int vlen[maxn];
    int cmp(int x,int y) {
        return dfn[x]<dfn[y];
    }
    void addedge(int u,int v) {
        vfa[v]=u; vlen[v]=LCA::dis(u,v);
    }
    int m;
    void vbuild(int n) {
        int i; m=0;
        sort(pid+1,pid+1+n,cmp);
        S[top=1]=pid[1];
        mark[pid[1]]=1;
        FOR(i,2,n) {
            int f=LCA::lca(pid[i-1],pid[i]);
            while (top&&LCA::dep[S[top]]>LCA::dep[f]) {
                int v; vid[++m]=v=S[top--];
                if (top&&LCA::dep[S[top]]>LCA::dep[f]) addedge(S[top],v);
                else addedge(f,v);
            } if (!top||S[top]!=f) S[++top]=f;
            S[++top]=pid[i]; mark[pid[i]]=1;
        } while (top-1) addedge(S[top-1],S[top]),vid[++m]=S[top--];
        vid[++m]=S[1];
        reverse(vid+1,vid+m+1);
        vfa[vid[1]]=0;
    }
    void vclear() {
        int i;
        FOR(i,1,m) mark[vfa[vid[i]]]=0;
        FOR(i,1,m) mark[vid[i]]=0;
    }
}

ll ans=0;
int vsz[maxn],viz[maxn]; // vtree::size
void solve(int pos,int n) {
    int i;
    vsz[0]=n;
    FOR(i,1,vtree::m) {
        int x=vtree::vid[i];
        vsz[x]=sz[x];
        // if (pos==29) printf("vsz[%d](%d) %d -= %d\n",vtree::vfa[x],x,vsz[vtree::vfa[x]],vsz[x]);
        vsz[vtree::vfa[x]]-=vsz[x];
    }
    rFOR(i,1,vtree::m) { // up
        int x=vtree::vid[i];
        if (x<=n) vsz[vtree::vfa[x]]+=vsz[x];
    }
    FOR(i,1,vtree::m) { // down
        int x=vtree::vid[i];
        if (x<=n) vsz[x]=vsz[vtree::vfa[x]];
    }
    FOR(i,1,vtree::m) {
        int x=vtree::vid[i];
        if (x<=n) continue;
        // if (pos==29) printf("%d-%d; sz=%d %d\n",x,vtree::vfa[x],vsz[x],vsz[vtree::vfa[x]]);
        ans+=(ll)vsz[x]*vsz[vtree::vfa[x]];
    }
}
vector<int> Nodes[maxn];
int main() {
    int n,i;
    scanf("%d",&n);
    LCA::init(n+n-1);
    FOR(i,1,n-1) {
        int u,v,x;
        scanf("%d%d%d",&u,&v,&x);
        addedge(u,n+i,1);
        addedge(v,n+i,1);
        Nodes[x].push_back(n+i);
    }
    FOR(i,1,n) sz[i]=1; sz[0]=n;
    LCA::dfs(1,0,0,0);
    LCA::initST(n+n-1);
    // FOR(i,1,n+n-1) printf("%d ",sz[i]); puts(" <- sz");
    FOR(i,1,n) {
        int m=0;
        for (int v:Nodes[i]) vtree::pid[++m]=v;
        if (!m) continue;
        // printf("solve pos=%d\n",i);
        for (int v:Nodes[i]) viz[v]=1;
        vtree::vbuild(m);
        solve(i,n);
        vtree::vclear();
        for (int v:Nodes[i]) viz[v]=0;
    }
    printf("%lld\n",ans);
}
/*
10
10 2 1
3 8 1
4 8 1
5 8 1
3 10 1
7 8 1
5 6 1
9 3 1
1 6 1

5
1 4 1
1 2 1
3 4 1
4 5 1

10
10 2 1
3 8 1
4 8 1
5 8 1
3 10 1
7 8 1
5 6 1
9 3 1
1 6 1

10
2 5 8
6 5 1
8 7 7
1 8 8
10 5 7
9 1 3
8 3 7
4 6 7
5 1 2
*/