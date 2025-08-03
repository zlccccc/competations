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
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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

const int mod = 998244353;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    // mint operator~() const { return mint(1) / *this;}
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
struct comb {
    vector<mint> fac,inv; // f:fac; g:inv
    comb() {}
    comb(int MAX):fac(MAX),inv(MAX) {
        fac[0] = 1;
        rep_(i,1,MAX) fac[i] = fac[i-1]*i;
        inv[MAX-1] = fac[MAX-1].pow(mod-2);
        rrep_(i,1,MAX) inv[i-1] = inv[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return fac[a]*inv[b]*inv[a-b];
    }
} C(maxn);

ll n;
int a1,a2,a3;
bool vis[67][10][10][10][2][2][2][2][2][2];
mint f[67][10][10][10][2][2][2][2][2][2];
mint calc(int x,int m1,int m2,int m3,int l1,int l2,int l3,int n1,int n2,int n3) {
    // printf("solve %d %d %d %d %d %d %d\n",x,m1,m2,m3,l1,l2,l3);
    if (x==-1) return !m1&&!m2&&!m3&&n1&&n2&&n3;
    if (vis[x][m1][m2][m3][l1][l2][l3][n1][n2][n3]) return f[x][m1][m2][m3][l1][l2][l3][n1][n2][n3];
    mint ret=0;
    int o=(n>>x)&1;
    FOR_(v1,0,max(o,(int)!l1)) FOR_(v2,0,max(o,(int)!l2)) FOR_(v3,0,max(o,(int)!l3)) {
        // printf("v=%d %d %d\n",v1,v2,v3);
        if ((v1^v2)!=v3) continue;
        ret+=calc(x-1,(m1+((ll)v1<<x))%a1,(m2+((ll)v2<<x))%a2,(m3+((ll)v3<<x))%a3,
                    l1&&(o==v1),l2&&(o==v2),l3&&(o==v3),
                    n1||v1,n2||v2,n3||v3);
    }
    f[x][m1][m2][m3][l1][l2][l3][n1][n2][n3]=ret;
    vis[x][m1][m2][m3][l1][l2][l3][n1][n2][n3]=1;
    return ret;
}
void solve() {
    scanf("%lld",&n);
    scanf("%d%d%d",&a1,&a2,&a3);
    memset(vis,0,sizeof(vis));
    mint now=calc(63,0,0,0,1,1,1,0,0,0);
    printf("%lld\n",now.x);
}
int main() {
    solve();
    // while (1) solve();
}
/*
13 2 3 5
1000000000000000000 1 1 1
31415926535897932 3 8 4

*/