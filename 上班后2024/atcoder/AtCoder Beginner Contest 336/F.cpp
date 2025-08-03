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


int solve() {
    int H,W;
    cin>>H>>W;
    auto hash=[&](vector<vector<int>> &vec) {
        ll hash1=0,hash2=0;
        REP_(i,H) REP_(j,W) hash1=(hash1*71+vec[i][j])%998244353;
        REP_(i,H) REP_(j,W) hash2=(hash2*17+vec[i][j])%1000000007;
        return (hash1<<32)|hash2;
    };
    auto solve=[&](vector<vector<int>> &vec) {
        map<ll,int> MP;
        queue<vector<vector<int>>> Q;
        Q.push(vec);
        while (Q.size()) {
            auto cur=Q.front(); Q.pop();
            ll hashcur=hash(cur);
            int curval=MP[hashcur];
            if (curval==10) continue;
            // REP_(i,H) {REP_(j,W) printf("%d ",cur[i][j]); puts("  <- current ");}
            REP_(x,2) REP_(y,2) {
                vector<vector<int>> now=cur;
                REP_(dx,H-1) REP_(dy,W-1) {
                    // printf("%d %d <- %d %d\n",x+dx,y+dy,x+H-2-dx,y+W-2-dy);
                    now[x+dx][y+dy]=cur[x+H-2-dx][y+W-2-dy];
                }
                ll hashnow=hash(now);
                if (!MP.count(hashnow)) {
                    MP[hashnow]=curval+1;
                    Q.push(now);
                    // puts("push");
                }
                // REP_(i,H) {REP_(j,W) printf("%d ",now[i][j]); puts("  <- conv");}
            }
        }
        return MP;
    };

    vector<vector<int>> vec(H,vector<int>(W));
    REP_(i,H) REP_(j,W) cin>>vec[i][j];
    auto MP1=solve(vec);
    int tot=0;
    REP_(x,H) REP_(y,W) vec[x][y]=++tot;
    auto MP2=solve(vec);
    // puts("fir ok");
    // printf("size = %d\n",MP.size());
    int res=INF;
    for (auto &p:MP2) if (MP1.count(p.first)) res=min(res,p.second+MP1[p.first]);
    // printf("size = %d\n",MP2.size());
    if (res==INF) puts("-1");
    else printf("%d\n",res);
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