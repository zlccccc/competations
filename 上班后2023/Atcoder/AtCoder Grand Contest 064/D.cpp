// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
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
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)

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
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

const int mod = 998244353;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    // mint operator~() const { return mint(1) / *this;}
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this;}
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this;}
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this;}
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this;}
    mint operator+(const mint &a)const { return mint(*this) += a;}
    mint operator-(const mint &a)const { return mint(*this) -= a;}
    mint operator*(const mint &a)const { return mint(*this) *= a;}
    mint operator/(const mint &a)const { return mint(*this) /= a;}
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (;t;t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};
struct comb {
    vector<mint> fac,inv; // f:fac; g:inv
    comb() {}
    comb(int MAX):fac(MAX),inv(MAX) {
        fac[0] = 1;
        rep_(i,1,MAX) fac[i] = fac[i-1]*i;
        inv[MAX-1] = fac[MAX-1].pow(mod-2);
        rrep_(i,1,MAX) inv[i-1] = inv[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return fac[a]*inv[b]*inv[a-b];
    }
} C(maxn);

char s[maxn];
int P[maxn];
int solve() {
    int n;
    scanf("%d",&n);
    scanf("%s",s+1);
    int m=0;
    FOR_(i,1,n-1) if (s[i]=='B') P[++m]=i;
    vector<vector<mint>> f(m+1,vector<mint>(P[m]+1,0));
    // FOR_(i,1,m) printf("%d ",P[i]);
    // puts("<- pos");
    f[0][0]=1;
    FOR_(i,1,P[m]) { // max-l
        // l的最大值是P[m]-m+1
        vector<vector<mint>> g(m+1,vector<mint>(P[m]+1,0));
        FOR_(j,0,m) FOR_(k,0,P[m]) g[j][k]+=f[j][k];
        FOR_(j,max(0,m-P[m]/i),m) { // 已经用了的number
            FOR_(k,0,P[m]) { // sum-val
                FOR_(l,1,min(m-j,(P[m]-k)/i)) {
                    if (P[j+l]<k+l*i) break;
                    // printf("i=%d: solve trans %d %d %d\n",i,j,k,l);
                    g[j+l][k+l*i]+=f[j][k]*C.inv[l];
                }
            }
        }
        // printf("i=%d\n",i);
        // FOR_(j,0,m) FOR_(k,0,P[m]) printf("%lld%c",g[j][k].x," \n"[k==P[m]]);
        f.swap(g);
    }
    mint ans;
    FOR_(i,0,P[m]) ans+=f[m][i]*C.fac[m];
    printf("%lld\n",ans.x);
    return 0;
}
int main() {
    solve();
    // while (1) solve();
}
/*
4
RBRB
5
BRRRB
6
RRRBRB
6
RRBRRB
20
RRBRRRBBRBBBBRBRBRBB
8
RRBRRRBB
*/