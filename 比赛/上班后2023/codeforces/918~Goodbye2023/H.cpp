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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=3e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline void pr2(T x,int k=64) {REP_(i,k) printf("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
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

// const int mod = 1e9+7;
const int mod=998244353;
// int mod=1;
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
        for (; t; t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};
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

inline ll powMM(ll a, ll b, ll mod) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}

namespace BruteForce {
    vector<int> mul(const vector<int> &A,const vector<int> &B,int mod)  { //C=A*B
        int n=A.size(),m=B.size();
        if (!n||!m) return vector<int>();
        vector<int> C(n+m-1,0);
        REP_(i,n) REP_(j,m) add_(C[i+j],(ll)A[i]*B[j]%mod,mod);
        return C;
    }
}

// FOR NTT
namespace NTT {
    static const int MOD=998244353;
    static const int g=3;
    static const int bruteforce_limit=16;
    vector<int> roots{0,1};
    inline int mul(int x,int y) {
        ll ret=(ll)x*y; (ret>MOD) &&(ret%=MOD);
        return ret;
    }
    int poww(int a,int b) {
        int ret=1;
        for (; b; b>>=1,a=mul(a,a))
            if (b&1) ret=mul(ret,a);
        return ret;
    }
    void dft(vector<int> &A,int len,int inv) {
        assert((int)A.size()==len);
        if (inv==-1) reverse(A.begin()+1, A.end());
        int i,j,k;
        // bitrev[i] = bitrev[i >> 1] >> 1 | (i & 1) << __builtin_ctz(len);
        for (i=1,j=len/2; i<len-1; i++) {
            if (i<j) swap(A[i],A[j]);
            k=len/2;
            while (j>=k) j-=k,k/=2;
            if (j<k) j+=k;
        }
        if ((int)roots.size()<len) {
            int k=__builtin_ctz(roots.size());
            roots.resize(len);
            while ((1<<k)<len) {
                int e=poww(g,(MOD-1)>>(k+1));
                for (int i=1<<(k-1); i<(1<<k); ++i) {
                    roots[2*i]=roots[i];
                    roots[2*i+1]=mul(roots[i],e);
                } ++k;
            }
        }
        for (i=1; i<len; i<<=1) { //fin version
            for (j=0; j<len; j+=i+i) { //merge length = i+i
                for (k=0; k<i; k++) {
                    int a=A[k+j];
                    // assert(k+i+j<(int)A.size());
                    // assert(k+i<(int)roots.size());
                    int b=mul(A[k+i+j],roots[k+i]);
                    int u=a+b; (u>=MOD) &&(u-=MOD); A[k+j]=u;
                    int v=a-b; (v<0) &&(v+=MOD); A[k+i+j]=v;
                }
            }
        }
        if (inv==-1) {
            int vn=poww(len,MOD-2);
            REP_(i,len) A[i]=mul(A[i],vn);
        }
    }
    vector<int> mul(const vector<int> &A,const vector<int> &B) { //C=A*B
        int n=A.size(),m=B.size();
        if (min(n,m)<=bruteforce_limit)
            return BruteForce::mul(A,B,MOD);
        int len=1;
        while (len<n+m-1) len<<=1;
        vector<int> _A(A),_B;
        _A.resize(len,0); dft(_A,len,1);
        if (A==B) _B=_A; else _B=B,_B.resize(len,0),dft(_B,len,1);
        REP_(i,len) _A[i]=mul(_A[i],_B[i]);
        dft(_A,len,-1); _A.resize(n+m-1);
        return _A;
    }
}

void solve() {
    ll n;
    int p,k;
    scanf("%lld%d%d",&n,&p,&k);
    vector<mint> base(k+1);
    vector<mint> inv(k+1);
    FOR_(i,0,k) inv[i]=mint(1)/i;
    base[0]=1;
    FOR_(x,0,min(n,(ll)k)-1) base[x+1]=base[x]*(mint(p).pow(n-x)-1);

    vector<int> multi(2,1);
    vector<int> f(k+1);
    f[0]=1;
    for (ll o=1;o<=n;o<<=1) {
        auto solve=[&](vector<int> A,vector<int> B,ll base) {
            ll mul=1;
            for (int &cur:A) cur=cur*mul%mod,mul=mul*base%mod;
            auto cur=NTT::mul(A,B);
            // for (int v:A) printf("%d ",v); puts("<- left");
            // for (int v:B) printf("%d ",v); puts("<- right");
            return cur;
        };
        if (n&o) f=solve(f,multi,mint(p).pow(o).x);
        multi=solve(multi,multi,mint(p).pow(o).x);
        f.resize(k+1); multi.resize(k+1);
    }
    // FOR_(i,1,n) {
    //     vector<mint> g(k+1);
    //     FOR_(x,0,k) f[x]=f[x]*mint(p).pow(x);
    //     FOR_(x,0,k) g[x+1]+=f[x],g[x]+=f[x];
    //     f.swap(g);
    // }
    // FOR_(i,0,k) printf("%d ",f[i]); puts("");

    FOR_(i,0,k) f[i]=(base[i]*f[i]).x;
    FOR_(i,0,k) printf("%d ",f[i]);
}
int main() {
    // init();
    int T; T=1;
    // cin>>T;
    // scanf("%d",&T);
    FOR_(_,1,T){
        solve();
    }
}
/*
3 2 3

*/