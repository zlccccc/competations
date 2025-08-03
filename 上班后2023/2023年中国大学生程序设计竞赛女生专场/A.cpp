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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
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
        for (int i=mx;i>0;i--) g[i-1] = g[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return f[a]*g[b]*g[a-b];
    }
} C(maxn);

mint pw[maxn];
// g: n个点m条边二分图数量(n个点颜色0/1,不需要连通); h: m条边需要连通
// f: 边用uid[x-y]区分
mint g[37][907],h[37][907],f[37][907];
void init() {
    const int MAX=30;
    mint inv2=mint(1)/2;
    FOR_(i,1,MAX) {
        FOR_(j,0,i) FOR_(k,0,j*(i-j))
            g[i][k]+=C(i,j)*C(j*(i-j),k); // j个0
        // h[i][k]需要/2; // n个点颜色未知; 也就是说之前同构的图01和10算了两次
        FOR_(k,0,i*(i-1)/2) {
            h[i][k]=g[i][k];
            FOR_(x,1,i-1) FOR_(y,0,x*(x-1)/2) // 枚举最后一个node所在的块有多少个点/多少个边
                h[i][k]-=C(i-1,x-1)*h[x][y]*g[i-x][k-y];
        }

        FOR_(k,0,i*(i-1)/2) {
            f[i][k]=h[i][k]*inv2;
            FOR_(x,1,i-1) FOR_(y,0,x*(x-1)/2) // 枚举最后一个node所在的块有多少个点/多少个边
                f[i][k]+=C(i-1,x-1)*h[x][y]*inv2*f[i-x][k-y];
        }
        // printf("i=%d\n",i);
        // FOR_(k,0,i*(i-1)) printf("%lld ",g[i][k]); puts(" <- g");
        // FOR_(k,0,i*(i-1)) printf("%lld ",h[i][k]/2); puts(" <- h");
        // FOR_(k,0,i*(i-1)) printf("%lld ",f[i][k]); puts(" <- f");
    }
}
void solve() {
    vector<int> ids[10];
    ids[2].push_back(1);
    ids[3].push_back(2);
    ids[4].push_back(3);
    FOR_(_,1,12) {
        int x,y;
        scanf("%d%d",&x,&y);
        FOR_(i,1,9) {
            bool ok=false;
            REP_(j,ids[i].size()) if (ids[i][j]==x) {
                rep_(k,j,ids[i].size()) ids[i+y].push_back(ids[i][k]);
                ids[i].erase(ids[i].begin()+j,ids[i].end());
                ok=true;
                break;
            }
            if (ok) break;
        }
        // FOR_(i,1,9) {
        //     printf("[");
        //     for (int v:ids[i]) printf("%d ",v);
        //     printf("]");
        // } puts("");
    }
    if (ids[9].size()==3) puts("Y");
    else puts("N");
}
int main() {
    init();
    int T; T=1;
    scanf("%d",&T);
    // while (1) solve();
    FOR_(_,1,T){
        solve();
    }
}
/*
3 2
3 3
12 34
20 231104

36
168
539029838
966200489
*/