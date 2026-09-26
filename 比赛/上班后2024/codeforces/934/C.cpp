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

struct LCA {
    vector<vector<int>> edge;
    vector<int> sz, fa, son, top, dep, id;
    LCA(int n) : edge(n + 1), sz(n + 1), fa(n + 1), son(n + 1), top(n + 1), dep(n + 1), id(n + 1) {}
    int tot=0;
    void addedge(int x,int y) {
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    void dfs1(int u,int f,int depth) {
        // printf("dfs1 %d %d %d\n",u,f,depth);
        int mx=-1; fa[u]=f;
        sz[u]=1; dep[u]=depth; son[u]=0;
        for(int v:edge[u]){
            if (v==f) continue;
            dfs1(v,u,depth+1);
            sz[u]+=sz[v];
            if (sz[v]>mx) mx=sz[v],son[u]=v;
        }
    }
    void dfs2(int u,int f,int x) {
        // printf("dfs2 %d %d %d\n",u,f,x);
        top[u]=x; id[u]=++tot;
        if (son[u]) dfs2(son[u],u,x);
        for (int v:edge[u]){
            if (v==son[u]||v==f) continue;
            dfs2(v,u,v);
        }
    }
    int lca(int x,int y){
        // printf("lca %d %d\n",x,y);
        while (top[x]!=top[y]){
            if (dep[top[x]]<dep[top[y]]) swap(x,y);
            x=fa[top[x]];
        }
        if (dep[x]>dep[y]) swap(x,y);
        return x;
    }
    int dis(int x,int y) {
        return dep[x]+dep[y]-2*dep[lca(x,y)];
    }
    void solve(int root) {
        dfs1(root,0,0);
        dfs2(root,0,root);
    }
};

int solve() {
    int n,q;
    scanf("%d",&n);
    vector<vector<int>> edge(n+1);
    FOR_(i,1,n-1) {
        int x,y;
        scanf("%d%d",&x,&y);
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    vector<int> parent(n+1);
    vector<int> dep(n+1);
    auto find=[&](int x) {
        fill(dep.begin(),dep.end(),0);
        fill(parent.begin(),parent.end(),0);
        function<void(int,int)> dfs=[&](int x,int fa) {
            parent[x]=fa;
            dep[x]=dep[fa]+1;
            for (int v:edge[x]) if (v!=fa) {
                dfs(v,x);
            }
        };
        dfs(x,0);
        return max_element(dep.begin()+1,dep.end())-dep.begin();
    };
    vector<int> chain;
    int x=find(1);
    int y=find(x);
    for (int c=y;c;c=parent[c]) chain.push_back(c);
    // printf("get %d %d\n",x,y);
    // for (int c:chain) printf("%d ",c); puts("<- chain");
    int k=chain.size();
    vector<pii> res;
    if (k&1) {
        REP_(i,(k+1)/2) res.push_back({chain[(k-1)/2],i});
    } else {
        for (int len=(k-2)/2;len>=0;len-=2) {
            res.push_back({chain[k/2-1],len});
            res.push_back({chain[k/2],len});
        }
    }
    printf("%d\n",res.size());
    for (auto [x,l]:res) printf("%d %d\n",x,l);
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