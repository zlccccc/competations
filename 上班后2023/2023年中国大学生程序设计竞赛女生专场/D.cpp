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
        for (int i=mx;i>0;i--) g[i-1] = g[i]*i;
    }
    mint operator()(int a, int b) {
        if (a < b) return 0;
        return f[a]*g[b]*g[a-b];
    }
} C(maxn);


namespace mincostflow {
    typedef int type;
    const type INF=0x3f3f3f3f;
    struct node {
        int to; type cap,cost; int rev;
        node(int t=0,type c=0,type _c=0,int n=0):
            to(t),cap(c),cost(_c),rev(n) {};
    }; vector<node> edge[maxn];
    void addedge(int from,int to,type cap,type cost,type rcap=0) {
        edge[from].push_back(node(to,cap,cost,edge[to].size()));
        edge[to].push_back(node(from,rcap,-cost,edge[from].size()-1));
    }
    int prev[maxn],pree[maxn];//pre_cnt
    type dis[maxn],h[maxn];
    pair<type,type> mincostflow(int s,int t,int n,type flow=INF) {
        type ret=0,ans=0;
        memset(h+1,0,n*sizeof(type));
        while (flow) {
            // dij
            typedef pair<type,int> pti;
            memset(dis+1,0x3f,n*sizeof(type));
            static priority_queue<pti,vector<pti>,greater<pti> > Q;
            dis[s]=0; Q.push(pti(0,s));
            while (Q.size()) {
                auto now=Q.top(); Q.pop();
                // printf("now=%d; dis=%d\n",now.second,now.first);
                if (dis[now.second]<now.first) continue;
                int i,v=now.second;
                REP_(i,(int)edge[v].size()) {
                    node &e=edge[v][i];
                    if (e.cap>0&&dis[e.to]>dis[v]+e.cost+h[v]-h[e.to]) {
                        dis[e.to]=dis[v]+e.cost+h[v]-h[e.to];
                        prev[e.to]=v; pree[e.to]=i;
                        Q.push(pti(dis[e.to],e.to));
                    }
                }
            } int i;
            if (dis[t]==INF) break;
            FOR_(i,1,n) h[i]+=dis[i];
            type d=flow;
            for (int i=t; i!=s; i=prev[i])
                d=min(d,edge[prev[i]][pree[i]].cap);
            if (d==0) break;
            if (h[t]>0) return make_pair(ret,ans); // 直接停止
            flow-=d; ret+=d; ans+=d*h[t];
            for (int i=t; i!=s; i=prev[i]){
                node &e=edge[prev[i]][pree[i]];
                e.cap-=d; edge[e.to][e.rev].cap+=d;
            }
        } return make_pair(ret,ans);
    }
    void init(int n) {
        int i; FOR_(i,1,n) edge[i].clear();
    }
}
int idx[37][37],idy[37][37]; // 拆点
int solve() {
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    int tot=0;
    int S=++tot,T=++tot;
    FOR_(i,1,n) FOR_(j,1,m) {
        idx[i][j]=++tot;
        idy[i][j]=++tot;
    }
    mincostflow::init(tot);
    FOR_(i,1,n) FOR_(j,1,m) {
        int op;
        scanf("%d",&op);
        if (op==1) mincostflow::addedge(idx[i][j],idy[i][j],1,0);
        if (op==0) mincostflow::addedge(idx[i][j],idy[i][j],1,1);

        if (i!=1) mincostflow::addedge(idy[i][j],idx[i-1][j],1,0);
        if (i!=n) mincostflow::addedge(idy[i][j],idx[i+1][j],1,0);
        if (j!=1) mincostflow::addedge(idy[i][j],idx[i][j-1],1,0);
        if (j!=m) mincostflow::addedge(idy[i][j],idx[i][j+1],1,0);
    }
    FOR_(i,1,k) {
        int x,y;
        scanf("%d%d",&x,&y);
        mincostflow::addedge(S,idx[x][y],1,-100);
    }
    FOR_(i,1,k) {
        int x,y;
        scanf("%d%d",&x,&y);
        mincostflow::addedge(idy[x][y],T,1,0);
    }
    auto res=mincostflow::mincostflow(S,T,tot);
    // printf("%d %d\n",res.first,res.second);
    printf("%d\n",-res.second);
    return 0;
}
int main() {
    int T; T=1;
    FOR_(_,1,T) solve();
}
/*
*/