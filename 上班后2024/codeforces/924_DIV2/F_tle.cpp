// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
#include <functional>
#include <random>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)

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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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
        for (;t;t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};
// struct comb {
//     vector<mint> f, g; // f:fac; g:inv
//     comb() {}
//     comb(int mx):f(mx+1),g(mx+1) {
//         f[0] = 1;(
//         rREP_(i,mx) f[i] = f[i-1]*i;
//         g[mx] = f[mx].pow(mod-2);
//         for (int i=mx; i>0; i--) g[i-1] = g[i]*i;
//     }
//     mint operator()(int a, int b) {
//         if (a < b) return 0;
//         return f[a]*g[b]*g[a-b];
//     }
// } C(maxn);

struct BIT {
    ll fx[maxn],f2[maxn],f1[maxn],f0[maxn];
    ll allx,all2; // sum of 0->b
    BIT() {
        allx=all2=0;
        memset(f0,0,sizeof(f0));
        memset(f1,0,sizeof(f1));
        memset(f2,0,sizeof(f2));
        memset(fx,0,sizeof(fx));
    }
    inline int lowbit(int x) {return x&-x;}
    void update(ll p,int op) {
        // a是未知数:
        // a<=b: \sum{k=0->a}(a-k)(b-k)=a*(a+1)/2*b - a*a*(a+1)/2 + a*(a+1)*(2a+1)/2; 
        // a>b: \sum{k=0->b}(a-k)(b-k)=a*b*(b+1)/2 - b*b*(b+1)/2 + b*(b+1)*(2b+1)/2;
        ll a0=0,a1=0,a2=0,ax=0;
        a0+=p*(p+1)*(2*p+1)/6-p*p*(p+1)/2; a1+=p*(p+1)/2;  // a<=b
        a2-=p; ax-=1;  // a>b

        all2+=p*op; allx+=1*op;
        for (int x=p;x<maxn;x+=lowbit(x)) {
            fx[x]+=ax*op; // count of a
            f2[x]+=a2*op; // p*(p+1)/2
            f1[x]+=a1*op; // p
            f0[x]+=a0*op; // +val
        }
    }
    ll ask(ll p) {
        ll sx=0,s2=0,s1=0,s0=0;
        for (int x=p;x;x-=lowbit(x)) {
            s1+=f1[x],s0+=f0[x];
            sx+=fx[x],s2+=f2[x];
        }
        ll flow=(allx+sx)*(p*(p+1)*(2*p+1)/6-p*p*(p+1)/2)+(all2+s2)*p*(p+1)/2;
        ll fhigh=s1*p+s0;
        // printf("low & high = %lld %lld; x=%lld; 2=%lld\n",flow,fhigh,allx+sx,all2+s2);
        return flow+fhigh;
    }
}bit[2];

ll A[2][maxn];
int solve() {
    set<pii> S[2];
    int n[2],q;
    // f[i]!=f[i-1]的位置有哪些
    scanf("%d%d%d",&n[0],&n[1],&q);
    ll res=0;
    // (a<b)的Cnt个数: a*b+(a-1)*(b-1)+...+1*(a-b) = 
    auto update_length=[&](int l,int r,int op,int o) {  // x->y += q
        // a<b: \sum{k=0->a}(a-k)(b-k)
        int x=r-l+1;
        if (x==0) return;
        if (op==1) S[o].insert({l,r});
        if (op==-1) S[o].erase({l,r});
        res+=op*bit[o^1].ask(x);
        bit[o].update(x,op);
        // printf("update %d->%d length %d %d; dir=%d\n",l,r,x,op,o);
        // for (auto &p:S[o]) printf("(%d %d) ",p.first,p.second);
        // puts(" <");
    };
    REP_(o,2) FOR_(i,1,n[o]) update_length(i,i,1,o);
    auto update_value=[&](int pos,int val,int o) {
        // s[l]+=val; s[r]-=val;
        // printf("value %d %d %d; init=%lld\n",pos,val,o,A[o][pos]);
        if (!val) return;
        if (pos==n[o]+1||pos==1) return;
        if (A[o][pos]!=0&&A[o][pos]+val==0) {  // split
            auto it=S[o].upper_bound(make_pair(pos,INF)); it--;
            int l=it->first,i=pos,r=it->second;
            update_length(l,r,-1,o);
            update_length(l,i-1,1,o);
            update_length(i,r,1,o);
        }
        if (A[o][pos]==0&&A[o][pos]+val!=0) {  // merge
            auto it=S[o].upper_bound(make_pair(pos,INF)); it--;
            int i=it->first,r=it->second; it--;
            auto l=it->first;
            update_length(l,i-1,-1,o);
            update_length(i,r,-1,o);
            update_length(l,r,1,o);
        }
        A[o][pos]+=val;
    };
    REP_(o,2) {
        FOR_(i,1,n[o]) {
            ll x; scanf("%lld",&x);
            update_value(i,x,o);
            update_value(i+1,-x,o);
        }
    }
    printf("%lld\n",res);
    FOR_(_,1,q) {
        int l,r,op,val;
        scanf("%d%d%d%d",&op,&l,&r,&val);
        op--;
        update_value(l,val,op);
        update_value(r+1,-val,op);
        printf("%lld\n",res);
    }
    return 0;
}
int main() {
    int T; T=1;
    // scanf("%d",&T);
    startTimer();
    // printTimer();
    FOR_(_,1,T) {
        solve();
    }
    // printTimer();
}
/*
3 3 0
1 2 2
2 3 4

2 3 0
1 2
2 3 4
*/