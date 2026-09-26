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

vector<pii> edge[maxn];
int A[maxn],id[maxn];
vector<int> ans;
int vis[maxn];
// [(left.x,left.y),(right.x,right.y),(up-val,down-val)]
void dfs(int x) { // topo, 后序遍历边swap会使得中序id shift
    sort(edge[x].begin(),edge[x].end(),[&](pii x,pii y){return id[x.first]<id[y.first];});
    vis[x]=1;
    for (auto p:edge[x]) {
        int v=p.first,i=p.second;
        if (id[v]<id[x]) continue;
        // printf("dfs %d %d %d\n",x,v,i);
        if (!vis[v]) dfs(v);
        ans.push_back(i);
    }
}
int main() {
    int T,_; T=1;
    // scanf("%d",&T);
    FOR(_,1,T){
        int n,m,i;
        scanf("%d%d",&n,&m);
        FOR(i,1,n) scanf("%d",&A[i]);
        FOR(i,1,m) {
            int u,v;
            scanf("%d%d",&u,&v);
            edge[u].push_back({v,i});
            edge[v].push_back({u,i});
        }
        int tot=0;
        FOR(i,1,n) if (!id[i]) {
            id[i]=++tot;
            for (int k=A[i];k!=i;k=A[k]) id[k]=++tot;
            if (!vis[i]) dfs(i);
            for (int k=A[i];k!=i;k=A[k]) if (!vis[k]) dfs(k);
        }
        // FOR(i,1,n) printf("%d ",id[i]); puts("<- id");
        for (int v:ans) printf("%d ",v); puts("");
    }
}
/*
5 4
3 5 4 2 1
4 1
2 4
1 5
1 3
*/