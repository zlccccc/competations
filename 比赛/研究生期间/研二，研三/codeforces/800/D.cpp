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

int n,_rev,_max;
int A[maxn],dp[maxn];
int MIN[maxn];
int f[maxn],g[maxn];
inline int lowbit(int x) {return x&-x;}
void update(int x,int val){
    if (_rev) x=n-x+1;
    if (_max) val=n-val+1;
    for (;x<=n;x+=lowbit(x)) min_(MIN[x],val);
}
int query(int x) {
    if (_rev) x=n-x+1;
    int ret=n;
    for (;x;x-=lowbit(x)) min_(ret,MIN[x]);
    if (_max) ret=n-ret+1;
    return ret;
}
vector<pii> a[maxn],b[maxn];
void solve() {
    int i;
    // int a,b,j;
    // FOR(i,1,n) FOR(a,i+1,n) FOR(b,a+1,n) FOR(j,b+1,n) {
    //     // i<a<b<j: dp[i]=min(dp[i],j)
    //     if (A[i]>A[a]&&A[j]>A[i]&&A[b]>A[j]) min_(dp[i],j-1); // not right
    // }
    FOR(i,1,n) a[i].clear(),b[i].clear();
    FOR(i,1,n) MIN[i]=n+1; _rev=1; _max=1; // rev:small/large
    FOR(i,1,n) {b[query(A[i])].push_back({i,A[i]}); update(A[i],i);} // find b
    FOR(i,1,n) MIN[i]=n+1; _rev=0; _max=0;
    rFOR(i,1,n) {a[query(A[i])].push_back({i,A[i]}); update(A[i],i);} // find a
    FOR(i,1,n) MIN[i]=n+1; _rev=1; _max=0;
    // FOR(i,1,n) for (auto p:a[i]) printf("Q-B %d->%d %d\n",i,p.first,p.second);
    // FOR(i,1,n) for (auto p:a[i]) printf("Q-A %d->%d %d\n",i,p.first,p.second);
    rFOR(i,1,n) {
        for (auto p:a[i]) min_(dp[p.first],query(p.second));
        for (auto p:b[i]) update(p.second,p.first-1);
    }
}
int main() {
    int i;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n) dp[i]=n;
    solve();
    // FOR(i,1,n) printf("%d ",dp[i]); puts("<- dp");
    FOR(i,1,n) A[i]=n-A[i]+1;
    solve();
    // FOR(i,1,n) printf("%d ",dp[i]); puts("<- dp");
    ll ans=0;
    rFOR(i,1,n-1) min_(dp[i],dp[i+1]);
    FOR(i,1,n) ans+=dp[i]-i+1;
    // FOR(i,1,n) printf("%d ",dp[i]); puts("<- dp");
    printf("%lld\n",ans);
}
/*
*/