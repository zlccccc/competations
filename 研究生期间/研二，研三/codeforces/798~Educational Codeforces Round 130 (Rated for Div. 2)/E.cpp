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
const LL M=998244353;
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

int A[107],B[107];
int dis[107][107];
int d[107];
bool ban[107];
int fa[107];
inline int getfa(int x) {
    if (fa[x]==x) return x;
    return fa[x]=getfa(fa[x]);
}
int sz[maxn];
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
int dp[maxn],nxt[maxn];
int main() {
    int i,j;
    int n; scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d",&A[i],&B[i]);
    memset(d,0x3f,sizeof(d));
    FOR(i,1,n) {
        FOR(j,1,n) dis[i][j]=abs(A[i]-A[j])+abs(B[i]-B[j]);
        FOR(j,1,n) if (i!=j) min_(d[i],dis[i][j]);
    }
    FOR(i,1,n) fa[i]=i;
    FOR(i,1,n) FOR(j,1,n) if (i!=j) {
        if (dis[i][j]==d[i]&&dis[i][j]==d[j]) {
            int x=getfa(i),y=getfa(j);
            if (x!=y) fa[x]=y;
        }
    }
    // FOR(i,1,n) printf("%d ",d[i]); puts("<- d");
    // FOR(i,1,n) printf("%d ",getfa(i)); puts("<- getfa");
    // FOR(i,1,n) FOR(j,1,n) printf("%d%c",dis[i][j]," \n"[j==n]);
    FOR(i,1,n) FOR(j,1,n) if (i!=j) {
        // if (dis[i][j]<d[j]) ban[getfa(j)]=1;
        if (dis[i][j]==d[i]&&dis[i][j]!=d[j]) ban[getfa(i)]=1;
        if (dis[i][j]!=d[i]&&getfa(i)==getfa(j)) ban[getfa(i)]=1;
    }
    // FOR(i,1,n) printf("%d ",ban[getfa(i)]); puts("<- ban getfa");
    FOR(i,1,n) sz[getfa(i)]++;
    vector<int> val;
    FOR(i,1,n) {
        if (ban[getfa(i)]) val.push_back(1);
        else if (fa[i]==i) val.push_back(sz[i]);
    }
    // for (int k:val) printf("%d ",k); puts("<- k");
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    dp[0]=1;
    for (int k:val) {
        FOR(i,0,n) nxt[i]=0;
        FOR(i,0,n) {
            add_(nxt[i+1],dp[i]%M);
            if (k!=1) add_(nxt[i+k],dp[i]%M);
        }
        FOR(i,0,n) dp[i]=nxt[i];
    }
    int ret=0;
    FOR(i,1,n) add_(ret,dp[i]*C(n,i)%M*fac[i]%M);
    // FOR(i,1,n) printf("%d*%lld ",dp[i],C(n,i)*fac[i]%M); puts("<- dp");
    printf("%d\n",ret);
}
/*
*/