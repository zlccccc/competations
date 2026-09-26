// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt,tune=native")
#include <sstream>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
#include <cassert>
#include <bitset>
#include <functional>
#include <random>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define REP_(I,N) for (int I=0;I<N;I++)
#define rREP_(I,N) for (int I=N-1;I>=0;I--)
#define rep_(I,S,N) for (int I=S;I<N;I++)
#define rrep_(I,S,N) for (int I=N-1;I>=S;I--)
#define FOR_(I,S,N) for (int I=S;I<=N;I++)
#define rFOR_(I,S,N) for (int I=N;I>=S;I--)

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
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
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

const int mod = 998244353;
struct mint {
    long long x;
    mint():x(0) {}
    mint(long long x):x((x%mod+mod)%mod) {}
    // mint(long long x):x(x){}
    mint &fix() { x = (x%mod+mod)%mod; return *this;}
    mint operator-() const { return mint(0) - *this;}
    // mint operator~() const { return mint(1) / *this;}
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
        for (;t;t>>=1ll,cur=cur*cur)
            if (t&1) ret=ret*cur;
        return ret;
    }
    bool operator<(const mint &a)const { return x < a.x;}
    bool operator==(const mint &a)const { return x == a.x;}
};
struct comb {
    vector<mint> fac,inv; // f:fac; g:inv
    comb() {}
    comb(int MAX):fac(MAX),inv(MAX) {
        fac[0] = 1;
        rep_(i,1,MAX) fac[i] = fac[i-1]*i;
        inv[MAX-1] = fac[MAX-1].pow(mod-2);
        rrep_(i,1,MAX) inv[i-1] = inv[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return fac[a]*inv[b]*inv[a-b];
    }
} C(maxn);

int fa[maxn][17];
int dep[maxn];
vector<pair<int,int>> edge[maxn];
void dfs(int x,int f,int depth) {
    dep[x]=depth; fa[x][0]=f;
    rep_(i,1,17) fa[x][i]=fa[fa[x][i-1]][i-1];
    for (auto p:edge[x]) {
        int v=p.first;
        if (v==f) continue;
        dfs(v,x,depth+1);
    }
}
int lca(int x,int y) {
    int i;
    if (dep[x]<dep[y]) swap(x,y);
    rREP(i,17) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
    if (x==y) return x;
    rREP(i,17) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
struct Type {
    ll f,g,gg;
};
Type merge(Type left,Type right) {
    Type ret; ret.f=ret.g=ret.gg=INFF;
    min_(ret.f,left.f+right.f);
    min_(ret.g,left.f+right.g);
    min_(ret.g,left.g+right.gg);
    min_(ret.gg,left.gg+right.gg);
    return ret;
}
Type up[maxn][17],down[maxn][17];

char s[maxn];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n; ll T;
        scanf("%d%lld",&n,&T);
        FOR_(i,1,n) edge[i].clear();
        FOR_(i,1,n-1) {
            int x,y,w;
            scanf("%d%d%d",&x,&y,&w);
            edge[x].push_back({y,w});
            edge[y].push_back({x,w});
        }
        scanf("%s",s+1);

        // improve需要*2
        int q; scanf("%d",&q);
        vector<pair<int,int>> query(q+1);
        vector<ll> ans(q+1,INFF);
        FOR_(i,1,q) {
            int x,y;
            scanf("%d%d",&x,&y);
            query[i]={x,y};
        }
        dfs(1,0,0);
        FOR_(k,1,17) {
        // FOR_(k,1,1) {
            int W=1<<k;
            vector<ll> dis(n+1,INFF);
            {
                vector<bool> vis(n+1,0);
                priority_queue<pair<ll,int>> Q;
                FOR_(i,1,n) if (s[i]=='1') Q.push({-T*k,i}),dis[i]=T*k;
                while (Q.size()) {
                    auto x=Q.top().second; Q.pop();
                    // printf("x=%d; dis=%lld\n",x,dis[x]);
                    if (vis[x]) continue;
                    vis[x]=1;
                    for (auto p:edge[x]) {
                        int v=p.first,d=p.second+(p.second+W-1)/W;
                        if (dis[v]>d+dis[x]) {
                            // printf(" -> v=%d; d=%d; %d\n",v,d,p.second);
                            dis[v]=d+dis[x];
                            Q.push({-dis[v],v});
                        }
                    }
                }
            }
            // printf("x=%d\n",k);
            // FOR_(i,1,n) printf("%lld ",dis[i]); puts("<- dis");
            function<void(int,int,int)> fix=[&](int x,int f,int len) {
                up[x][0].f=len;
                up[x][0].g=dis[x]+(len+W-1)/W;
                up[x][0].gg=(len+W-1)/W;

                down[x][0].f=len;
                down[x][0].g=dis[f]+(len+W-1)/W;
                down[x][0].gg=(len+W-1)/W;

                rep_(i,1,17) up[x][i]=merge(up[x][i-1],up[fa[x][i-1]][i-1]);
                rep_(i,1,17) down[x][i]=merge(down[fa[x][i-1]][i-1],down[x][i-1]);

                // printf("dfs %d\n",x);
                // REP_(i,3) printf("(%d %d %d %d) ",up[x][i][0][0],up[x][i][0][1],up[x][i][1][0],up[x][i][1][1]); puts("<- up");
                // REP_(i,3) printf("(%d %d %d %d) ",down[x][i][0][0],down[x][i][0][1],down[x][i][1][0],down[x][i][1][1]); puts("<- down");
                // REP_(i,3) printf("(%d %d %d) ",up[x][i].f,up[x][i].g,up[x][i].gg); puts("<- up");
                // REP_(i,3) printf("(%d %d %d) ",down[x][i].f,down[x][i].g,down[x][i].gg); puts("<- down");
                for (auto e:edge[x]) {
                    int v=e.first;
                    if (v==f) continue;
                    fix(v,x,e.second);
                }
            };
            fix(1,0,0);

            FOR_(id,1,q) {
                int x=query[id].first,y=query[id].second;
                Type tx,ty;
                // printf("x=%d;  y=%d\n",x,y);
                tx.f=0; tx.g=tx.gg=INFF;
                ty.f=ty.g=ty.gg=0;
                rREP_(i,17) {
                    if (dep[x]-dep[y]>=1<<i) {
                        tx=merge(tx,up[x][i]); x=fa[x][i];
                    } else if (dep[y]-dep[x]>=1<<i) {
                        ty=merge(down[y][i],ty); y=fa[y][i];
                    }
                }
                // printf("first x=%d;  y=%d\n",x,y);
                if (x!=y) {
                    rREP_(i,17) if (fa[x][i]!=fa[y][i]) {
                        tx=merge(tx,up[x][i]); x=fa[x][i];
                        ty=merge(down[y][i],ty); y=fa[y][i];
                    }
                    tx=merge(tx,up[x][0]); x=fa[x][0];
                    ty=merge(down[y][0],ty); y=fa[y][0];
                }
                tx=merge(tx,ty);
                // printf("second x=%d;  y=%d; %lld %lld %lld\n",x,y,tx.f,tx.g,tx.gg);
                ans[id]=min(ans[id],min(tx.f,tx.g));
            }
            // FOR_(i,1,q) printf("%lld ",ans[i]); puts("  <- first solve");
        }
        FOR_(i,1,q) printf("%lld ",ans[i]); puts("");
    }
}
/*
*/