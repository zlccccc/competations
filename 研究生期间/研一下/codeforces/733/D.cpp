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
const LL maxn=1.2e6+107;
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

LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
ll getval(int x,int y) {
    if (x<0||x>y) return 0;
    return C(y,x);
    // printf("getval %lld %lld %lld\n",l,r,mid);
}
int main() {
    int i;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)

    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int l,r,n;
        scanf("%d%d%d",&n,&l,&r);
        ll ans=0;
        ll Mor=max(0,min(-l-4*n,r-4*n));
        ans=Mor*getval(n/2,n)%M; l+=Mor; r-=Mor;
        if (n&1) ans+=Mor*getval(n/2+1,n),ans%=M;
        FOR(i,1,n*10) {
            // l+i,r-i: all-ok
            // 1->l+i-1: only -;
            // r-i+1->n: only +;
            int xl=max(1,l+i)-1,xr=n+1-min(r-i+1,n+1);
            int mid=(n-xl-xr);
            if (mid<0) continue;
            // printf("get %d: %d %d %d\n",i,xl,xr,mid);
            ans+=getval(n/2-xl,mid);
            if (n&1) ans+=getval(n/2+1-xl,mid);
            ans%=M;
        }
        printf("%lld\n",ans);
    }
}
/*
10
3 -20 26
4 -3 5
42 -33 55
69 -42 146

*/
