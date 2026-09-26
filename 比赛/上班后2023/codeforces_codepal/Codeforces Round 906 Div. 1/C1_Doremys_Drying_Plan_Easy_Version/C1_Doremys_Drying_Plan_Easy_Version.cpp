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

void solve(int _) {
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    int zero=0;
    vector<int> Cnt(m+2); // one
    vector<map<int,int>> MP(m+2); // two
    vector<vector<pii>> S(n+2);
    FOR_(i,1,m) {
        int l,r;
        scanf("%d%d",&l,&r);
        S[l].push_back({i,1});
        S[r+1].push_back({i,-1});
    }
    set<int> days;
    FOR_(i,1,n) {
        for (auto p:S[i]) {
            if (p.second==1) days.insert(p.first);
            else days.erase(p.first);
        }
        if (days.size()<=2) {
            vector<int> cur;
            for (int v:days) cur.push_back(v);
            if (days.size()==0) zero++;
            if (days.size()==1) Cnt[cur[0]]++;
            if (days.size()==2) MP[cur[0]][cur[1]]++,MP[cur[1]][cur[0]]++;
        }
    }
    int ans=0;
    FOR_(i,1,m) {
        for (auto p:MP[i]) {
            // printf("%d %d: %d+%d+%d+%d=%d\n",i,p.first,p.second,Cnt[i],zero,Cnt[p.first],Cnt[p.first]+p.second+Cnt[i]+zero);
            ans=max(ans,p.second+Cnt[i]+Cnt[p.first]+zero);
        }
    }
    sort(Cnt.begin()+1,Cnt.begin()+m+1);
    ans=max(ans,zero+Cnt[m]+Cnt[m-1]);
    printf("%d\n",ans);
}
int main() {
    int T = 1;
    scanf("%d",&T);
    FOR_(_, 1, T) solve(_);
}
/*
 */