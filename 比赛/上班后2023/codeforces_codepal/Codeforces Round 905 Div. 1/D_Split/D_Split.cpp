#define DEBUG
// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC
// target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I, N) for (int I = 0, END = (N); I < END; I++)
#define rREP_(I, N) for (int I = (N)-1; I >= 0; I--)
#define rep_(I, S, N) for (int I = (S), END = (N); I < END; I++)
#define rrep_(I, S, N) for (int I = (N)-1, START = (S); I >= START; I--)
#define FOR_(I, S, N) for (int I = (S), END = (N); I <= END; I++)
#define rFOR_(I, S, N) for (int I = (N), START = (S); I >= START; I--)

#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n", str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef long long LL;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int INF = 0x3f3f3f3f;
const LL INFF = 0x3f3f3f3f3f3f3f3fll;
const LL maxn = 1e6 + 107;
const double pi = acos(-1.0);
const double eps = 0.0000000001;
template <typename T> inline T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }
template <typename T> inline void pr2(T x, int k = 64) {
    REP_(i, k) debug("%d", (x >> i) & 1);
    debug(" ");
}
template <typename T> inline void add_(T &A, int B, ll MOD) { A += B, (A >= MOD) && (A -= MOD); }
template <typename T> inline void mul_(T &A, ll B, ll MOD) { A = (A * B) % MOD; }
template <typename T> inline void mod_(T &A, ll MOD) { A %= MOD, A += MOD, A %= MOD; }
template <typename T> inline void max_(T &A, T B) { (A < B) && (A = B); }
template <typename T> inline void min_(T &A, T B) { (A > B) && (A = B); }
template <typename T> inline T abs(T a) { return a > 0 ? a : -a; }
template <typename T> inline T fastgcd(T a, T b) {
    int az = __builtin_ctz(a), bz = __builtin_ctz(b), z = min(az, bz), diff;
    b >>= bz;
    while (a) {
        a >>= az, diff = b - a;
        az = __builtin_ctz(diff);
        min_(b, a), a = abs(diff);
    }
    return b << z;
}
int startTime;
void startTimer() { startTime = clock(); }
void printTimer() { debug("/--- Time: %ld ms ---/\n", clock() - startTime); }
typedef array<int, 4> ar4;
typedef array<int, 3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

// const int mod = 1e9 + 7;
const int mod = 998244353;
struct mint {
    long long x;
    mint() : x(0) {}
    mint(long long x) : x((x % mod + mod) % mod) {}
    // mint(long long x):x(x){}
    mint &fix() { return x = (x % mod + mod) % mod, *this; } // Not Used
    mint operator-() const { return mint(0) - *this; }
    mint operator~() const { return mint(1) / *this; }
    mint &operator+=(const mint &a) { return ((x += a.x) >= mod) && (x -= mod), *this; }
    mint &operator-=(const mint &a) { return ((x += mod - a.x) >= mod) && (x -= mod), *this; }
    mint &operator*=(const mint &a) { return (x *= a.x) %= mod, *this; }
    mint &operator/=(const mint &a) { return (x *= a.pow(mod - 2).x) %= mod, *this; }
    mint operator+(const mint &a) const { return mint(*this) += a; }
    mint operator-(const mint &a) const { return mint(*this) -= a; }
    mint operator*(const mint &a) const { return mint(*this) *= a; }
    mint operator/(const mint &a) const { return mint(*this) /= a; }
    bool operator<(const mint &a) const { return x < a.x; }
    bool operator==(const mint &a) const { return x == a.x; }
    mint pow(long long t) const {
        mint ret = 1, cur = x;
        for (; t; t >>= 1ll, cur = cur * cur)
            if (t & 1)
                ret = ret * cur;
        return ret;
    }
};
// struct comb {
//     vector<mint> f, g; // f:fac; g:inv
//     comb() {}
//     comb(int mx) : f(mx + 1), g(mx + 1) {
//         f[0] = 1;
//         rREP_(i, mx) f[i] = f[i - 1] * i;
//         g[mx] = f[mx].pow(mod - 2);
//         for (int i = mx; i > 0; i--)
//             g[i - 1] = g[i] * i;
//     }
//     mint operator()(int a, int b) {
//         if (a < b)
//             return 0;
//         return f[a] * g[b] * g[a - b];
//     }
// } C(maxn);

inline int lowbit(int x) {return x&-x;}
int T[maxn];
void update(int x,int val) {
    for (;x<=1e6;x+=lowbit(x)) T[x]+=val;
}
int query(int x) {
    int ret=0;
    for (;x;x-=lowbit(x)) ret+=T[x];
    return ret;
}

int A[maxn],p[maxn];
vector<ar3> chg[maxn];
vector<pii> que[maxn];
int ans[maxn];
void solve(int _) {
    int n;
    scanf("%d", &n);
    FOR_(i,1,n) scanf("%d",&A[i]);
    FOR_(i,1,n) p[A[i]]=i;
    set<int> S,rS;
    S.insert(n+1); S.insert(0);
    FOR_(i,0,n+1) rS.insert(i); // larger (on left)
    FOR_(i,1,n) chg[i].clear();
    rFOR_(i,1,n) {
        S.insert(p[i]);
        auto it=rS.lower_bound(p[i]);
        it--; int m=*it+1;
        it=rS.lower_bound(p[i]);
        it++; int r=*it-1;
        if (m!=1) {
            it=S.lower_bound(m-1);
            it--; int l=*it+1;
            // if (l==m) continue;
            chg[l].push_back({m,r,1});
            chg[m].push_back({m,r,-1});
            // printf("%d -> [%d(p=%d) -> %d]\n",l,m,p[i],r);
        }
        rS.erase(p[i]);
    }
    FOR_(i,1,n) T[i]=0;
    FOR_(i,1,n) que[i].clear();
    int q;
    scanf("%d",&q);
    FOR_(i,1,q) {
        int l,r;
        scanf("%d%d",&l,&r);
        que[l].push_back({r,i});
    }
    FOR_(i,1,n) {
        for (auto now:chg[i]) {
            // printf("%d: update %d %d %d\n",i,now[0],now[1],now[2]);
            update(now[0],now[2]);
            update(now[1]+1,-now[2]);
        }
        for (auto now:que[i]) {
            // printf("%d: query %d %d\n",i,now.first,now.second);
            int x=query(now.first);
            ans[now.second]=x;
        }
    }
    FOR_(i,1,q) {
        if (ans[i]) puts("Yes");
        else puts("No");
    }
}
int main() {
    int T = 1;
    // scanf("%d",&T);
    FOR_(_, 1, T) solve(_);
}
/*
 */