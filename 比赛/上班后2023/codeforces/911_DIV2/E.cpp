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
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void add_(T &A,int B,ll MOD) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T fastgcd(T a, T b) {
    int az=__builtin_ctz(a),bz=__builtin_ctz(b),z=min(az,bz),diff; b>>=bz;
    while (a) {
        a>>=az; diff=b-a; az=__builtin_ctz(diff);
        min_(b,a); a=abs(diff);
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

namespace Tarjan {
    struct Edge {
        int to,next;
        Edge(int _to=0,int _next=-1):to(_to),next(_next) {};
    } edge[maxn*2];
    int head[maxn],etot;
    inline void addedge(int u,int v) {
        edge[++etot]=Edge(v,head[u]);
        head[u]=etot;
    }
    //lowlink是说,遇到的min
    //无向图:
    //u割点:low[v]>=dfn[u];(表示能到的点都在之后)
    //u-v割边(桥):low[v]>dfn[u];(要在u-v处得到)
    //块:low[u]==dfn[u];(最终从stack取出x)
    //dfs时注意fa和重边处理
    //无向图不用vis这个东西=_=,vis是为了避免横叉边
    vector<int> nodes[maxn];
    int cnt;
    int dfn[maxn],low[maxn],tot;
    bool vis[maxn];//instack
    int S[maxn],top;
    int id[maxn];
    void tarjan(int x) {
        low[x]=dfn[x]=++tot;
        S[++top]=x;
        vis[x]=1;
        for(int i=head[x]; ~i; i=edge[i].next) {
            int v=edge[i].to;
            if(!dfn[v]) {
                tarjan(v);
                low[x]=min(low[x],low[v]);
            } else if(vis[v])
                low[x]=min(low[x],dfn[v]);
        }
        if(low[x]==dfn[x]) {
            cnt++;
            while(1) {
                int now=S[top--];
                vis[now]=0;
                id[now]=cnt;
                nodes[cnt].push_back(now);
                if(now==x) break;
            }
        }
    }
}

using namespace Tarjan;

int solve() {
    int n,m;
    scanf("%d%d",&n,&m);
    FOR_(i,1,n) head[i]=-1,low[i]=vis[i]=dfn[i]=0;
    etot=0; cnt=tot=0; top=0;
    FOR_(i,1,n) nodes[i].clear();

    vector<int> A(n+1);
    FOR_(i,1,n) scanf("%d",&A[i]);
    vector<pair<int,int>> E;
    FOR_(i,1,m) {
        int x,y;
        scanf("%d%d",&x,&y);
        E.push_back({x,y});
        addedge(x,y);
    }
    FOR_(i,1,n) if (!dfn[i]) tarjan(i);
    // printf("cnt=%d\n",cnt);
    // FOR_(i,1,cnt) {
    //     for (int v:nodes[i]) printf("%d ",v);
    //     puts("");
    // }
    vector<vector<int>> Edge(cnt+1);
    vector<int> D(cnt+1);
    for (auto &edge:E) {
        int x=edge.first,y=edge.second;
        x=id[x]; y=id[y];
        if (x!=y) Edge[x].push_back(y),D[y]++;
    }
    queue<int> Q;
    FOR_(i,1,cnt) if (!D[i]) Q.push(i);

    pair<int,ll> res={0,0};
    vector<pair<int,ll>> Sol(cnt+1);
    while (Q.size()) {
        int x=Q.front(); Q.pop();
        for (int v:nodes[x]) Sol[x].first++,Sol[x].second-=A[v];
        res=max(res,Sol[x]);
        for (int v:Edge[x]) {
            Sol[v]=max(Sol[v],Sol[x]);
            D[v]--;
            if (!D[v]) Q.push(v);
        }
    }
    printf("%d %lld\n",res.first,-res.second);
    return 0;
}
int main() {
    int T; T=1;
    scanf("%d",&T);
    // while (1) solve();
    FOR_(_,1,T){
        solve();
    }
}
/*
*/

