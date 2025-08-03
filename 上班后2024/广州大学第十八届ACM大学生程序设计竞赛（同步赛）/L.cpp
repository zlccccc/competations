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

namespace fastIO {//感觉没问题, 测试几次
#define BUF_SIZE 100000
    namespace Istream {
        bool IOerror = 0;
        inline char ic() {
            static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
            if (p1==pend) {
                p1=buf;
                pend=buf+fread(buf,1,BUF_SIZE,stdin);
                if (pend == p1) {IOerror = 1; return -1;}
            } return *p1++;
        }
        inline bool blank(char ch) {
            return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
        }
        template<typename T>
        inline void readPositive(T &x) {//no
            char ch; x=0;
            while (blank(ch=ic()));
            if (IOerror) return;
            for (x=0; '0'<=ch&&ch<='9'; ch=ic()) x=x*10+ch-'0';
        }
        template<typename T>
        inline void read(T &x) {
            char ch; T op=1; x=0;
            while (blank(ch=ic()));
            if (IOerror) return;
            if (ch=='-') op=-1,ch=ic();
            for (x=0; '0'<=ch&&ch<='9'; ch=ic()) x=x*10+ch-'0';
            x*=op;
        }
        inline void read(char &c) {
            c=ic();
        }
        inline void read(char *s) { //len
            char ch;
            while (blank(ch=ic()));
            if (IOerror) return;
            for (; !blank(ch)&&!IOerror; ch=ic()) *s++=ch;
            *s='\0';
        }
    }
    namespace Ostream {
        char buf[BUF_SIZE], *p1 = buf, *pend = buf + BUF_SIZE;
        inline void flush() {
            fwrite(buf,1,p1-buf,stdout);
            p1=buf;
        }
        inline void oc(char ch) {
            if (p1 == pend) flush();
            *p1++=ch;
        }
        inline void println() {
            oc('\n');
        }
        template<typename T>
        inline void print(T x) {
            static char s[27],*s1=s;
            if (!x) *s1++='0';
            if (x<0) oc('-'),x=-x;
            while (x) *s1++=x%10+'0',x/=10;
            do {s1--; oc(*s1);} while (s1!=s);
        }
        inline void print(char s) {
            oc(s);
        }
        inline void print(char *s) {
            for (; *s; oc(*s++));
        }
        inline void print(const char *s) {
            for (; *s; oc(*s++));
        }
        inline void print(string s) {
            for (unsigned i=0; i<s.length(); i++) oc(s[i]);
        }
        struct _flush {
            ~_flush() {flush();}
        } fflush;
    };
    template<typename T>
    // inline void read(T &x) {Istream::readPositive(x);}
    inline void read(T &x) {Istream::read(x);} //negative
    inline void read(char *x) {Istream::read(x);}
    template<typename T>
    inline void print(T x) {Ostream::print(x);}
    template<typename T>
    inline void println(T x) {print(x); Ostream::oc('\n');}
}
using namespace fastIO;

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

ll res=0;
struct LeastCommonAncenstor {//内部和外部dfn不同...
    vector<vector<pair<int,ll>>> edge;
    void addedge(int u,int v,int l=1) {
        edge[u].push_back({v,l});
        edge[v].push_back({u,l});
    }
    vector<int> fa,dep,sz; // fa,depth
    vector<ll> len,uplen;  // 每个点到root的距离; 到father距离
    vector<int> id_dfn,dfn;  // dfs序第i个位置是x, dfn[x]=i
    vector<int> st_id,st_vec;
    int n;
    LeastCommonAncenstor(int n=1) :n(n), edge(n+1), dfn(n+1), fa(n+1), uplen(n+1), dep(n+1), len(n+1),st_id(n+1), sz(n+1) {}

    unique_ptr<SparseTable<int>> table;
    void dfs(int x,int f,int depth=0,ll length=0) {
        sz[x]=1;
        dep[x]=depth; len[x]=length;
        st_id[x]=st_vec.size(); st_vec.push_back(x);
        dfn[x]=id_dfn.size(); id_dfn.push_back(x);
        for (auto [v,l]:edge[x]) {
            if (v==f) continue;
            fa[v]=x; uplen[v]=l;
            dfs(v,x,depth+1,length+l);
            sz[x]+=sz[v];
            res+=(ll)sz[v]*(n-sz[v])*2;
            // printf("res: sz=%d; n=%d\n",sz[v],n-sz[v]);
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

int solve() {
    int n;
    scanf("%d",&n);
    LeastCommonAncenstor lca(n);
    FOR_(i,1,n-1) {
        int x,y;
        scanf("%d%d",&x,&y);
        lca.addedge(x,y);
    }
    lca.solve(1);
    // printf("%lld\n",res);
    FOR_(i,1,n) {
        FOR_(j,1,min(n,n*2/i)) {
            res+=min((ll)i*j,lca.dis(i,j))-lca.dis(i,j);
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