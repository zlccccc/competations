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

vector<int> edge[maxn];
int A[maxn];
bool vis[maxn],done[maxn];
ll ans[maxn]; // ans: distance
void dfs(int x,int mid) {
    if (A[x]>mid) return;
    vis[x]=1; ans[x]=1; // count
    for (int v:edge[x]) {
        if (!vis[v]) dfs(v,mid);
        if (vis[v]&&!done[v]) ans[x]=INFF;
        else max_(ans[x],ans[v]+1);
    }
    done[x]=1;
    // printf("dfs %d %d; ans=%lld\n",x,mid,ans[x]);
}
int n,m,k;
int i;
bool solve(int mid) {
    FOR(i,1,n) vis[i]=done[i]=0,ans[i]=0;
    FOR(i,1,n) if (!vis[i]) dfs(i,mid);
    ll MAX=0;
    FOR(i,1,n) max_(MAX,ans[i]);
    return (MAX>=k);
} 
int main() {
    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,m) {
        int u,v; scanf("%d%d",&u,&v);
        edge[u].push_back(v);
    }
    int l=0,r=INF;
    while (l+1<r) {
        int mid=(l+r)/2;
        if (solve(mid)) r=mid;
        else l=mid;
    }
    if (r==INF) puts("-1");
    else printf("%d\n",r);
}
/*
1 4 6 7

5
7 6 1 8 2
*/