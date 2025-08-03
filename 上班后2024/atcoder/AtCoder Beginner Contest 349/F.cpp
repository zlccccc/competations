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
        if (b < 0 || a < b)
            return 0;
        return f[a] * g[b] * g[a - b];
    }
} Comb(maxn); // Combination(x,y)

// Arrange(x,y)
mint Arra(int a, int b) { return Comb.f[a] * Comb.g[a - b]; }
// the number of way from (0, 0) to (w, h) which dosn't exceed line y = x + bound (y-x<=bound)
mint Catalan(int w, int h, int bound) { return Comb(w + h, h) - Comb(w + h, h - bound - 1); }

namespace PollardRho {
    LL mul(LL a,LL b,LL M) {
        // LL ret=0;
        // for (; b; b>>=1,(a+=a)>=M&&(a-=M))
        //     if (b&1)(ret+=a)>=M&&(ret-=M);{
        // return ret;
        a=(a%M+M)%M, b=(b%M+M)%M;
        return (((a*b)-(LL)((long double)a*b/M)*M)%M+M)%M;
    }
    LL poww(LL a,LL b,LL M) {
        LL ret=1;
        for (; b; b>>=1,a=mul(a,a,M))
            if (b&1) ret=mul(ret,a,M);
        return ret;
    }
    vector<int> bs={2,3,7,31,61};
    bool check(LL a,LL n,LL x,LL t) {
        LL ret=poww(a,x,n);
        LL last=ret;
        for (ret=mul(ret,ret,n); t--; last=ret,ret=mul(ret,ret,n))
            if (ret==1&&last!=1&&last!=n-1) return true;
        if (ret!=1) return true;
        return false;
    }
    bool Miller_Robin(LL x) {
        for (int p:bs) if(x==p) return 1;
        LL res=x-1, k=0;
        for(; !(res&1); res>>=1,++k);
        for (int p:bs) {
            LL pre=poww(p,res,x), now;
            for(int t=k;t--;swap(now,pre))
                if ((now=mul(pre, pre, x)) == 1 && pre != 1 && pre != x-1)
                    return 0;
            if(pre != 1) return 0;
        }
        return 1;
    }
    LL Rho(LL x, LL c) {
        LL i=1,j=0,sum=1,a=rand()%(x-1)+1,b=a,d=1;
        while(d==1) {
            sum=mul(sum,abs((a=(mul(a,a,x)+c)%x)-b),x);
            if(++j==i) i<<=1, b=a, d=__gcd(sum, x);
            if(!(j&1023)) d=__gcd(sum, x);
        }
        return d==x?Rho(x,c+1):d;
    }
    map<LL, int>mp;
    void Pollard(LL x) {
        if(x == 1) return;
        if(Miller_Robin(x)) { ++mp[x]; return; }
        LL tmp=Rho(x, 3);
        Pollard(tmp), Pollard(x/tmp);
    }
    vector<pair<LL,int> > Solve(LL x) {
        mp.clear(); Pollard(x);
        vector<pair<LL,int> > re;
        for(auto &p:mp) re.push_back(p);
        return re;
    }
}

void fwt(vector<mint> &A,int inv)//对拍对了 
{
    int len=A.size();
    int i,j,k;
    for(i=2;i<=len;i<<=1){
        for(j=0;j<len;j+=i){
            for(k=j;k<j+i/2;k++){
                if (inv==1){
                    auto a=A[k],b=A[k+i/2];
                    A[k+i/2]=a+b;
                    //xor:a[k]=x+y,a[k+i/2]=(x-y+mod)%mod;
                    //and:a[k]=x+y;
                    //or:a[k+i/2]=x+y;
                }else{
                    auto a=A[k],b=A[k+i/2];
                    A[k+i/2]=b-a;
                    //xor:a[k]=(x+y)/2,a[k+i/2]=(x-y)/2;
                    //and:a[k]=x-y;
                    //or:a[k+i/2]=y-x;
                }
            }
        }
    }
}

int solve() {
    int n; ll m;
    cin>>n>>m;
    vector<ll> A(n+1);
    FOR_(i,1,n) cin>>A[i];
    auto mp=PollardRho::Solve(m);
    vector<ll> vec;
    for (auto [v,c]:mp) {
        ll cur=1;
        while (c--) cur*=v;
        vec.push_back(cur);
    }
    vector<mint> f(1<<vec.size());
    FOR_(x,1,n) {
        int cur=0;
        if (m%A[x]) continue;
        REP_(i,vec.size()) if (A[x]%vec[i]==0) cur|=1<<i;
        f[cur]+=1;
        // pr2(cur,vec.size()); puts("<- cur");
    }
    function<void(int,int)> divide=[&](int l,int r) {
        if (l+1==r) {
            f[l]=mint(2).pow(f[l].x)-1;
            return;
        }
        int mid=(l+r)/2;
        divide(l,mid); divide(mid,r);
        vector<mint> A(mid-l),B(r-mid),C(mid-l);
        rep_(i,l,mid) A[i-l]=f[i];
        rep_(i,mid,r) B[i-mid]=f[i];
        fwt(A,1); fwt(B,1);
        REP_(i,mid-l) C[i]=A[i]*B[i];
        fwt(C,-1);
        rep_(i,mid,r) f[i]+=C[i-mid];
    };
    divide(0,f.size());
    cout<<f.back();
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