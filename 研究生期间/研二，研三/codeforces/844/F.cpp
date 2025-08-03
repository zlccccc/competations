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
// const LL M=1e9+7;
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
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

ll f[507][507]; // f:合法(...)序列数量, prefix-min=-x (x<=0)
ll g[507][507];
ll prefix[507];
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
const int MID=502;
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
bool solve() {
    int n,p,q,i,j,k;
    if (scanf("%d%d",&n,&q)!=2) return 0;
    p=powMM(10000,M-2)*q%M;
    memset(f,0,sizeof(f)); // f[x][k]: prefix-min <= -x
    // f[0][0]=1;
    FOR(i,0,n+1) f[0][i]=1; // prefix-min <= -x
    FOR(i,1,n) {
        FOR(k,0,n) {
            if (k>i+1) {f[i][k]=f[i][k-1]; continue;}
            FOR(j,0,i-1) {
                // last >= k-1 / k+1; other >= k
                // printf("i=%d; k=%d: j=%d  mul=%d; C=%d\n",i,k,j,mul,C(i,i-j-1));
                if (k) add_(f[i][k],f[i-j-1][k-1]*C(i,i-j)%M*(M+1-p)%M*f[j][k]%M%M); // )(
                add_(f[i][k],f[i-j-1][k+1]*C(i,i-j)%M*p%M*f[j][k]%M%M); // (); MIN=0
            }
        }
        // FOR(k,0,n) printf("%lld ",f[i][k]); puts("  <- f");
        // FOR(k,0,i) printf("%lld ",f[i][k]*10*10%M); puts("  <- f * 100");
        // FOR(k,0,i) printf("%lld ",f[i][k]*100000%M); puts("  <- f * 100000");
    }
    // printf("%lld\n",519087064ll*100%M);
    // printf("%lld\n",119387743ll*100000%M);

    // add_(f[n][0],M-f[n][1]);
    ll mul=1;
    FOR(i,1,n) mul=mul*(i*2-1)%M;
    printf("%lld\n",f[n][0]*powMM(mul,M-2)%M);
    return 1;
}
int main() {
    int i;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    while (solve());
}
/*
1 7500
2 6000
5 4000
*/