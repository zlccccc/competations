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
const LL maxn=1e5+7;
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

struct node{
    int l,r,val;
}T[maxn*32];
int tot=0;
void update(int &x,int pos,int L,int R) {
    T[++tot]=T[x]; x=tot;
    T[x].val++;
    if (L==R) return;
    int mid=(L+R)/2;
    if (pos<=mid) update(T[x].l,pos,L,mid);
    if (mid<pos) update(T[x].r,pos,mid+1,R);
}
int query(int x,int y,int l,int r,int L,int R) {
    if (!x&&!y) return 0;
    if (l<=L&&R<=r) return T[x].val-T[y].val;
    int mid=(L+R)/2,ret=0;
    if (l<=mid) ret+=query(T[x].l,T[y].l,l,r,L,mid);
    if (mid<r) ret+=query(T[x].r,T[y].r,l,r,mid+1,R);
    return ret;
}
int A[maxn],root[maxn];
int solve() {
    int n; tot=0;
    scanf("%d",&n);
    FOR_(i,1,n) scanf("%d",&A[i]);
    ll all=0;
    FOR_(i,1,n) {
        root[i]=root[i-1];
        all+=query(root[i],0,A[i]+1,n,1,n);
        update(root[i],A[i],1,n);
    }
    set<pair<pair<int,int>,ll>> S;
    multiset<ll> Vals;
    Vals.insert(all);
    S.insert({{1,n},all});
    // printf("initial=%lld\n",all);
    FOR_(_,1,n) {
        printf("%lld ",*Vals.rbegin());
        ll x;
        scanf("%lld",&x);
        x^=*Vals.rbegin();
        // printf("ask %lld\n",x);
        auto it=S.upper_bound({{x,INF},INF}); it--;
        ll l=it->first.first,r=it->first.second,sum=it->second;
        S.erase(it);
        Vals.erase(Vals.lower_bound(sum));
        // printf("solve %d %d %d\n",l,x,r);

        if (x-l<r-x) {
            ll cur=0;
            FOR_(i,l,x)
                sum-=query(root[r],root[x-1],1,A[i]-1,1,n);
            FOR_(i,l,x-1) 
                cur+=query(root[i],root[l-1],A[i]+1,n,1,n);
            sum-=cur;
            // printf("solve left %lld %lld\n",cur,sum);
            if (l<=x-1) S.insert({{l,x-1},cur});
            if (x+1<=r) S.insert({{x+1,r},sum});
            Vals.insert(cur);
            Vals.insert(sum);
        } else {
            ll cur=0;
            FOR_(i,x,r)
                sum-=query(root[x],root[l-1],A[i]+1,n,1,n);
            FOR_(i,x+1,r)
                cur+=query(root[r],root[i-1],1,A[i]-1,1,n);
            sum-=cur;
            // printf("solve right %lld %lld\n",cur,sum);
            if (l<=x-1) S.insert({{l,x-1},sum});
            if (x+1<=r) S.insert({{x+1,r},cur});
            Vals.insert(cur);
            Vals.insert(sum);
        }
    }
    puts("");
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
6
15
4 8 8 1 12 1 10 14 7 14 2 9 13 10 3
37 19 23 15 7 2 10 15 2 13 4 5 8 7 10
*/