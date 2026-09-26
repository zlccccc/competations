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

int tot;
vector<int> edge[maxn],tree[maxn];
int color[maxn],id[maxn],out[maxn];
int fa[maxn][21],depth[maxn];
void dfs(int x,int col,int dep=0) {
    color[x]=col^1; id[x]=++tot; depth[x]=dep;
    for (int v:edge[x]) {
        if (color[v]!=-1) continue;
        fa[v][0]=x; int i;
        rep(i,1,21) fa[v][i]=fa[fa[v][i-1]][i-1];
        dfs(v,col^1,dep+1);
        tree[x].push_back(v);
    } out[x]=tot;
}
int lca(int x,int y) {
    int i;
    if (depth[x]<depth[y]) swap(x,y);
    rREP(i,21) if (depth[x]-depth[y]>=(1<<i)) x=fa[x][i];
    if (x==y) return x;
    rREP(i,21) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int diff[maxn],same[maxn];
int diff_all=0,same_all=0;
int root=0;
void solve(int x) {
    for (int v:edge[x]) { // same/diff
        if (color[x]==color[v]) same[x]++,same[lca(x,v)]--;
        else diff[x]++,diff[lca(x,v)]--;
        // printf("add x=%d  v=%d  lca=%d\n",x,v,lca(x,v));
    }
    for (int v:tree[x]) {
        solve(v);
        diff[x]+=diff[v];
        same[x]+=same[v];
    }
    // solve!
    int linesame=same[x],othersame=same_all-linesame;
    int linediff=diff[x],otherdiff=diff_all-linediff;
    // same color
    if (linediff+othersame<=1) root=x;
    // printf("x=%d: line:%d %d other:%d %d\n",x,linesame,linediff,othersame,otherdiff);
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m,i;
        scanf("%d%d",&n,&m);
        tot=0;
        FOR(i,1,n) edge[i].clear(),tree[i].clear(),color[i]=-1;
        FOR(i,1,n) same[i]=diff[i]=0;
        FOR(i,1,m) {
            int u,v; scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        dfs(1,0);
        diff_all=0; same_all=0;
        FOR(i,1,n) for (int v:edge[i]) if (color[v]==color[i]) same_all++,root=v; else diff_all++;
        same_all/=2; diff_all/=2;
        if (same_all<=1) {
            puts("YES");
            FOR(i,1,n) printf("%d",color[i]^color[root]^1);
            puts("");
        } else {
            root=0;
            solve(1);
            if (root) {
                // printf("root=%d\n",root);
                puts("YES");
                FOR(i,1,n) printf("%d",color[i]^(id[root]<=id[i]&&id[i]<=out[root])^color[root]);
                puts("");
            } else puts("NO");
        }
    }
}
/*
*/