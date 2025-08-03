// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (int I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (int I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (int I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (int I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (int I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (int I=(N),START=(S);I>=START;I--)

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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=1e-10;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
inline ll fastgcd(ll a, ll b) {  // __gcd()
    if (!b) return a;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az, diff=b-a, az=__builtin_ctzll(diff);
        (b>a)&&(b=a), a=abs(diff);
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
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

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
    comb(int mx) : f(mx + 1), g(mx + 1) {
        f[0] = 1;
        FOR_(i, 1, mx) f[i] = f[i - 1] * i;
        g[mx] = f[mx].pow(mod - 2);
        rFOR_(i, 1, mx) g[i - 1] = g[i] * i;
    }
    mint operator()(int a, int b) {
        if (a < b)
            return 0;
        return f[a] * g[b] * g[a - b];
    }
} Combination(maxn);  // C(x,y)
mint Arrange(int a,int b) { // A(x,y)
    return Combination.f[a]*Combination.g[a - b];
}

template <class T> struct fenwick {
    int n;
    vector<T> t;
    fenwick(int _n = -1) : n(_n), t(n + 1) {}
    void add(int i, T a) {
        for (i; i <= n; i += i & -i) // ++i了...
            t[i] += a;
    }
    T sum(int i) const {
        T s = 0;
        for (; i; i -= i & -i)
            s += t[i];
        return s;
    }
    T sum(int l, int r) const { return sum(r) - sum(l-1); }
};
int val[maxn];
mint self[maxn],res[maxn];
mint low[maxn];
int solve() {
    int n,k;
    scanf("%d%d",&n,&k);
    FOR_(i,1,k) scanf("%d",&val[i]);
    bool have;
    mint all=0;
    {
        fenwick<mint> bit(n),notexist(n);
        vector<int> vis(n+1);
        FOR_(i,1,k) {
            int x=val[i];
            bit.add(x,1);
            mint lower=mint(x)-bit.sum(1,x);
            low[i]=lower;
            self[i]=lower*Arrange(n-i,k-i);
            // printf("lower=%lld; self=%lld; res-x=%lld\n",lower.x,self[i].x,res[x].x);
            // 前边没出现过x; x比其他都要小的方案
            res[x]+=notexist.sum(x,n);
            notexist.add(x,Arrange(n-i,k-i)); vis[x]=1;
            // res[x]+=1;  // 全部相同
        }
        // FOR_(i,1,n) printf("%d ",vis[i]); puts("<- vis");
        FOR_(i,1,n) if (!vis[i]) res[i]+=notexist.sum(i,n);  // less
    }
    // FOR_(i,1,n) printf("%lld ",res[i].x); puts("<- sub result");
    // FOR_(i,1,k) printf("%lld ",self[i].x); puts("<- self");
    {
        fenwick<mint> lessChoose(n),moreChoose(n);
        // fenwick<mint> less(n),more(n);
        vector<bool> vis(n+1);
        mint all=0,nxtself=0;
        FOR_(i,1,k) {
            int x=val[i];
            mint lower=low[i];
            if (i!=k&&lower.x) {
                mint larger=lower*Arrange(n-i-1,k-i-1);  // 后面随便选的时候的方案数量
                mint largerChoose=larger*Arrange(k-i,1);
                mint smaller=(lower-1)*Arrange(n-i-1,k-i-1);  // 底下不能选i
                mint smallerChoose=smaller*Arrange(k-i,1);
                // less.add(x,smaller);
                // more.add(x,larger);
                lessChoose.add(x,smallerChoose);
                moreChoose.add(x,largerChoose);
                // printf("%d:%d; %lld %lld  <- choose right no idx\n",i,x,smaller.x,larger.x);
                // printf("%d:%d; %lld %lld  <- choose right\n",i,x,smallerChoose.x,largerChoose.x);
            }
            res[x]+=lessChoose.sum(x+1,n)+moreChoose.sum(1,x);
            vis[x]=1;
        }
        FOR_(i,1,n) if (!vis[i]) res[i]+=lessChoose.sum(i+1,n)+moreChoose.sum(1,i);
        // FOR_(i,1,n) printf("%lld ",res[i]); puts("<- nxt-value");
    }
    // FOR_(i,1,k) printf("%lld ",larger[i].x); puts("<- after-large");
    // FOR_(i,1,k) printf("%lld ",smaller[i].x); puts("<- after-smaller");
    {  // 选择x
        mint nxtself=1;
        rFOR_(i,1,k) {
            int x=val[i];
            res[x]+=nxtself;
            nxtself+=self[i];
        }
    }
    FOR_(i,1,n) printf("%lld\n",res[i]);
    return 0;
}
int main() {
    // FOR_(i,1,1000000) {
    //     int y=sqrt(i);
    //     bool same=false;
    //     for (int k=i;k;k/=10) if (k==y) same=1;
    //     if (same) printf("%d %d\n",i,(int)sqrt(i));
    // }
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
4 3
3 2 4
*/