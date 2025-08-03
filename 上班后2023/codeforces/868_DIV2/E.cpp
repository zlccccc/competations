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

const int mod = 1e9+7;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    mint operator~() const { return mint(1) / *this;}
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
// struct comb {
//     vector<mint> fac,inv; // f:fac; g:inv
//     comb() {}
//     comb(int MAX):fac(MAX),inv(MAX) {
//         fac[0] = 1;
//         rep_(i,1,MAX) fac[i] = fac[i-1]*i;
//         inv[MAX-1] = fac[MAX-1].pow(mod-2);
//         rrep_(i,1,MAX) inv[i-1] = inv[i]*i;
//     }
//     mint operator()(int a, int b) {
//         if (a < b) return 0;
//         return fac[a]*inv[b]*inv[a-b];
//     }
// } C(maxn);

int f[maxn],g[maxn];
int cur[maxn];
int fa[maxn],cnt[maxn];
inline int getfa(int x) {
    if (x==fa[x]) return x;
    return fa[x]=getfa(fa[x]);
}
void solve() {
    int n,l,r; scanf("%d%d%d",&n,&l,&r);
    if (0) 
    {
        memset(f,0,sizeof(f));
        memset(g,0,sizeof(g));
        FOR_(i,1,n) {
            FOR_(j,l,r) if (i-j>=0) {
                FOR_(k,0,i-j) cur[f[k]^f[i-j-k]]++;
            }
            while (cur[f[i]]) f[i]++;
            FOR_(j,0,f[i]) printf("%d ",cur[j]); printf("<- cur %d(=%d)\n",i,f[i]);
            FOR_(j,l,r) if (i-j>=0) {
                FOR_(k,0,i-j) cur[f[k]^f[i-j-k]]--;
            }
            FOR_(j,l,r) if (i-j>=0) cur[f[i-j]]++;
            while (cur[g[i]]) g[i]++;
            FOR_(j,l,r) if (i-j>=0) cur[f[i-j]]--;
        }
        FOR_(i,1,n) printf("%d ",f[i]); puts(" <- f");
        FOR_(i,1,n) printf("%d ",g[i]); puts(" <- g");
    }
    // l<r: 无论奇偶, n>k的时候mex!=0
    // 小于的时候直接算max即可
    // mex_f=0: 0->l-1
    // mex_g!=0: 0->l+r-1
    FOR_(i,1,l+r-1) g[i]=i/l;
    FOR_(i,1,n) fa[i]=i;
    FOR_(i,1,n) {
        int x,y;
        scanf("%d%d",&x,&y);
        x=getfa(x); y=getfa(y);
        if (x!=y) fa[x]=y;
    }
    int ans=0;
    memset(cnt,0,sizeof(cnt));
    FOR_(i,1,n) cnt[getfa(i)]++;
    FOR_(i,1,n) if (fa[i]==i) ans^=g[cnt[i]];
    if (!ans) puts("Bob");
    else puts("Alice");
}

int main() {
    int T,_; T=1;
    // scanf("%d",&T);
    // T=10000;
    FOR(_,1,T) {
        solve();
    }
}
/*
100 3 100
100 3 4
20 2 3
100 1 2

6 2 3
1 2
2 3
3 1
4 5
5 6
6 4

6 1 2
1 2
2 3
3 1
4 5
5 6
6 4

12 1 3
1 2
2 3
3 1
4 5
5 6
6 7
7 4
8 9
9 10
10 11
11 12
12 8

*/