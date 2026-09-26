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
// const LL M=585698298;
// const LL M=998244353;
const LL M=1e9+7;
// ll M=1;
const LL maxn=2e5+107;
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
std::mt19937 rng(time(0));
std::mt19937_64 rng64(time(0));

int A[maxn],fa[maxn],id[maxn];//id: topo
void buildtree(int n){
    static int S[maxn],top,tot,i;
    tot=top=0;
    FOR(i,1,n){
        int now=0;
        while (top&&A[S[top]]<A[i]){
            if (now) fa[now]=S[top],id[++tot]=now;//pop
            now=S[top];  top--;
        } S[++top]=i;
        if (now) fa[now]=S[top],id[++tot]=now;//pop
    } int now=0;
    while (top){
        if (now) fa[now]=S[top],id[++tot]=now;
        now=S[top]; top--;
    } fa[now]=0; id[++tot]=now;
    reverse(id+1,id+1+n);// 变成正的
    // FOR(i,1,n) printf("%d ",fa[i]);puts("");
    // FOR(i,1,n) printf("%d ",id[i]);puts("");
    // printf("tot=%d\n",tot);
}
const int MAXDEPTH=31;
int nxt[maxn*32*2][2],tot;
int prefix[maxn],root[maxn];
void insert(int &x,int val,int depth=MAXDEPTH) {
    if (!x) x=++tot,nxt[x][0]=nxt[x][1]=0;
    // if (depth==-1) printf("insert x=%d; val=%d; depth=%d\n",x,val,depth);
    if (depth==-1) return;
    insert(nxt[x][(val>>depth)&1],val,depth-1);
}
int query(int x,int y,int val,int depth=MAXDEPTH) {
    // printf("??? solve %d %d\n",x,y);
    // if (depth==-1) printf("query solve %d %d val=%d; dep=%d\n",x,y,val,depth);
    if (depth==-1) return 0;
    if (!x||!y) return 0;
    int ret=0,a,b;
    REP(a,2) if (nxt[x][a]) {
        b=a^((val>>depth)&1)^1;
        if (nxt[y][b]) ret=max(ret,query(nxt[x][a],nxt[y][b],val,depth-1)|1<<depth);
    }
    if ((ret>>depth)&1) return ret;
    REP(a,2) if (nxt[x][a]) {
        b=a^((val>>depth)&1);
        if (nxt[y][b]) ret=max(ret,query(nxt[x][a],nxt[y][b],val,depth-1));
    }
    // REP(a,2) REP(b,2) if (!(a^b^((val>>depth)&1))) {
    //     if (nxt[x][a]&&nxt[y][b]) ret=max(ret,query(nxt[x][a],nxt[y][b],val,depth-1));
    // }
    return ret;
}
void merge(int x,int &y,int depth=MAXDEPTH) { // insert x into y
    if (!x||!y) {y+=x; return;}
    if (x==y) return;
    if (depth==-1) return;
    // if (!nxt[y][0]) nxt[y][0]=nxt[x][0];
    // if (!nxt[y][1]) nxt[y][1]=nxt[x][1];
    merge(nxt[x][0],nxt[y][0],depth-1);
    merge(nxt[x][1],nxt[y][1],depth-1);
}
int R[maxn]; // right!
int son[maxn][2];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T) {
        int n,i;
        scanf("%d",&n);
        FOR(i,1,n) scanf("%d",&A[i]);
        buildtree(n);
        FOR(i,1,n) son[i][0]=son[i][1]=0;
        FOR(i,2,n) {
            int x=id[i],f=fa[x];
            if (x<f) son[f][0]=x;
            if (x>f) son[f][1]=x;
        }
        // initialize
        // FOR(i,1,n) printf("%d ",fa[i]); puts("<- fa");
        // FOR(i,1,n) printf("%d ",id[i]); puts("<- id");
        tot=0;
        FOR(i,1,n) {
            prefix[i]=A[i]^prefix[i-1];
            root[i]=0;
        }
        int ans=0;
        int zero=0; insert(zero,0);
        function<void(int)> dfs=[&](int x) {
            if (son[x][0]) dfs(son[x][0]);
            if (son[x][1]) dfs(son[x][1]);
            // printf("solve dfs x=%d: A[x]=%d son=%d %d\n",x,A[x],son[x][0],son[x][1]);
            if (son[x][0]) root[x]=root[son[x][0]];
            insert(root[x],prefix[x-1]); // all left-value
            if (son[x][1]) {
                R[x]=R[son[x][1]];
                int v=query(root[x],root[son[x][1]],A[x]);
                ans=max(ans,v);
                // printf("son 1 sol=%d\n",v);
            } else R[x]=x; // 整个区间
            int v=query(root[x],zero,A[x]^prefix[R[x]]);
            ans=max(ans,v);
            if (son[x][1]) merge(root[son[x][1]],root[x]); // all right-value
            // printf("all sequence = %d\n",v);
        };
        dfs(id[1]);
        printf("%d\n",ans);
    }
}
/*
*/