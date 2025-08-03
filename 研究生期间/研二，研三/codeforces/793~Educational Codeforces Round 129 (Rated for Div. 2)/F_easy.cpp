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

ll ans=0;
vector<pii> edge[maxn];
map<int,int> MP1[maxn],MPk[maxn];
int sz[maxn];
void dfs(int x,int fa) {
    map<int,int> ret;
    sz[x]=1;
    for (auto p:edge[x]) {
        int v=p.first,c=p.second;
        if (v==fa) continue;
        dfs(v,x); sz[x]+=sz[v];
        ans+=(ll)(sz[v]-MPk[v][c])*MP1[v][c];
        MP1[v][c]=sz[v]-MPk[v][c];
        MPk[v][c]=sz[v];
        if (MP1[x].size()<MP1[v].size()) swap(MP1[x],MP1[v]);
        for (auto now:MP1[v]) MP1[x][now.first]+=now.second;
        if (MPk[x].size()<MPk[v].size()) swap(MPk[x],MPk[v]);
        for (auto now:MPk[v]) MPk[x][now.first]+=now.second;
    }
}
int main() {
    int n,i;
    scanf("%d",&n);
    FOR(i,1,n-1) {
        int u,v,x;
        scanf("%d%d%d",&u,&v,&x);
        edge[u].push_back({v,x});
        edge[v].push_back({u,x});
    } dfs(1,0);
    FOR(i,1,n) ans+=(ll)(sz[1]-MPk[1][i])*MP1[1][i];
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