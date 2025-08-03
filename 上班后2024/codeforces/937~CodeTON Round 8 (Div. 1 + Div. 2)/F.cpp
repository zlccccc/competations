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
        if (a < b)
            return 0;
        return f[a] * g[b] * g[a - b];
    }
} Comb(maxn);  // Combination(x,y)
mint Arra(int a,int b) { // Arrange(x,y)
    return Comb.f[a]*Comb.g[a - b];
}

ll A[maxn];
struct node{
    ll res,add=INF;  // current-value; need-to-change
}T[maxn*4];
ll Sqrt(ll x) {
    ll cur=sqrt(x);
    while (cur*cur<x) cur++;
    while (cur*cur>x) cur--;
    return cur;
}
node merge(node x,node y,int lx,int rx,int ly,int ry) {
    if (x.res+1==y.add) return {y.res,x.add};
    if (x.res+1<y.add) {
        if (rx-lx+1>=7) return {y.res,INF};
        // if (x.res==INF||y.res==INF) return {y.res,INF};
        ll cur=y.add;  // sqrt(A[l-1])>=cur, y.res才能够++
        rFOR_(i,lx,rx) cur=min((ll)INF,cur*cur-A[i]);
        return {y.res,cur};
    }
    if (ry-ly+1>=7) return {y.res+1,INF};
    if (x.res==INF||y.res==INF) return {y.res+1,INF};
    auto check=[&](ll val) {
        rFOR_(i,lx,ry) {
            val=min((ll)INF,val*val-A[i]);
            if (val<=0) return 0ll;
        }
        return val;
    };
    ll left=y.res,right=INF;
    while (left+1<right) {
        ll mid=(left+right)/2;
        if (check(mid)>0) right=mid;
        else left=mid;
    }
    // printf("merge: solve final; right=%lld; check=%lld\n",right,check(right));
    return {left,check(right)};
}
void update(int x,int pos,int L,int R) {
    if (L==R) {
        ll cur=Sqrt(A[L]);
        T[x]={cur,(cur+1)*(cur+1)-A[L]};  // current-value; need-to-change
        // printf("solve single: %d: %lld %lld\n",pos,T[x].res,T[x].add);
        return;
    }
    int mid=(L+R)/2;
    if (pos<=mid) update(x<<1,pos,L,mid);
    if (mid<pos) update(x<<1|1,pos,mid+1,R);
    T[x]=merge(T[x<<1],T[x<<1|1],L,mid,mid+1,R);
    // printf("%d -> %d: %lld %lld\n",L,R,T[x].res,T[x].add);
}
int solve() {
    int n,m;
    scanf("%d%d",&n,&m);
    FOR_(i,1,n) {
        scanf("%lld",&A[i]);
        update(1,i,1,n);
    }
    FOR_(i,1,m) {
        int k;
        scanf("%d",&k);
        scanf("%lld",&A[k]);
        update(1,k,1,n);
        printf("%lld\n",T[1].res);
    }
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