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

int A[maxn],B[maxn];
int solve() {
    int n,m;
    int i,j;
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",&A[i]);
    int k; scanf("%d",&k);
    FOR(j,1,k) scanf("%d",&B[j]);
    ll val=0,cnt=0;
    i=j=1;
    while (i<=n||j<=k) {
        if (i<=n&&cnt<=0) {
            int nowc=1;
            while (A[i]%m==0) A[i]/=m,nowc*=m;
            if (cnt&&A[i]!=val) return 0*puts("No");
            val=A[i]; cnt+=nowc; i++;
        } else if (j<=k&&cnt>=0) {
            int nowc=1;
            // printf("%d %d\n",B[j],m);
            while (B[j]%m==0) B[j]/=m,nowc*=m;
            if (cnt&&B[j]!=val) return 0*puts("No");
            val=B[j]; cnt-=nowc; j++;
        } else return 0*puts("No");
        // printf("i,j = %d %d: %lld %lld\n",i,j,val,cnt);
    }
    if (cnt!=0) return 0*puts("No");
    return 0*puts("Yes");
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        solve();
    }
}
/*
*/