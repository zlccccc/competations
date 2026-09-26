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


vector<int> red[maxn];
set<int> blue[maxn];
vector<int> nodes;
int id[maxn],tot;
set<vector<int>> items[maxn];
int Fa[maxn];
inline int getFa(int x) {
    if (Fa[x]==x) return x;
    return Fa[x]=getFa(Fa[x]);
}
int res=0;
void dfs(int x,int fa) {
    // x需要是subset中id最小的
    if (id[x]) return;
    id[x]=++tot;
    for (int v:red[x]) if (!id[v]) dfs(v,x);
    items[x].insert({x});
    for (int v:red[x]) if (id[v]>id[x]) {
        set<vector<int>> nxt=items[x];
        for (auto &vec1:items[x]) for (auto &vec2:items[v]) {
            vector<int> cur(vec1.size()+vec2.size());
            merge(vec1.begin(),vec1.end(),vec2.begin(),vec2.end(),cur.begin());
            cur.erase(unique(cur.begin(),cur.end()),cur.end());
            if (cur.size()<=4) nxt.insert(cur);
        }
        items[x].swap(nxt);
    }

    for (auto it=items[x].begin();it!=items[x].end();) {
        vector<int> vec;
        for (int v:*it) vec.push_back(v);
        // for (int v:vec) printf("%d ",v); puts("<- check");
        for (int a:vec) Fa[a]=a;
        for (int a:vec) for (int b:vec) if (a<b) {
            int x=getFa(a),y=getFa(b);
            if (x==y) continue;
            if (blue[a].count(b)) Fa[x]=y;
        }
        int cnt=0;
        for (int a:vec) if (getFa(a)==a) cnt++;
        if (cnt==1) res++;
        if (vec.size()==4) it=items[x].erase(it);
        else it++;
    }
}
int solve() {
    int n,m;
    cin>>n>>m;
    FOR_(i,1,m) {
        int x,y,c;
        cin>>x>>y>>c;
        if (c) red[x].push_back(y),red[y].push_back(x);
        else blue[x].insert(y),blue[y].insert(x);
    }
    FOR_(i,1,n) if (!id[i]) dfs(i,0);
    cout<<res;
    return 0;
}
int main() {
    int T; T=1;
    // cin>>T;
    // scanf("%d",&T);
    startTimer();
    FOR_(_,1,T) {
        solve();
    }
    // printTimer();
}
/*
*/