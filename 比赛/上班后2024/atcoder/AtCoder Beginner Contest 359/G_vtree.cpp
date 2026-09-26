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
const LL maxn=2e5+7;
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


template <typename T> struct SparseTable {
    int n;
    vector<vector<T>> sparse; // func: function
    function<bool(T,T)> cmp;
    SparseTable(const vector<T> &vec, function<bool(T,T)> func=nullptr) {
        if (func==nullptr) cmp=[](T x,T y) {return x<y;};
        else cmp=func;
        n = static_cast<int>(vec.size());
        int max_log = 32 - __builtin_clz(n);
        sparse.resize(max_log);
        sparse[0] = vec;
        for (int level = 1; level < max_log; level++) {
            sparse[level].resize(n - (1 << level) + 1);
            for (int i = 0; i <= n - (1 << level); i++) {
                sparse[level][i] = std::min(sparse[level - 1][i], sparse[level - 1][i + (1 << (level - 1))], cmp);
            }
        }
    }
    T get(int from, int to) const {
        assert(0 <= from && from <= to && to < n);
        assert(cmp!=nullptr);
        int lg = 32 - __builtin_clz(to - from + 1) - 1;
        return std::min(sparse[lg][from], sparse[lg][to - (1 << lg) + 1], cmp);
    }
};
struct LeastCommonAncenstor {//内部和外部dfn不同...
    vector<vector<pair<int,ll>>> edge;
    void addedge(int u,int v,int l=1) {
        edge[u].push_back({v,l});
        edge[v].push_back({u,l});
    }
    vector<int> fa,dep; // fa,depth
    vector<ll> len,uplen;  // 每个点到root的距离; 到father距离
    vector<int> id_dfn,dfn;  // dfs序第i个位置是x, dfn[x]=i
    vector<int> st_id,st_vec;
    int n;
    LeastCommonAncenstor(int n=1) :n(n), edge(n+1), dfn(n+1), fa(n+1), uplen(n+1), dep(n+1), len(n+1),st_id(n+1) {}

    unique_ptr<SparseTable<int>> table;
    void dfs(int x,int f,int depth=0,ll length=0) {
        dep[x]=depth; len[x]=length;
        st_id[x]=st_vec.size(); st_vec.push_back(x);
        dfn[x]=id_dfn.size(); id_dfn.push_back(x);
        for (auto [v,l]:edge[x]) {
            if (v==f) continue;
            fa[v]=x; uplen[v]=l;
            dfs(v,x,depth+1,length+l);
            st_vec.push_back(x);
        }
    }
    inline int lca(int x,int y) {
        if (table==nullptr) {
            puts("Not Initialized!");
            return -1;
        }
        int l=st_id[x],r=st_id[y];
        if (l>r) swap(l,r);
        int f=table->get(l,r);
        return f;
    }
    inline ll dis(int x,int y) {
        return len[x]+len[y]-2*len[lca(x,y)];
    }
    void solve(int root) {
        dfs(1,0);
        table=make_unique<SparseTable<int>> (st_vec,[&](int x,int y) {return dep[x]<dep[y];});
    }
};

struct VirtualTree {
    LeastCommonAncenstor lca;
    vector<vector<int>> vedge;
    vector<int> mark,vfa;  // vid: 第x个位置的id, 从虚树root往下做的
    vector<ll> vuplen;  // 虚数上节点到father的距离; 需要注意, 中间的节点是没有合并的~ 如果要看中间有没有mark节点的话需要通过别的手段去检查
    VirtualTree() {};
    VirtualTree(int n): vedge(n+1), mark(n+1), vfa(n+1), vuplen(n+1), lca(n+1) {}
    vector<int> vid; // build结束以后的点有哪些
    void clear_lastvtree() {
        for (int v:vid) vedge[vfa[v]].clear(),mark[v]=0;
        vid.clear();
    }
    void build_vtree(vector<int> pid) {
        // puts("clear start");
        if (!pid.size()) return;
        clear_lastvtree();
        auto addvedge=[&](int u,int v) {
            vfa[v]=u; vuplen[v]=lca.dis(u,v);
            vedge[u].push_back(v);  // len记录在vuplen[v]
        };
        sort(pid.begin(),pid.end(),[&](int x,int y) { return lca.dfn[x]<lca.dfn[y]; });
        static int S[maxn],top;
        S[top=1]=pid[0];
        mark[pid[0]]=1;
        // for (int v:pid) printf("%d ",v); puts("<- pid");
        rep_(i,1,(int)pid.size()) {
            int f=lca.lca(pid[i-1],pid[i]);
            // printf("build %d %d; f=%d\n",pid[i-1],pid[i],f);
            while (top&&lca.dep[S[top]]>lca.dep[f]) {
                int v=S[top--];
                vid.push_back(v);
                if (top&&lca.dep[S[top]]>lca.dep[f]) addvedge(S[top],v);
                else addvedge(f,v);
            } if (!top||S[top]!=f) S[++top]=f;
            S[++top]=pid[i]; mark[pid[i]]=1;
        } while (top-1) addvedge(S[top-1],S[top]),vid.push_back(S[top--]);
        vid.push_back(S[1]);
        reverse(vid.begin(),vid.end());
        vfa[vid[0]]=0;
        // puts("build done");
    }
};

int solve() {
    int n;
    scanf("%d",&n);
    VirtualTree vtree(n);
    FOR_(i,1,n-1) {
        int x,y;
        scanf("%d%d",&x,&y);
        vtree.lca.addedge(x,y);
    }
    map<int,vector<int>> MP;
    vtree.lca.solve(1);
    FOR_(i,1,n) {
        int col;
        scanf("%d",&col);
        MP[col].push_back(i);
    }
    ll res=0;
    vector<int> sz(n+1);
    for (auto [col,ind]:MP) {
        vtree.build_vtree(ind);
        // printf("col=%d\n",col);
        for (int v:vtree.vid) sz[v]=0;
        rREP_(i,vtree.vid.size()) {
            int x=vtree.vid[i],f=vtree.vfa[x];
            vtree.mark[f]+=vtree.mark[x];
            res+=(ll)vtree.vuplen[x]*vtree.mark[x]*(ind.size()-vtree.mark[x]);
        }
        // for (int v:vtree.vid) printf("%d: fa=%d; len=%d mark=%d ",v,vtree.vfa[v],vtree.vuplen[v],vtree.mark[v]); puts("<- v");
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