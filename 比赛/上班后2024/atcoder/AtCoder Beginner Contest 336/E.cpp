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
    if (!a) return b;
    ll az=__builtin_ctzll(a),bz=__builtin_ctzll(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctzll(diff);
        (b>a)&&(b=a); a=abs(diff);
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

typedef long long DPTYPE;

const int MLEN=18; // max-length
bool vis[MLEN][140][140][140][2];
DPTYPE f[MLEN][140][140][140][2];
int lval[MLEN],rval[MLEN];
DPTYPE pw10[MLEN]; // 位
DPTYPE calc(int x,int k,int val,int mod,int not_0,int l_limit,int r_limit) { // k: 奇数位数
    // printf("calc %d k=%d %d %d; %d %d %d\n",x,k,val,mod,not_0,l_limit,r_limit);
    if (x==-1) return (k==mod&&val==0); // cnt,sum
    if (!l_limit&&!r_limit&&vis[x][k][val][mod][not_0]) return f[x][k][val][mod][not_0];
    DPTYPE ret=0;
    int l=0,r=9;
    if (l_limit) l=max(l,lval[x]);
    if (r_limit) r=min(r,rval[x]);
    FOR_(i,l,r) {
        int nxtk=k+i,nxtval=val;
        if (not_0||i) {
            nxtval=(val+pw10[x]*i)%mod;
        }
        DPTYPE cur=calc(x-1,nxtk,nxtval,mod,not_0||i,l_limit&&(i==l),r_limit&&(i==r));
        ret+=cur;
    }
    // printf("x=%d; bit=%d; not0=%d; l_limit=%d; r_limit=%d; ret=%lld %lld\n",x,bit,not_0,l_limit,r_limit,ret.first.x,ret.second.x);
    if (!l_limit&&!r_limit) f[x][k][val][mod][not_0]=ret,vis[x][k][val][mod][not_0]=1;
    return ret;
}
DPTYPE calc(long long l,long long r) {
    pw10[0]=1;
    rep_(i,1,MLEN) pw10[i]=pw10[i-1]*10;
    REP_(i,MLEN) lval[i]=l%10,l/=10;
    REP_(i,MLEN) rval[i]=r%10,r/=10;
    ll res=0;
    FOR_(mod,1,140) res+=calc(MLEN-1,0,0,mod,0,1,1);
    return res;
}

int digsum(int x) {
    if (!x) return x;
    return digsum(x/10)+x%10;
}
int solve() {
    ll n;
    cin>>n;
    // int c=0;
    // FOR_(i,1,n) if (calc(1,i)) printf("%d(%d) ",i,i%(digsum(i))),c++; puts("<- val");
    // cout<<c<<"\n";
    ll res=calc(1,n);
    cout<<res;
    return 0;
}
int main() {
    int T; T=1;
    // cin>>T;
    startTimer();
    FOR_(_,1,T) {
        solve();
    }
    // printTimer();
}
/*
*/