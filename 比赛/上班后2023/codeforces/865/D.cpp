// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)
 
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
// const LL M=1e9+7;
const LL M=998244353;
// ll M=1;
const int maxn=2e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
    }
    return b<<z;
}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

//结论:p=2: C(n,k)%2==1当且仅当n&k==k (n|k==n)
int solve(ll n) {
    array<array<int,2>,2> dp{};
    dp[0][0]=1;
    for (ll k=0;k<=60;k++) {
        int c=(n>>k)&1;
        array<array<int,2>,2> nxt{};
        FOR_(a,0,1) {
            FOR_(x,0,2) {
                if (((a+x)&1)!=c) continue;
                int b=(a+x)/2;
                add_(nxt[b][0],dp[a][0]);
                add_(nxt[b][1],((x&1ll)<<k)%M*dp[a][0]%M);
                add_(nxt[b][1],dp[a][1]);
                // printf("nxt[%d][%d]: %lld * %lld\n",b,1,(x&1)<<k,dp[a][1]);
            }
        }
        swap(dp,nxt);
        // printf("k=%lld: (%d %d), (%d %d)  %lld\n",k,dp[0][0],dp[0][1],dp[1][0],dp[1][1],(1ll<<k));
    }
    return dp[0][1];
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        ll n; int m;
        scanf("%lld%d",&n,&m);
        // need to delete: m-ones
        if (m==1) printf("%lld\n",n%M);
        else if (m!=2) {
            if (n&1) {
                n=(n+1)/2%M;
                printf("%lld\n",n*n%M);
            } else {
                n=n/2%M;
                printf("%lld\n",n*(n+1)%M);
            }
        } else printf("%d\n",solve(n));
    }
}
/*
3 2 3
1 2 1
7 4 10
1 9 1 9 8 1 0
*/