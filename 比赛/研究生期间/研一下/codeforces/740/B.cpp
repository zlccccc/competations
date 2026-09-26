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
const LL maxn=4e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
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

//f(x)=f(x-1)+f(x/k)
//f(x/y>=k)+=f(x)
int f[maxn],g[maxn];//g:prefix-sum
int main() {
    int n,m,i;
    scanf("%d%d",&n,&m);
    f[1]=1;
    FOR(i,1,n) {
        add_(f[i],f[i-1],m);
        // int k; FOR(k,1,n-1) add_(f[i],f[i-k],m);
        // int k; FOR(k,2,n) add_(f[i],(f[i/k]-f[i/k-1]+M),m);
        add_(g[i],g[i-1],m); add_(f[i],g[i],m);
        for (int j=i+i;j<=n;j+=i) {
            add_(g[j],f[i],m);
            add_(g[j],m-f[i-1],m);
            if (i>=2) add_(g[j],f[i-2],m);
        }
        // int k; FOR(k,1,n) printf("%d ",g[k]); printf("<-f=%d ;g\n",f[i]);
        add_(f[i],f[i-1],m); // prefix sum
    }
    // FOR(i,1,n) printf("%d ",f[i]); puts("<- f");
    // FOR(i,1,n) printf("%d ",g[i]); puts("<- f");
    
    add_(f[n],m-f[n-1],m);
    printf("%d\n",f[n]);
}
/*
6 100000000
*/