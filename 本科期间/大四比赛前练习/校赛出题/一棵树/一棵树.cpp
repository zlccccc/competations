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
template<typename T>inline void pr2(T x,int k=64) {ll i; rREP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}


struct Edges {
    int to; LL len; int next;
    Edges(int _to=0,LL _len=0,int _next=0):to(_to),len(_len),next(_next) {}
} edge[maxn*2]; int etot;
int head[maxn];
int fa[maxn];
LL uplen[maxn];
int id[maxn],dfn[maxn],idtot;
inline void addedge(int u,int v,LL len) {
    edge[++etot]=Edges(v,len,head[u]); head[u]=etot;
}
namespace LCA {//内部和外部dfn不同...
    int dep[maxn]; LL len[maxn];
    int st_dfn[maxn],tot;
    int ST[maxn*2][20];//only L
    void dfs(int x,int f,int d,LL l) {
        int i; dep[x]=d; len[x]=l;
        st_dfn[x]=++tot; ST[tot][0]=x;
        ::id[++idtot]=x; ::dfn[x]=idtot;
        for (i=head[x]; ~i; i=edge[i].next) if (edge[i].to!=f) {
                int v=edge[i].to;
                ::fa[v]=x; ::uplen[v]=edge[i].len;
                dfs(v,x,d+1,l+edge[i].len);
                ST[++tot][0]=x;
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
    inline LL dis(int x,int y) {
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
    LL vlen[maxn];
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
    }
    void vclear() {
        int i;
        FOR(i,1,m) mark[vfa[vid[i]]]=0;
        FOR(i,1,m) mark[vid[i]]=0;
    }
}

int tid[maxn];
int Ans[maxn],ans;
int cnt[maxn];
void solve(int tot) {
    int i;
    FOR(i,1,vtree::m) cnt[vtree::vid[i]]=0;
    rFOR(i,1,vtree::m) {
        int x=vtree::vid[i];
        if (vtree::mark[x]) cnt[x]++;
        if (i>1) cnt[vtree::vfa[x]]+=cnt[x];
        add_(ans,vtree::vlen[x]*cnt[x]%M*(tot-cnt[x])%M);
    }
}
int main() {
    int _,T;
    scanf("%d",&T);
    assert(1<=T&&T<=4);
    FOR(_,1,T) {
        int n,q,i,k,x;
        scanf("%d",&n);
        assert(1<=n&&n<=100000);
        FOR(i,1,n) 
        FOR(i,1,n) tid[i]=0;
        FOR(i,1,n) scanf("%d",&x),tid[x]=i;
        FOR(i,1,n) assert(tid[i]);
        LCA::init(n);
        FOR(i,1,n-1) {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            // assert(1<=w&&w<=1100000000);
            addedge(u,v,w); addedge(v,u,w);
        } LCA::dfs(1,0,0,0);
        LCA::initST(n);
        FOR(k,1,n){
            int tot=0;
            for (i=k;i<=n;i+=k) vtree::pid[++tot]=tid[i];
            vtree::vbuild(tot);
            ans=0; solve(tot); Ans[k]=ans;
            vtree::vclear();
        } scanf("%d",&q);
        while (q--) {
            int x; scanf("%d",&x);
            printf("%d\n",Ans[x]);
        }
    } char str[100];
    assert(scanf("%s",str)==EOF);
    return 0;
}
/*
*/
