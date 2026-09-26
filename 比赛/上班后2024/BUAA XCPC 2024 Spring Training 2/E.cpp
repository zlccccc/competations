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

int op,mod=1e9+7;
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
vector<ar3> P;
vector<mint> f4; // all-length; max-length; 一个角的方案数
void Init(int n) {
    FOR_(i,1,n) {
        P.push_back({i*i,i,i});
        P.push_back({i*(i+1),i,i+1});
    }
    vector<vector<mint>> f(n+1,vector<mint>(n+1));
    vector<mint> f1(n+1);
    f4.resize(n+1);
    f[0][0]=1;
    FOR_(i,0,n) {
        // 最后一层length
        FOR_(j,1,i) f[i][j]+=f[i-j][j];
        FOR_(j,0,i) f1[i]+=f[i][j];
        FOR_(j,1,n) f[i][j]+=f[i][j-1]; // prefix-sum
    }
    // FOR_(i,0,n) printf("%d ",f1[i].x); puts("<- f1");
    f4[0]=1;
    REP_(t,4) {
        rFOR_(i,1,n) rFOR_(j,1,i) {
            f4[i]+=f4[i-j]*f1[j];
        }
    }
    // FOR_(i,0,n) printf("%d ",f4[i].x); puts("<- f4");
}
int solve() {
    int n;
    scanf("%d",&n);
    auto [all,H,W]=*lower_bound(P.begin(),P.end(),ar3{n,0,0});
    int remain=all-n;
    if (op==1) {
        printf("%d %d\n",H,W);
        FOR_(i,1,H) {
            FOR_(j,1,W) {
                if (remain) putchar('.'),remain--;
                else putchar('#');
            }
            puts("");
        }
    } else {
        mint res=0;
        while (H*W>=n) {
            int remain=H*W-n;  // min(H,W)>remain
            // printf("solve %d %d: remain=%d\n",H,W,remain);
            res+=f4[remain];
            if (H!=W) res+=f4[remain];
            H--; W++;
        }
        printf("%d %lld\n",(H+W)*2,res.x);
    }
    return 0;
}
int main() {
    int T = 1;
    scanf("%d%d",&T,&op);
    if (op==2) scanf("%d",&mod);
    Init(1000);
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
*/