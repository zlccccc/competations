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
typedef array<int,5> ar5;
typedef array<int,4> ar4;
typedef array<int,3> ar3;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));
vector<pii> direction4 = {{-1,0},{0,-1},{0,1},{1,0}};
vector<pii> direction8 = {{-1,-1},{-1,0},{1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

const int mod = 1e9+7;
// const int mod=998244353;
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
} Comb(maxn);  // Combination(x,y)
mint Arra(int a,int b) { // Arrange(x,y)
    return Comb.f[a]*Comb.g[a - b];
}

int solve() {
    int n,m;
    scanf("%d%d",&n,&m);
    vector<vector<int>> A(n+1,vector<int>(n+1));
    FOR_(i,1,n) FOR_(j,1,n) scanf("%d",&A[i][j]);
    ll res=0;
    REP_(k,4) {
        vector<vector<ll>> LU(n+2,vector<ll>(n+2));
        vector<vector<ll>> RU(n+2,vector<ll>(n+2));
        vector<ll> U(n+2),U2(n+2),D(n+2);  // 上面俩 底下一个
        vector<vector<ll>> Sum(n+2,vector<ll>(n+2));
        FOR_(i,1,n) FOR_(j,1,n) Sum[i][j]=A[i][j]+Sum[i-1][j]+Sum[i][j-1]-Sum[i-1][j-1];
        FOR_(lx,1,n-m+1) {
            FOR_(ly,1,n-m+1) {
                int rx=lx+m-1,ry=ly+m-1;
                ll all=Sum[rx][ry]-Sum[lx-1][ry]-Sum[rx][ly-1]+Sum[lx-1][ly-1];
                LU[rx][ry]=RU[rx][ly]=all;
                max_(D[lx],all);
                max_(U[rx],all);
            }
        }
        FOR_(x,1,n) {
            FOR_(y,1,n) max_(LU[x][y],LU[x-1][y]),max_(LU[x][y],LU[x][y-1]);
            rFOR_(y,1,n) max_(RU[x][y],RU[x-1][y]),max_(RU[x][y],RU[x][y+1]);
            // max_(U2[x],U2[x-1]);
            FOR_(y,1,n-1) max_(U2[x],LU[x][y]+RU[x][y+1]);
        }
        FOR_(x,1,n) max_(U[x],U[x-1]);
        rFOR_(x,1,n) max_(D[x],D[x+1]);

        FOR_(lx,1,n-m+1) {
            FOR_(ly,1,n-m+1) {
                int rx=lx+m-1,ry=ly+m-1;
                ll all=Sum[rx][ry]-Sum[lx-1][ry]-Sum[rx][ly-1]+Sum[lx-1][ly-1];
                // 上面两个
                max_(res,all+U2[lx-1]);
                // 上面一个下面一个
                max_(res,all+U[lx-1]+D[rx+1]);
                // if (all+U2[lx-1]>=3295) printf("f21  k=%d: lx=%d; ly=%d: U2=%lld; cur=%lld; all=%lld\n",k,lx,ly,U2[lx-1],all,all+U2[lx-1]);
                // printf("f111 k=%d: lx=%d; ly=%d: U=%lld; D=%lld; cur=%lld; all=%lld\n",k,lx,ly,U[lx-1],D[rx+1],all,all+U[lx-1]+D[rx+1]);
            }
        }
        { // rotate
            vector<vector<int>> B(n+1,vector<int>(n+1));
            FOR_(i,1,n) FOR_(j,1,n) B[j][n+1-i]=A[i][j];
            A.swap(B);
            // puts("Convert");
            // FOR_(i,1,n) FOR_(j,1,n) printf("%d%c",A[i][j]," \n"[j==n]);
        }
    }
    printf("%lld\n",res);
    return 0;
}
int main() {
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
*/