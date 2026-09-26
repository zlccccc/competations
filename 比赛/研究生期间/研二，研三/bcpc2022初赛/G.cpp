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

// prufer序列性质
LL inv[1000010];//inverse
LL fac[1000010];//Factorial
LL C(int n,int m) {
    if (n<m) return 0;
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
ll f[maxn];
int main() {
    int i;
    fac[0]=1;
    FOR(i,1,1000007) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000007) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000007) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)

    FOR(i,1,1000000) {
        add_(f[i],C(i,4)*2*2%M);
        add_(f[i],C(i,3)*3*2%M);
        add_(f[i],C(i,2)%M);// intersect
    }
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m;
        scanf("%d%d",&n,&m);
        ll base=C(n,2)*C(n,2)%M*C(m,2)%M*C(m,2)%M;
        ll inside=C(n,4)*C(m,4)%M; // inside
        ll div=f[n]*f[m]%M;
        // printf("%lld %lld %lld\n",base,div,inside);
        printf("%lld\n",(base-div+inside+inside+M)*inv[2]%M);
    }
}
/*
2
4 4
5 5
*/