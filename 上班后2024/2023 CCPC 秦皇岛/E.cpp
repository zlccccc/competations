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
template <typename T> inline void pr2(T x, int k = 64) { REP_(i, k) debug("%d", (x >> i) & 1); putchar(' '); }
template <typename T> inline void max_(T &A, T B) { (A < B) && (A = B); }
template <typename T> inline void min_(T &A, T B) { (A > B) && (A = B); }
inline ll fastgcd(ll a, ll b) { // __gcd()
    if (!a)
        return b;
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
typedef array<int, 4> ar4;
typedef array<int, 3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
vector<pii> direction8 = {{-1, -1}, {-1, 0}, {1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

// const int mod = 1e9+7;
const int mod=998244353;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this; }
    mint operator-() const { return mint(0) - *this; }
    mint operator~() const { return mint(1) / *this; }
    mint &operator+=(const mint &a) { if ((x+=a.x)>=mod) x-=mod; return *this; }
    mint &operator-=(const mint &a) { if ((x+=mod-a.x)>=mod) x-=mod; return *this; }
    mint &operator*=(const mint &a) { (x*=a.x)%=mod; return *this; }
    mint &operator/=(const mint &a) { (x*=a.pow(mod-2).x)%=mod; return *this; }
    mint operator+(const mint &a)const { return mint(*this) += a; }
    mint operator-(const mint &a)const { return mint(*this) -= a; }
    mint operator*(const mint &a)const { return mint(*this) *= a; }
    mint operator/(const mint &a)const { return mint(*this) /= a; }
    mint pow(long long t) const {
        mint ret=1,cur=x;
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x; }
    bool operator==(const mint &a)const { return x == a.x; }
};
istream & operator>>(istream &o,mint &a) { o>>a.x; a=a.fix(); return o; }
ostream & operator<<(ostream &o,const mint &a) { o<<a.x; return o; }

int solve() {
    int n,m,r;
    scanf("%d%d%d",&n,&m,&r);
    vector<vector<ar3>> limits(m+1);
    vector<vector<pii>> connects(1<<(n-1));
    // vec: 前面status是k,对应的后面status是?
    auto at=[](int sta,int i) { return (sta>>i)&1; };
    int cnum=0;
    REP_(sta,1<<(n-1)) {
        vector<pii> cur;
        function<void(int,int,int)> dfs=[&](int i,int src,int dst) {
            if (i>=n) {
                // printf("dfs %d sta=%d: %d %d\n",i,sta,src,dst);
                cur.push_back({src,dst});
                return;
            }
            int k=i;
            while (k<n&&at(sta,i)==at(sta,k)) k++; k--;
            dfs(k+1,src^(1<<i),dst^(1<<k));
            if (i!=k) dfs(k+1,src^(1<<k),dst^(1<<i));
        };
        dfs(0,0,0);
        connects[sta].swap(cur);
        cnum+=connects[sta].size();
    }
    // printf("cnum=%d\n",cnum);
    FOR_(i,1,r) {
        int c,x,y,diff;
        scanf("%d%d%d%d",&c,&x,&y,&diff);
        limits[c].push_back({x,y,diff});
    }
    vector<mint> cur(1<<n);  // count
    cur[(1<<n)-1]=1;
    FOR_(i,1,m) {
        // subset-sum
        vector<mint> nxt(1<<n);  // count
        REP_(sta,1<<(n-1)) {
            bool okay=true;
            for (auto [x,y,diff]:limits[i]) {
                // check if in the same
                x--; y--;
                if (x>y) swap(x,y);
                int rx=x;
                while (rx<n&&at(sta,x)==at(sta,rx)) rx++; rx--;
                int dif=(y>rx);
                // printf("sta=%d; x,y=%d %d; rx=%d; dif=%d\n",sta,x,y,rx,dif);
                if (dif!=diff) {okay=false; break;}
            }
            if (okay) {
                // printf("i=%d: solve sta=%d\n",i,sta);
                for (auto &[src,dst]:connects[sta]){
                    // printf("%d: %d %d\n",i,src,dst);
                    nxt[dst]+=cur[src];
                }
            }
        }
        cur.swap(nxt);
        REP_(k,n) REP_(sta,1<<n) if (at(sta,k)) cur[sta^(1<<k)]+=cur[sta];
        // REP_(sta,1<<n) printf("%d ",cur[sta].x); puts("<- cur");
    }
    // mint res=0;
    // for (auto val:cur) res+=val;
    mint res=cur[0];
    printf("%lld\n",res.x);
    return 0;
}
int main() {
    int T;
    T = 1;
    // cin>>T;
    // scanf("%d", &T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
 */