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
// const LL M=998244353;
ll M=1;
const LL maxn=3e5+107;
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

ll A[maxn],B[maxn];
int solve() {
    int n,i;
    ll x,y;
    scanf("%d%lld%lld",&n,&x,&y);
    FOR(i,1,n) scanf("%lld",&A[i]);
    sort(A+1,A+1+n); A[n+1]=y+A[n];
    FOR(i,1,n) B[i]=max(B[i-1],A[i]-i+1); B[n+1]=y+B[n];
    // FOR(i,1,n) printf("%lld ",B[i]); puts("<- B");
    ll ans=0; int l=0;
    while (x<y) {
        while (B[l]<=x) l++; l--;
        // int l=upper_bound(B+1,B+1+n,x)-B-1; // 1->l: add; l+1->n: div
        if (x+l>=y) return 0*printf("%lld\n",ans+(y-x));
        int valone=l+l-n;
        // printf("solve l=%d; valone=%d\n",l,valone);
        if (valone<=0) return 0*puts("-1");
        ll kl=(B[l+1]-x+valone-1)/valone;
        // printf("todo solve x+kl %lld %lld\n",x+kl*valone,B[l+1]);
        if (x+l+kl*valone>=y) {
            ll nkl=(y-x-l+valone-1)/valone;
            ans+=nkl*n; x+=nkl*valone;
            return 0*printf("%lld\n",ans+(y-x));
        } else ans+=kl*n,x+=kl*valone;
    }
    return 0*printf("%lld\n",ans);
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) solve();
}
/*
30
7 2 10
3 1 9 2 5 20 8
7 2 2
3 1 9 2 5 20 8
7 2 3
3 1 9 2 5 20 8
7 2 4
3 1 9 2 5 20 8
7 2 5
3 1 9 2 5 20 8
7 2 6
3 1 9 2 5 20 8
7 2 7
3 1 9 2 5 20 8
7 2 8
3 1 9 2 5 20 8
7 2 9
3 1 9 2 5 20 8
7 2 10
3 1 9 2 5 20 8
7 2 11
3 1 9 2 5 20 8
7 2 12
3 1 9 2 5 20 8
7 2 13
3 1 9 2 5 20 8
7 2 14
3 1 9 2 5 20 8
7 2 15
3 1 9 2 5 20 8
7 2 16
3 1 9 2 5 20 8
7 2 17
3 1 9 2 5 20 8

*/