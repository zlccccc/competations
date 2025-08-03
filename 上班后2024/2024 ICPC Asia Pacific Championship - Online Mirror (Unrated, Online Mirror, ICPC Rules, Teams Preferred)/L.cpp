// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I, N) for (auto I = 0, END = (N); I < END; I++)
#define rREP_(I, N) for (auto I = (N)-1; I >= 0; I--)
#define rep_(I, S, N) for (auto I = (S), END = (N); I < END; I++)
#define rrep_(I, S, N) for (auto I = (N)-1, START = (S); I >= START; I--)
#define FOR_(I, S, N) for (auto I = (S), END = (N); I <= END; I++)
#define rFOR_(I, S, N) for (auto I = (N), START = (S); I >= START; I--)

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

struct comb {
    vector<mint> f, g; // f:fac; g:inv
    comb() {}
    comb(int mx):f(mx+1),g(mx+1) {
        f[0] = 1;
        FOR_(i,1,mx) f[i] = f[i-1]*i;
        g[mx] = f[mx].pow(mod-2);
        rFOR_(i,1,mx) g[i-1] = g[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return f[a]*g[b]*g[a-b];
    }
} C(maxn);

namespace LB {
    typedef int BaseType;
    const int MaxBit=32;
    struct L_B {
        BaseType b[MaxBit]; bool have_0;
        L_B() {clear();}
        void clear() {memset(b,0,sizeof(b)); have_0=0;}
        BaseType XORMIN(BaseType x) {
            int i;
            rREP_(i,MaxBit) if ((b[i]^x)<x) x^=b[i];
            return x;
        }
        BaseType XORMAX(BaseType x) {
            int i;
            rREP_(i,MaxBit) if ((b[i]^x)>x) x^=b[i];
            return x;
        }
        bool insert(BaseType x) {
            int operation=0;
            if (!have_0&&!XORMIN(x)) have_0=1;
            rREP_(i,MaxBit) if ((x>>i)&1) {
                if (!b[i]) {
                    b[i]=x;
                    return true;
                }
                x^=b[i]; operation^=1<<i;
            }
            // return operation;
            return false;
        }
        void rebuild() {
            int i,j;
            rREP_(i,MaxBit) rREP_(j,i) if ((b[i]>>j)&1) b[i]^=b[j];
        }
        BaseType querykth(BaseType k) {
            BaseType ret=0; int i; k-=have_0;
            REP_(i,MaxBit) if (b[i]) {if (k&1) ret^=b[i]; k>>=1;}
            if (k) return -1;
            return ret;
        }
    };
}
using namespace LB;

int A[maxn];
L_B items[maxn][2];
int main() {
    int n;
    scanf("%d",&n);
    vector<int> A(n);
    FOR_(i,1,n) {
        scanf("%d",&A[i]);
        A[i]|=1<<30;
    }
    vector<int> base,remain;
    {
        L_B cur;
        FOR_(i,1,n) {  // x^a
            if (cur.insert(A[i])!=0) base.push_back(A[i]);
            else remain.push_back(A[i]);
        }
        // for (int v:remain) all^=cur.insert(v);
    }
    if (base.size()==1) return 0*puts("1");
    mint res=mint(2).pow(base.size()*(base.size()-1)/2+(base.size()-1)*remain.size());
    printf("%lld\n",res.x);
}
/*
 */