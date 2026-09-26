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
const LL maxn=4e5+7;
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
} C(maxn);

char s[maxn],str[maxn*2];
int p[maxn*2];
int f[maxn][26][2];
int solve() {
    int n,q;
    scanf("%d%d",&n,&q);
    scanf("%s",s+1);
    FOR_(i,1,n) {
        REP_(k,26) REP_(o,2) f[i][k][o]=f[i-1][k][o];
        f[i][s[i]-'a'][i&1]++;
    }
    {
        str[0]='+'; str[1]='%';
        FOR_(i,1,n) {
            str[i*2]=s[i];
            str[i*2+1]='%';
        }
        int len2=n*2+2;
        
        int id=0,mx=0; int i;
        FOR_(i,1,len2-1) {
            if (mx>i) p[i]=min(p[2*id-i],mx-i);
            else p[i]=1;
            while (str[i+p[i]]==str[i-p[i]]) p[i]++;
            if (p[i]+i>mx) {
                mx=p[i]+i; id=i;
            }
        }

        // FOR_(i,1,len2) printf("%c ",str[i]); puts("<- s");
        // FOR_(i,1,len2) printf("%d ",p[i]-1); puts("<- p");
    }
    // 需要判断[l,r]是否回文
    FOR_(i,1,q) {
        int l,r;
        scanf("%d%d",&l,&r);
        int f0=0,f1=0,fall=0;
        REP_(k,26) {
            max_(f0,f[r][k][0]-f[l-1][k][0]);
            max_(f1,f[r][k][1]-f[l-1][k][1]);
            max_(fall,f[r][k][0]-f[l-1][k][0]+f[r][k][1]-f[l-1][k][1]);
        }
        // 判断all-same或者same1&&same2
        if (fall==r-l+1) { printf("%d\n",0); continue; }
        int plen=p[l+r]-1; // 判断s是否回文
        bool par=(plen>=r-l+1);
        // printf("plen=%d; %d\n",plen,par);
        ll all=0;
        if (f0+f1==r-l+1) { // 奇数偶数分别same
            ll mx=(r-l+1)/2;
            all=mx*(mx+1); // 2+4+6+8...
        } else {
            all=(ll)(r-l+1)*(r-l+2)/2-1;
            if (par) all-=r-l+1;
        }
        printf("%lld\n",all);
    }
    return 0;
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
*/