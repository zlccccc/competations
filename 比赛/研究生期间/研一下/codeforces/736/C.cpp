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
const LL M=1e9+7;
const LL maxn=3e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

LL inv[3000007];//inverse
LL fac[3000007];//Factorial
LL CXX(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
// int A[maxn],B[maxn],C[maxn];
int C[maxn];
int main() {
    int n,q,i,j,_;
    fac[0]=1;
    FOR(i,1,3000003) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,3000003) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,3000003) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
    scanf("%d%d",&n,&q);
    // A[0]=1;
    // FOR(j,1,n) {
    //     rFOR(i,0,3*n) A[i+1]+=A[i];
    //     rFOR(i,0,3*n) A[i+1]+=A[i];
    //     rFOR(i,0,3*n) A[i+1]+=A[i];
    //     FOR(i,0,3*n) B[i]+=A[i];
    //     FOR(i,0,3*n) printf("%d ",B[i]); puts("<- B");
    // }
    // FOR(_,0,n*3) {
    //     ll ans=0; int k;
    //     FOR(k,(_+2)/3,n) ans+=CXX(k*3,_);
    //     printf("%lld\n",ans);
    // }
    // \sum((i+x)^3); 
    ll inv3=powMM(3,M-2);
    FOR(i,0,3*n) C[i]=CXX(3*n+3,i+1);
    FOR(i,0,3*n) {
        C[i]=C[i]*inv3%M;
        add_(C[i+1],M-3ll*C[i]%M);
        add_(C[i+2],M-C[i]%M);
    }
    // FOR(i,0,3*n) printf("%d ",C[i]); puts("<- C");
    FOR(_,1,q) {
        int x; scanf("%d",&x);
        printf("%d\n",C[x]);
    }


    // FOR(i,1,n) 
    // // FOR(i,0,MAX) FOR(j,0,MAX) C[i+j]+=A[i]*B[j];
    // // FOR(_,0,MAX) printf("%d ",A[_]); puts("<- A[i]");
    // FOR(_,0,MAX) printf("%d ",B[_]); puts("<- B[i]");
    // // FOR(_,0,MAX) printf("%d ",C[_]); puts("<- C[i]");
}
/*
5 4
*/