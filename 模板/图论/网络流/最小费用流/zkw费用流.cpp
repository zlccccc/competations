// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I, N) for (int I = 0, END = (N); I < END; I++)
#define rREP_(I, N) for (int I = (N)-1; I >= 0; I--)
#define rep_(I, S, N) for (int I = (S), END = (N); I < END; I++)
#define rrep_(I, S, N) for (int I = (N)-1, START = (S); I >= START; I--)
#define FOR_(I, S, N) for (int I = (S), END = (N); I <= END; I++)
#define rFOR_(I, S, N) for (int I = (N), START = (S); I >= START; I--)

#define DEBUG
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
const LL maxn = 1e6 + 7;
const double pi = acos(-1.0);
const double eps = 1e-10;
template <typename T> inline void pr2(T x, int k = 64) {
    REP_(i, k) printf("%d", (x >> i) & 1);
    putchar(' ');
}
template <typename T> inline void max_(T &A, T B) { (A < B) && (A = B); }
template <typename T> inline void min_(T &A, T B) { (A > B) && (A = B); }
inline ll fastgcd(ll a, ll b) { // __gcd()
    if (!b)
        return a;
    ll az = __builtin_ctzll(a), bz = __builtin_ctzll(b), z = min(az, bz), diff;
    b >>= bz;
    while (a) {
        a >>= az, diff = b - a, az = __builtin_ctzll(diff);
        (b > a) && (b = a), a = abs(diff);
    }
    return b << z;
}
int startTime;
void startTimer() { startTime = clock(); }
void printTimer() { debug("/--- Time: %ld milliseconds ---/\n", clock() - startTime); }
typedef array<int, 5> ar5;
typedef array<int, 4> ar4;
typedef array<int, 3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
vector<pii> direction8 = {{-1, -1}, {-1, 0}, {1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

// const int mod = 1e9+7;
const int mod = 998244353;
struct mint {
    long long x;
    mint() : x(0) {}
    mint(long long x) : x((x % mod + mod) % mod) {}
    // mint(long long x):x(x){}
    mint &fix() {
        x = (x % mod + mod) % mod;
        return *this;
    }
    mint operator-() const { return mint(0) - *this; }
    mint operator~() const { return mint(1) / *this; }
    mint &operator+=(const mint &a) {
        if ((x += a.x) >= mod)
            x -= mod;
        return *this;
    }
    mint &operator-=(const mint &a) {
        if ((x += mod - a.x) >= mod)
            x -= mod;
        return *this;
    }
    mint &operator*=(const mint &a) {
        (x *= a.x) %= mod;
        return *this;
    }
    mint &operator/=(const mint &a) {
        (x *= a.pow(mod - 2).x) %= mod;
        return *this;
    }
    mint operator+(const mint &a) const { return mint(*this) += a; }
    mint operator-(const mint &a) const { return mint(*this) -= a; }
    mint operator*(const mint &a) const { return mint(*this) *= a; }
    mint operator/(const mint &a) const { return mint(*this) /= a; }
    mint pow(long long t) const {
        mint ret = 1, cur = x;
        for (; t; t >>= 1ll, cur = cur * cur)
            if (t & 1)
                ret = ret * cur;
        return ret;
    }
    bool operator<(const mint &a) const { return x < a.x; }
    bool operator==(const mint &a) const { return x == a.x; }
};
istream &operator>>(istream &o, mint &a) {
    o >> a.x;
    a = a.fix();
    return o;
}
ostream &operator<<(ostream &o, const mint &a) {
    o << a.x;
    return o;
}

struct comb {
    vector<mint> f, g; // f:fac; g:inv
    comb() {}
    comb(int mx) : f(mx + 1), g(mx + 1) {
        f[0] = 1;
        FOR_(i, 1, mx) f[i] = f[i - 1] * i;
        g[mx] = f[mx].pow(mod - 2);
        rFOR_(i, 1, mx) g[i - 1] = g[i] * i;
    }
    mint operator()(int a, int b) {
        if (b < 0 || a < b)
            return 0;
        return f[a] * g[b] * g[a - b];
    }
} Comb(maxn); // Combination(x,y)

// Arrange(x,y)
mint Arra(int a, int b) { return Comb.f[a] * Comb.g[a - b]; }
// the number of way from (0, 0) to (w, h) which dosn't exceed line y = x + bound (y-x<=bound)
mint Catalan(int w, int h, int bound) { return Comb(w + h, h) - Comb(w + h, h - bound - 1); }

// 这个好像就是zkw费用流

// 拆点后可以S向入连边, 出向T连边, 然后入和出就可以保持动态平衡!
// 连边是为了将"获取的"和"使用的"联系起来! 大概意思就是, 使用的流量确定...
// 注意观察特殊性质

// https://ac.nowcoder.com/acm/problem/13820
// 题意: 给一个数组A
// 连续k个数字中最少选a个最多选b个; 每个数字只能选一次; 问你res最大多少
// 就连边网络流就好了
struct MinCostFlow {
    typedef ll type;
    struct node {
        int to, next;
        type cap, cost;
        node(int t = 0, type c = 0, type _c = 0, int n = 0) : to(t), cap(c), cost(_c), next(n){};
    };
    vector<node> edge;
    MinCostFlow(int n = 0) { init(n); }
    vector<int> head, cur; // cur:当前弧优化
    int addedge(int from, int to, type cap, type cost, type rcap = 0) {
        edge.push_back(node(to, cap, cost, head[from])), head[from] = edge.size() - 1;
        edge.push_back(node(from, rcap, -cost, head[to])), head[to] = edge.size() - 1;
        return edge.size() - 2;
    }
    vector<type> dis;
    vector<bool> mark;
    bool spfa(int s, int t) {
        dis.resize(head.size());
        fill(dis.begin(), dis.end(), 0x3f3f3f3f3f3f3f3fll);
        mark.resize(head.size());
        fill(mark.begin(), mark.end(), false);
        deque<int> Q;
        Q.push_back(s);
        dis[s] = 0;
        while (Q.size()) {
            int v = Q.front();
            mark[v] = 0;
            Q.pop_front();
            for (int i = head[v]; ~i; i = edge[i].next) {
                node &e = edge[i];
                if (e.cap > 0 && dis[e.to] > dis[v] + e.cost) {
                    dis[e.to] = dis[v] + e.cost;
                    if (!mark[e.to]) {
                        if (!Q.size() || dis[Q.front()] <= dis[e.to])
                            Q.push_back(e.to), mark[e.to] = 1;
                        else
                            Q.push_front(e.to), mark[e.to] = 1;
                    }
                }
            }
        }
        if (dis[t] == 0x3f3f3f3f3f3f3f3fll)
            return false;
        return true;
    }
    type dfs(int x, int t, type flow) {
        if (x == t || !flow)
            return flow;
        type ret = 0;
        mark[x] = 1;
        for (int i = cur[x]; ~i; i = edge[i].next) {
            if (!mark[edge[i].to]) {
                if (dis[x] + edge[i].cost == dis[edge[i].to] && edge[i].cap) {
                    int f = dfs(edge[i].to, t, min(flow, edge[i].cap));
                    edge[i].cap -= f, edge[i ^ 1].cap += f;
                    ret += f, flow -= f, cur[x] = i;
                    if (flow == 0)
                        break;
                }
            }
        }
        mark[x] = 0;
        return ret;
    }
    pair<type, type> mincostflow(int s, int t, type flow = 0x3f3f3f3f3f3f3f3fll) {
        type ret = 0, ans = 0;
        while (flow) {
            if (!spfa(s, t))
                break;
            cur = head; // 这样加当前弧优化会快, 我也不知道为啥
            type len = dis[t], f;
            while ((f = dfs(s, t, flow)) > 0) // while也行
                ret += f, ans += len * f, flow -= f;
        }
        return make_pair(ret, ans);
    }
    void init(int n) {
        head.resize(n + 1);
        fill(head.begin(), head.end(), -1);
    }
};

int solve() {
    int n, k, a, b;
    scanf("%d%d%d%d", &n, &k, &a, &b);
    vector<int> A(n + 1);
    FOR_(i, 1, n) scanf("%d", &A[i]);
    MinCostFlow flow(n + 2);
    int s = n + 1, t = n + 2;
    // a<=f[1]+...+f[k]<=b
    flow.addedge(s, 0, b, 0); // 新增节点0; 避免负环
    // a<=f[n-k+1]+...+f[n]<=b
    flow.addedge(n - k + 1, t, b, 0);
    // a<=f[x]+...+f[x+k-1]<=b
    // a<=f[x+1]+...+f[x+k]<=b  // 等价于f[x]向f[x+k]连一条边; 代表选了A[x+k]
    FOR_(i, 1, n) {
        flow.addedge(max(0, i - k), min(i, n - k + 1), 1, -A[i]); // choose A[i]
        // A[i-1]->A[i]: a~b
        if (i <= n - k + 1)
            flow.addedge(i - 1, i, b - a, 0);
    }
    auto res = flow.mincostflow(s, t, b);
    // printf("%lld\n",res.first);
    printf("%lld\n", -res.second);
    return 0;
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    scanf("%d", &T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
2
5 2 1 2
1 -2 -2 -1 3
*/