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

const int mod = 998244353;
struct mint {
  ll x;
  mint():x(0){}
  mint(ll x):x((x%mod+mod)%mod){}
  // mint(ll x):x(x){}
  mint& fix() { x = (x%mod+mod)%mod; return *this;}
  mint operator-() const { return mint(0) - *this;}
  mint operator~() const { return mint(1) / *this;}
  mint& operator+=(const mint& a){ if((x+=a.x)>=mod) x-=mod; return *this;}
  mint& operator-=(const mint& a){ if((x+=mod-a.x)>=mod) x-=mod; return *this;}
  mint& operator*=(const mint& a){ (x*=a.x)%=mod; return *this;}
  mint& operator/=(const mint& a){ (x*=a.pow(mod-2).x)%=mod; return *this;}
  mint operator+(const mint& a)const{ return mint(*this) += a;}
  mint operator-(const mint& a)const{ return mint(*this) -= a;}
  mint operator*(const mint& a)const{ return mint(*this) *= a;}
  mint operator/(const mint& a)const{ return mint(*this) /= a;}
  mint pow(ll t) const {
    if(!t) return 1;
    mint res = pow(t/2);
    res *= res;
    return (t&1)?res*x:res;
  }
  bool operator<(const mint& a)const{ return x < a.x;}
  bool operator==(const mint& a)const{ return x == a.x;}
};
typedef vector<mint> vm;
struct comb {
  vm f, g;
  comb(){}
  comb(int mx):f(mx+1),g(mx+1) {
    f[0] = 1; int i; g[0]=1;
    FOR(i,1,mx) f[i] = f[i-1]*i;
    g[mx] = f[mx].pow(mod-2);
    for(int i=mx;i>0;i--) g[i-1] = g[i]*i;
  }
  mint operator()(int a, int b) {
    if (a < b) return 0*printf("???");
    return f[a]*g[b]*g[a-b];
  }
} c(maxn);

mint dp[1007][1007];
mint f[maxn];
int main() {
    // printf("%lld\n",419834392ll*234*14%M);
    int _T,_; _T=1;
    scanf("%d",&_T);
    FOR(_,1,_T){
        int n,m,p,q,j;
        scanf("%d%d%d%d",&n,&m,&p,&q);
        mint P(p),Q(q); P=P/mint(100); Q=Q/mint(100);
        mint one=mint(1);
        mint a=one/(one-(one-P)*(one-Q));//done
        mint ans=0; int i;
        // printf("%lld\n",(a*mint(3)).x);
        // dp[x][y]=dp[x-1][y]*a*P*(1-Q)+dp[x-1][y-1]*a*P*Q
        //          +dp[x][y-1]*a*(1-P)*Q
        // printf("%lld  %lld\n",(a*(one-P)*Q).x,(one-a*P).x);
        // dp[0][0]=mint(1);
        // FOR(i,0,n-1) {
        //     FOR(j,0,m-1) {
        //         if (i||j) dp[i][j]=mint(0);
        //         if (i) dp[i][j]+=dp[i-1][j]*a*(one-P)*Q;//(a*(one-P)*Q);
        //         if (j) dp[i][j]+=dp[i][j-1]*a*P*(one-Q);
        //         //得分开算...
        //         if (i&&j) dp[i][j]+=dp[i-1][j-1]*a*P*Q;
        //         // printf("%lld%c",(dp[i][j]*mint(8)).x," \n"[j==m-1]);
        //     }
        //     ans=ans+dp[i][m-1]*a*P;
        //     printf("%lld ",(dp[i][m-1]*a*P).x);
        // }
        // puts("");
        mint pw=mint(1);
        FOR(i,0,min(n-1,m-1)) f[i]=c(m-1,i)*pw,pw=pw*Q;
        pw=(one-Q).pow(m-1-min(n-1,m-1));
        rFOR(i,0,min(n-1,m-1)) f[i]*=pw,pw=pw*(one-Q);
        FOR(i,1,min(n-1,m-1)) f[i]+=f[i-1];//use k -1 and -1
        pw=mint(1);
        mint mul=(a*P).pow(m-1);
        FOR(i,0,n-1) {
            // printf("c=%lld  %d %d %lld %lld\n",c(i+m-1,i).x,i,i+m-1,a.pow(m).x,(one-a).pow(i).x);
            mint noww=c(i+m-1,m-1)*(P*a)*pw*mul*f[min(m-1,n-1-i)];
            pw=pw*a*Q*(one-P);
            ans=ans+noww;
            // printf("%lld ",noww.x);
        }
        printf("%lld\n",ans.x);
    }
}
/*
100
50 100 100 50
100 50 50 100
*/