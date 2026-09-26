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

struct LCA {
    vector<vector<pair<int, ll>>> edge;
    vector<int> sz, fa, son, top, dep, id;
    vector<ll> length;
    LCA() {};
    LCA(int n) : edge(n + 1), sz(n + 1), fa(n + 1), son(n + 1), top(n + 1), dep(n + 1), id(n + 1), length(n + 1) {}
    int tot = 0;
    void addedge(int x, int y, ll w) {
        edge[x].push_back({y, w});
        edge[y].push_back({x, w});
    }
    void dfs1(int u, int f, int depth) {
        int mx = -1;
        fa[u] = f, sz[u] = 1, dep[u] = depth, son[u] = 0;
        for (auto &[v, w] : edge[u]) {
            if (v == f)
                continue;
            length[v] = length[u] + w;
            dfs1(v, u, depth + 1);
            sz[u] += sz[v];
            if (sz[v] > mx)
                mx = sz[v], son[u] = v;
        }
    }
    void dfs2(int u, int f, int x) {
        top[u] = x, id[u] = ++tot;
        if (son[u])
            dfs2(son[u], u, x);
        for (auto &[v, w] : edge[u]) {
            if (v == son[u] || v == f)
                continue;
            dfs2(v, u, v);
        }
    }
    int lca(int x, int y) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]])
                swap(x, y);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y])
            swap(x, y);
        return x;
    }
    ll dis(int x, int y) {
        int f = lca(x, y);
        return length[x] + length[y] - length[f] * 2;
    }
    void solve(int root) {
        dfs1(root, 0, 0);
        dfs2(root, 0, root);
    }
} lca;

bool red[maxn];
ll toplen[maxn];  // towards-top
void dfs_top(int x,int f,ll tlen) {
    if (red[x]) tlen=0;
    toplen[x]=tlen;
    for (auto [v,l]:lca.edge[x]) {
        if (v==f) continue;
        dfs_top(v,x,tlen+l);
    }
}

void solve() {
    int n,m,q;
    // cin>>n>>m>>q;
    read(n); read(m); read(q);
    lca=LCA(n);
    FOR_(i,1,n) red[i]=0;
    FOR_(i,1,m) {
        // int x; cin>>x;
        int x; read(x);
        red[x]=1;
    }
    FOR_(i,1,n-1) {
        int x,y,len;
        // cin>>x>>y>>len;
        read(x); read(y); read(len);
        lca.addedge(x,y,len);
    }
    lca.solve(1);
    dfs_top(1,0,0);
    vector<ll> dp(n+1);  // black; cnt
    FOR_(i,1,q) {
        int k;
        // cin>>k;
        read(k);
        vector<int> inds(k);
        REP_(x,k) read(inds[x]);
        sort(inds.begin(),inds.end(),[&](int x,int y) {return toplen[x]>toplen[y];});
        inds.push_back(0);
        int top=inds[0]; ll w=0;
        ll res=toplen[inds[1]];
        rep_(i,1,k) {
            int x=inds[i],f=lca.lca(top,x);
            // printf("x=%d; f=%d; ptop=%d; w=%lld %lld\n",x,f,top,lca.dis(f,x),lca.dis(top,f)+w);
            w=max(lca.dis(f,x),lca.dis(top,f)+w);
            min_(res,max(w,toplen[inds[i+1]]));
            top=f;
        }
        println(res);
    }
}
int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    int T = 1;
    // cin>>T;
    read(T);
    // scanf("%d",&T);
    startTimer();
    FOR_(_, 1, T) { solve(); }
    // printTimer();
}
/*
2
12 2 4
1 9
1 2 1
2 3 4
3 4 3
3 5 2
2 6 2
6 7 1
6 8 2
2 9 5
9 10 2
9 11 3
1 12 10
4 4 5 7 8
*/