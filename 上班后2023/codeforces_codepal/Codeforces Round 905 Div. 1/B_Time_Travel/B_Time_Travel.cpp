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
const LL maxn = 2e5 + 107;
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

vector<int> alledge[maxn];
struct node{
    int l,r,val;
}T[maxn*32];
int tot=0;
void update(int &x,int pos,int val,int L,int R) {
    T[++tot]=T[x]; x=tot;
    // T[tot].l=T[tot].r=T[x].val=0;
    if (L==R) {T[x].val=val; return;}
    int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,pos,val,L,mid);
    if (mid<pos) update(T[x].r,pos,val,mid+1,R);
}
int query(int x,int pos,int L,int R) {
    if (!x) return 0;
    if (L==R) return T[x].val;
    int mid=(L+R)/2;
    if (pos<=mid) return query(T[x].l,pos,L,mid);
    if (mid<pos) return query(T[x].r,pos,mid+1,R);
}
int root[maxn];
vector<pii> edge[maxn]; // edges
int A[maxn];
int dis[maxn];
set<int> ids[maxn];
void solve(int _) {
    int n,t;
    scanf("%d%d",&n,&t);
    FOR_(i,1,n) edge[i].clear();
    
    FOR_(o,1,t) {
        int m;
        scanf("%d",&m);
        FOR_(i,1,m) {
            int x,y;
            scanf("%d%d",&x,&y);
            edge[x].push_back(make_pair(y,o));
            edge[y].push_back(make_pair(x,o));
        }
    }
    int k;
    scanf("%d",&k);
    FOR_(i,1,k) scanf("%d",&A[i]);
    tot=0; root[t+1]=0;
    rFOR_(i,1,k) {
        root[i]=root[i+1];
        update(root[i],A[i],i,1,t);
    }
    FOR_(i,1,k) ids[i].clear();
    FOR_(i,1,n) dis[i]=INF;
    dis[1]=1; ids[1].insert(1);
    // FOR_(i,1,k) printf("%d ",root[i]); puts("<- root");
    for (int cur=1;cur<=k;cur++) {
        for (int x:ids[cur]) if (dis[x]==cur) {
            // printf("dfs cur=%d; x=%d\n",cur,x);
            for (auto p:edge[x]) {
                int y=p.first,o=p.second;
                int nxt=query(root[cur],o,1,t);
                // printf("y=%d; o=%d; nxt=%d\n",y,o,nxt);
                if (nxt==0) continue;
                nxt++;
                ids[nxt].insert(y);
                dis[y]=min(dis[y],nxt);
            }
        }
    }
    if (dis[n]==INF) puts("-1");
    else printf("%d\n",dis[n]-1);
}
int main() {
    int T = 1;
    // scanf("%d",&T);
    FOR_(_, 1, T) solve(_);
}
/*
 */