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

struct Node {
    int val,l,r;
}T[maxn*32];
int tot;
void merge_(int &x,int y,int l,int r,int val,int L,int R) {  // val: to-pushdown
    if (l<=L&&R<=r) {
        T[++tot]=T[y]; x=tot; T[x].val+=val;
        return;
    }
    T[++tot]=T[x]; x=tot;
    int mid=(L+R)/2;
    if (l<=mid) merge_(T[x].l,T[y].l,l,r,val+T[y].val,L,mid);
    if (mid<r) merge_(T[x].r,T[y].r,l,r,val+T[y].val,mid+1,R);
}
// void update(int &x,int l,int r,int L,int R) {
//     if (!x) x=++tot,T[x]=T[0];
//     if (l<=L&&R<=r) {
//         T[x].val++;
//         return;
//     }
//     T[++tot]=T[x]; x=tot;
//     int mid=(L+R)/2;
//     if (l<=mid) update(T[x].l,l,r,L,mid);
//     if (mid<r) update(T[x].r,l,r,mid+1,R);
// }
int ask(int x,int pos,int L,int R) {
    if (!x) return 0;
    if (L==R) return T[x].val;
    int mid=(L+R)/2;
    if (pos<=mid) return T[x].val+ask(T[x].l,pos,L,mid);
    if (mid<pos) return T[x].val+ask(T[x].r,pos,mid+1,R);
}
int A[maxn],id[maxn],root[maxn];
int R[maxn];
int main() {
    int n,q;
    scanf("%d%d",&n,&q);
    FOR_(i,1,n) scanf("%d",&A[i]);
    rFOR_(i,1,n) {
        if (id[A[i]]) {
            root[i]=root[id[A[i]]+1];
            merge_(root[i],root[i+1],i,id[A[i]]-1,1,1,n);
        } else {
            merge_(root[i],root[i+1],i,n,1,1,n);
        }
        id[A[i]]=i;
    }
    int lastans=0;
    FOR_(_,1,q) {
        int l,r;
        scanf("%d%d",&l,&r);
        l^=lastans; r^=lastans;
        int cur=ask(root[l],r,1,n);
        // printf("ask %d %d: cur=%d\n",l,r,cur);
        printf("%d\n",lastans=cur);
    }
}
/*
 */