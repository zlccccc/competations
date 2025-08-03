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

deque<ar3> sub;
vector<int> edge[maxn];
void dfs(int x,int fa,int rt,int len) {  // rt: 第一个sz>=3的
    // printf("dfs %d %d %d %d\n",x,fa,rt,k);
    if (edge[x].size()!=2) {
        if (rt) sub.push_back({len,rt,x});
        rt=x,len=0;
    }
    for (int v:edge[x]) {
        if (v==fa) continue;
        dfs(v,x,rt,len+1);
    }
}
int fa[maxn];
int getfa(int x) {
    if (fa[x]==x) return fa[x];
    return fa[x]=getfa(fa[x]);
}
int solve() {
    int n,k;
    scanf("%d",&n);
    FOR_(i,1,n) edge[i].clear();
    FOR_(i,1,n-1) {
        int x,y;
        scanf("%d%d",&x,&y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    sub.clear();
    int rt=1;
    rFOR_(i,1,n) if (edge[i].size()!=2) rt=i;
    dfs(rt,0,0,1);
    sort(sub.begin(),sub.end());
    // for (auto [len,x,y]:sub) printf("get len %d %d %d\n",len,x,y);
    vector<int> adj(n+1),sz(n+1);
    set<int> S; // not removed
    FOR_(i,1,n) if (edge[i].size()!=2) adj[i]=edge[i].size(),sz[i]=1,S.insert(i);
    vector<mint> res(n+1,1);
    FOR_(i,1,n) fa[i]=i;
    rFOR_(i,1,n-1) {
        while (sub.size()&&sub.front()[0]+2<n-i+1) {
            auto [len,x,y]=sub.front(); sub.pop_front();
            x=getfa(x); y=getfa(y);
            // printf("merge x=%d; y=%d\n",x,y);
            // if (x==y) continue;
            sz[x]+=sz[y]+len-1; adj[x]+=adj[y]-2;
            fa[y]=x; S.erase(y);
        }
        // for (int id:S) printf("(%d,%d,%d) ",id,adj[id],sz[id]); puts("<- ids");
        for (int id:S) res[i]*=Comb.f[(adj[id]-1)*(n-1-i)+sz[id]-1];
    }
    // FOR_(i,1,n) printf("%lld ",res[i].x); puts("  <- solve");
    FOR_(i,1,n) res[i]*=Comb(n,i);
    FOR_(i,1,n) printf("%lld ",res[i].x); puts("");
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