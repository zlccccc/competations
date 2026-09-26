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
#include <functional>
#include <random>
#include <unordered_set>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

// #define DEBUG
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
// ll M=1;
const LL maxn=1e6+107;
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
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
template<typename T>inline void mod_M(T &A,ll B=M) {A%=B; A+=B; A%=B;}

//sum{pow(i,k)}(1->n)
ll B[maxn],pw[maxn];
ll A[maxn];
ll INV[10007];
LL inv[10002];//inverse
LL fac[10002];//Factorial
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
} ll SUM_N_K(int n,int k) {
    ll pw=1,now=0; int i;
    FOR(i,1,k+1) {
        pw=pw*(n+1)%M;
        now+=INV[k+1]*C(k+1,i)%M*B[k+1-i]%M*pw%M;
    } mod_M(now);
    return now;
}
void initialize() {
    int i,j;
    fac[0]=1;
    FOR(i,1,10000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1; INV[0]=INV[1]=1;
    FOR(i,2,10000) INV[i]=inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,10000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    B[0]=1;
    FOR(i,1,2000) {
        FOR(j,0,i-1) B[i]-=INV[i+1]*C(i+1,j)%M*B[j]%M; mod_M(B[i]);
    }
//    FOR(i,0,2000) printf("%lld ",B[i]);
}

int f[57][57]; // same
int g[57];
int main() {
    initialize();
    int T,_; T=1;
    // scanf("%d",&T);
    FOR(_,1,T){
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
        int n,k,K,i,j,a,b;
        scanf("%d%d",&n,&K);
        FOR(i,1,n) {
            FOR(j,0,i-1) FOR(k,j+1,n-i) { //j smaller, k larger
                FOR(a,0,i-1-j) FOR(b,0,n-i-k) { // a larger(l), b smaller(r)
                    add_(f[j+b][k+a],C(i-1,j)*C(n-i,k)%M
                                    *C(i-1-j,a)%M*C(n-i-k,b)%M); // j<,a>(l),k>,b<(r)
                }
            }
        }
        int ans=0;
        FOR(i,0,n) FOR(j,0,n) if (f[i][j]) {
            // printf("solve %d %d %d\n",i,j,f[i][j]);
            // FOR(a,1,K) {
            //     add_(ans,a*powMM(a-1,i)%M*powMM(K-a,j)%M*f[i][j]%M);
            // }
            FOR(a,0,i) FOR(b,0,j) {
                add_(g[i-a+b+1],C(i,a)*C(j,b)%M*powMM(K,j-b)%M*powMM(M-1,a+b)%M*f[i][j]%M);
            }
        }
        // FOR(i,0,n) FOR(a,1,K) add_(ans,powMM(a,i)*g[i]%M);
        FOR(i,0,n) add_(ans,g[i]*SUM_N_K(K,i)%M);
        printf("%d\n",ans);
    }
}
/*
10
3 3
5 6
12 30
*/