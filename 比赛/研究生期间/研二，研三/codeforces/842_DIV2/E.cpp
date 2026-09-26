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
// const LL M=998244353;
ll M=1;
const LL maxn=3e6+107;
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

ll fac[maxn],inv[maxn];
LL C(int n,int m) {
    if (n<m) return 0;
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
void init() {
    int i;
    fac[0]=1;
    FOR(i,1,3000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,3000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,3000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
}
void solve() {
    int i,j,n;
    scanf("%d%lld",&n,&M);
    init();
    // zero
    ll zero=1;
    ll one=(fac[2*n]%M*2-fac[n]+M-1+M)%M;
    ll two=C(2*n,n)*fac[n]%M*fac[n*2]%M*2%M;
    FOR(i,0,n) { // A in range[1->n]
        ll pos=C(n,i)*C(n,n-i)%M*fac[n]%M; // A in left
        ll val=C(n,n-i)*fac[n-i]%M*fac[n+i]%M; // -1: once
        // printf("i=%d: two-pos %lld, & val=%lld\n",i,pos,val);
        add_(two,M-pos*val%M);
    }
    add_(two,M-one);
    add_(two,M-zero);
    ll three=(fac[n*3]-two-one-zero+M*3)%M;
    // printf("zero,one,two,three=%lld %lld %lld %lld\n",zero,one,two,three);
    printf("%lld\n",(one+two*2+three*3)%M);
}
int main() {
    int T,_; T=1;
    // scanf("%d",&T);
    FOR(_,1,T){
        /*to solve the problem*/
        solve();
    }
}
/*
1000
1 100009067
2 100000357
69 999900997
*/