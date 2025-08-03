// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define REP_(I,N) for (auto I=0,END=(N);I<END;I++)
#define rREP_(I,N) for (auto I=(N)-1;I>=0;I--)
#define rep_(I,S,N) for (auto I=(S),END=(N);I<END;I++)
#define rrep_(I,S,N) for (auto I=(N)-1,START=(S);I>=START;I--)
#define FOR_(I,S,N) for (auto I=(S),END=(N);I<=END;I++)
#define rFOR_(I,S,N) for (auto I=(N),START=(S);I>=START;I--)

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

int L[3][3];
int solve() {
    int v1,v2,v3;
    cin>>v1>>v2>>v3;
    auto vox2=[](int A[3],int B[3]) {
        int res=1;
        res*=max(0,min(A[0]+7,B[0]+7)-max(A[0],B[0]));
        res*=max(0,min(A[1]+7,B[1]+7)-max(A[1],B[1]));
        res*=max(0,min(A[2]+7,B[2]+7)-max(A[2],B[2]));
        return res;
    };
    auto vox3=[](int A[3],int B[3],int C[3]) {
        int res=1;
        res*=max(0,min(min(A[0]+7,B[0]+7),C[0]+7)-max(max(A[0],B[0]),C[0]));
        res*=max(0,min(min(A[1]+7,B[1]+7),C[1]+7)-max(max(A[1],B[1]),C[1]));
        res*=max(0,min(min(A[2]+7,B[2]+7),C[2]+7)-max(max(A[2],B[2]),C[2]));
        return res;
    };
    for (L[1][0]=-7;L[1][0]<=7;L[1][0]++) for (L[1][1]=-7;L[1][1]<=7;L[1][1]++) for (L[1][2]=-7;L[1][2]<=7;L[1][2]++) {
        for (L[2][0]=0;L[2][0]<=7;L[2][0]++) for (L[2][1]=0;L[2][1]<=7;L[2][1]++) for (L[2][2]=0;L[2][2]<=7;L[2][2]++) {
            int f1=7*7*7*3;
            int f2=vox2(L[0],L[1])+vox2(L[0],L[2])+vox2(L[2],L[1]);  // 算了两次
            int f3=vox3(L[0],L[1],L[2]);
            f2-=f3*3;
            f1-=f2*2+f3*3;
            // cout<<f1<<" "<<f2<<" "<<f3<<endl;
            if (f1==v1&&f2==v2&&f3==v3) {
                cout<<"Yes"<<endl;
                REP_(i,3) REP_(j,3) cout<<L[i][j]<<" ";
                return 0;
            }
        }
    }
    cout<<"No";
    return 0;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int T = 1;
    // cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
*/