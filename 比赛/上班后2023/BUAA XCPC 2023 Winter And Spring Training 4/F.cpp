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
const LL maxn=1e6+107;
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

vector<int> edge[maxn];
set<int> Q[maxn];
int n;
int T[maxn*4];
void update(int x,int l,int r,int val,int L,int R) {
    if (l<=L&&R<=r) {T[x]+=val; return;}
    int mid=(L+R)/2;
    if (l<=mid) update(x<<1,l,r,val,L,mid);
    if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
}
int query(int x,int pos,int L,int R) {
    if (L==R) return T[x];
    int mid=(L+R)/2,ret=T[x];
    if (pos<=mid) ret+=query(x<<1,pos,L,mid);
    if (mid<pos) ret+=query(x<<1|1,pos,mid+1,R);
    return ret;
}
int f[maxn],g[maxn]; // f:sub-sum; g:maximize
// link u->fa->v;
// f[u]+(g(u')-g[v])
int id[maxn],out[maxn],tot;
ar3 Query[maxn];
void solve(int x) {
    id[x]=++tot;
    for (int v:edge[x]) {
        solve(v);
        f[x]+=g[v]; // g: all-sum
        g[x]+=g[v];
        if (Q[v].size()>Q[x].size()) swap(Q[x],Q[v]);
        for (int i:Q[v]) {
            if (Q[x].count(i)) {
                // solve circle
                int all=Query[i][2];
                all+=query(1,id[Query[i][0]],1,n);
                all+=query(1,id[Query[i][1]],1,n);
                g[x]=max(g[x],f[x]+all);
                Q[x].erase(i);
            } else Q[x].insert(i);
        }
    } out[x]=tot;
    update(1,id[x],out[x],f[x]-g[x],1,n);
}
int fa[maxn];
int main() {
    int m,i;
    scanf("%d%d",&n,&m);
    FOR(i,2,n) {
        scanf("%d",&fa[i]);
        edge[fa[i]].push_back(i);
    }
    FOR(i,1,m) {
        scanf("%d%d%d",&Query[i][0],&Query[i][1],&Query[i][2]);
        Q[Query[i][0]].insert(i);
        Q[Query[i][1]].insert(i);
    }
    solve(1);
    printf("%d\n",g[1]);
}
/*
*/