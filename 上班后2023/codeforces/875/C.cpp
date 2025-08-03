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
const LL maxn=1e6+107;
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

mint f[maxn];
void init() {
    f[0]=1;
    rep_(i,2,maxn) if (!(i&1)) {
        f[i]=C(i,i/2)-C(i,i/2+1);
    }
    // FOR_(i,0,100) printf("%lld ",f[i].x);
}
vector<int> P[maxn];
set<int> R[maxn];
int L[maxn],all[maxn];
void solve() {
    int n,m;
    scanf("%d%d",&n,&m);
    FOR_(i,1,n) L[i]=all[i]=0;
    FOR_(i,1,n) P[i].clear(),R[i].clear();
    P[1].push_back(n);
    FOR_(i,1,m) {
        int l,r;
        scanf("%d%d",&l,&r);
        P[l].push_back(r);
    }
    mint ans=1;
    int top=0;
    FOR_(i,1,n) {
        sort(P[i].begin(),P[i].end());
        for (int r:P[i]) {
            if (i==r) {ans=0; continue;}
            if (top&&(*(R[top].begin()))<=r) {
                while (top&&(*(R[top].begin()))<=r) {
                    // pop-top(减少)
                    // to i-1
                    // printf("PUSH-POP: i=%d top=%d len=%d; all=%d; R=",i,top,i-L[top],all[top]);
                    // for (int v:R[top]) printf("%d ",v); puts("");
                    ans*=f[i-L[top]-all[top]];
                    all[top]=0; all[top-1]+=i-L[top];// split
                    L[top]=i;
                    if (top!=1&&*(R[top-1].begin())<=r) {
                        // merge...
                        if (R[top].size()>R[top-1].size()) swap(R[top],R[top-1]);
                        for (int v:R[top]) R[top-1].insert(v); R[top].clear();
                        top--;
                        continue;
                    } else {
                        R[top].insert(r);
                        break;
                    }
                }
            } else {
                // printf("push i=%d; ->%d\n",i,r);
                top++; all[top]=0;
                L[top]=i; R[top].insert(r);
            }
        }
        while (top&&*(R[top].begin())==i) { // pop front
            // printf("pop: i=%d, len=%d; all=%d\n",i,i-L[top]+1,all[top]);
            ans*=f[i-L[top]+1-all[top]];
            all[top]=0; all[top-1]+=i-L[top]+1;// split
            L[top]=i+1;
            R[top].erase(i);
            if (!R[top].size()) top--;
        }
    }
    assert(R[1].size()==0);
    printf("%lld\n",ans.x);
}
int main() {
    init();
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        solve();
    }
}
/*
100
1000 7
100 701
200 801
300 901
400 499
410 421
414 423
416 417

1000 3
300 499
400 799
100 699

6 5
1 6
2 3
3 6
3 4
1 4
*/