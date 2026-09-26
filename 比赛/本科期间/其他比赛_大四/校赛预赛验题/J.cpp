#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
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

ll f[maxn],g[maxn];//f:all_cnt; g:have_1
void getbruteforce(ll n) {
    int i,j;
    FOR(i,1,n) {
        f[i]+=1;
        for (j=i+i;j<=n;j+=i) add_(f[j],f[i]);
        // FOR(j,2,i) if (i%j==0) f[i]+=f[i/j];
        // FOR(j,1,i-1) if (i%j==0) f[i]+=f[j];
    } FOR(i,1,n) {
        add_(g[i],f[i]/2);
        if (i==1) g[i]=1;
        for (j=i+i;j<=n;j+=i) add_(g[j],(ll)j/i*g[i]%M);
        // FOR(j,2,i) if (i%j==0) g[i]+=j*g[i/j];
        // FOR(j,1,i-1) if (i%j==0) g[i]+=i/j*g[j];
    }
    // FOR(i,1,n) printf("%lld(%d) ",f[i],i); puts(" <- f");
    // FOR(i,1,n) printf("%lld(%d) ",g[i],i); puts(" <- g");
    FOR(i,1,n) add_(f[i],f[i-1]);
    FOR(i,1,n) add_(g[i],g[i-1]);
    // FOR(i,1,n) printf("%lld(%d) ",f[i],i); puts(" <- sumf");
    // FOR(i,1,n) printf("%lld(%d) ",g[i],i); puts(" <- sumg");
    // FOR(i,1,n) printf("%lld(%d) ",g[i]*2-(f[i]+1)/2,i); puts(" <- sumg");
}
const int MAX=1e6;
unordered_map<int,int> MPf,MPg;
int getf(int n) {
    if (n<=MAX) return f[n];
    if (MPf.count(n)) return MPf[n];
    if (n==0) return 0;
    // printf("get:%d\n",n);
    int ret=n; int l;
    FOR(l,1,n) {
        int t=n/l,r=n/t;
        if (t==1) break;
        ret=(ret+(ll)(t-1)*(getf(r)-getf(l-1)+M))%M;
        l=r;
    } return MPf[n]=ret;
}
const int inv2=powMM(2,M-2);
int getg(int n) {
    if (n<=MAX) return g[n];
    if (MPg.count(n)) return MPg[n];
    if (n==0) return 0;
    int ret=(ll)(getf(n)+1)*inv2%M; int l;
    FOR(l,1,n) {
        int t=n/l,r=n/t;
        if (t==1) break;
        ret=(ret+((ll)(t+2)*(t-1)/2)%M*(getg(r)-getg(l-1)+M))%M;
        l=r;
    }
    // printf("getg:%lld : %lld\n",n,ret);
    return MPg[n]=ret;
}
int main() {
    getbruteforce(MAX);
    // printf("getf(18):%lld\n",getf(18));
    // printf("getg(18):%lld\n",getg(14));
    int n;
    scanf("%d",&n);
    printf("%lld\n",(getg(n)*2-(ll)(getf(n)+1)*inv2%M+M)%M);
    // printf("%d %d\n",MPg.size(),MPf.size());
}
/*
1000000000
*/