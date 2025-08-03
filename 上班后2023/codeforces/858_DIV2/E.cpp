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
// const LL M=1e9+7;
const LL M=998244353;
// ll M=1;
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
template<typename T>inline T gcd(T a, T b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
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
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
typedef array<int,4> ar4;
typedef array<int,3> ar3;
typedef array<int,2> ar2;
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

ll pw[maxn],A[maxn];
const int SIZE=500;
vector<int> edge[maxn];
int cl[maxn],cr[maxn],dfn[maxn<<1];
int dep[maxn];
int tot;
int fa[maxn][21];
void dfs(int x,int fa,int depth) {
    ::fa[x][0]=fa;
    rep_(i,1,20) ::fa[x][i]=::fa[::fa[x][i-1]][i-1];
    cl[x]=++tot; dfn[tot]=x; dep[x]=depth;
    pw[x]+=pw[fa]; pw[x]+=A[x]*A[x];
    for (int v:edge[x]) if (v!=fa) {
        dfs(v,x,depth+1);
    } cr[x]=++tot; dfn[tot]=x;
}
int lca(int x,int y) {
    int i;
    if (dep[x]<dep[y]) swap(x,y);
    rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
    if (x==y) return x;
    rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int block[maxn<<1];
struct node {
    int l,r,id;
} Q[maxn];
int cmp(node a,node b) {
    if (block[a.l]==block[b.l]) return a.r<b.r;
    return block[a.l]<block[b.l];
}
bool vis[maxn];
ll cnt[maxn];
ll cur[maxn];//block,now
ll nowans=0,ans[maxn];
void change(int x) {
    x=dfn[x]; vis[x]^=1;
    if (vis[x]) { // insert x
        cur[dep[x]]*=A[x]; cnt[dep[x]]++;
        if (cnt[dep[x]]==2) nowans+=cur[dep[x]];
    } else { // remove
        if (cnt[dep[x]]==2) nowans-=cur[dep[x]];
        cnt[dep[x]]--; cur[dep[x]]/=A[x];
    }
}
ll fin[maxn];
int main() {
    int n,q;
    scanf("%d%d",&n,&q);
    FOR_(i,0,n) cur[i]=1;
    FOR_(i,0,n*2+1) block[i]=i/SIZE;
    FOR_(i,1,n) scanf("%lld",&A[i]);
    FOR_(i,2,n) {
        int p; scanf("%d",&p);
        edge[p].push_back(i);
    }
    dfs(1,0,0);
    REP_(i,q) {
        int a,b;
        scanf("%d%d",&a,&b);
        ans[i]+=pw[lca(a,b)];
        if (cl[a]>cl[b]) swap(a,b);
        if (cr[a]>cr[b]) Q[i].l=cl[a]+1,Q[i].r=cl[b];
        else Q[i].l=cr[a],Q[i].r=cl[b];
        Q[i].id=i;
    }
    sort(Q,Q+q,cmp);
    int L=1,R=0;
    REP_(i,q) {
        while (L<Q[i].l) {change(L); L++;}
        while (R>Q[i].r) {change(R); R--;}
        while (L>Q[i].l) {L--; change(L);}
        while (R<Q[i].r) {R++; change(R);}
        ans[Q[i].id]+=nowans;
    }
    REP_(i,q) printf("%lld\n",ans[i]);
}