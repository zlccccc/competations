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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
 
#define DEBUG1
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
const LL M=998244353;
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
    ll ret=1;
    for (; b; b>>=1ll,a=a*a%mod)
        if (b&1) ret=ret*a%mod;
    return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

namespace NTT {
    const int maxn=1<<20|7;
    const ll MOD=998244353;
    const ll g=3;
    int wn[maxn],invwn[maxn];
    ll mul(ll x,ll y) {
        return x*y%MOD;
    }
    ll poww(ll a,ll b) {
        ll ret=1;
        for (; b; b>>=1ll,a=mul(a,a))
            if (b&1) ret=mul(ret,a);
        return ret;
    }
    void initwn(int l) {
        static int len=0;
        if (len==l) return; len=l;
        ll w=poww(g,(MOD-1)/len); int i;
        ll invw=poww(w,MOD-2); wn[0]=invwn[0]=1;
        rep(i,1,len) {
            wn[i]=mul(wn[i-1],w);
            invwn[i]=mul(invw,invwn[i-1]);
        }
    }
    void ntt(ll *A,int len,int inv) {
        int i,j,k; initwn(len);
        for (i=1,j=len/2; i<len-1; i++) {
            if (i<j) swap(A[i],A[j]);
            k=len/2;
            while (j>=k) j-=k,k/=2;
            if (j<k) j+=k;
        } for (i=2; i<=len; i<<=1) {
            for (j=0; j<len; j+=i) {
                for (k=j; k<(j+i/2); k++) {
                    ll a,b; a=A[k];
                    if (inv==-1) b=mul(A[k+i/2],invwn[(ll)(k-j)*len/i]);
                    else b=mul(A[k+i/2],wn[(ll)(k-j)*len/i]);
                    A[k]=(a+b); (A[k]>=MOD) &&(A[k]-=MOD);
                    A[k+i/2]=(a-b+MOD); (A[k+i/2]>=MOD) &&(A[k+i/2]-=MOD);
                }
            }
        } if (inv==-1) {
            ll vn=poww(len,MOD-2);
            REP(i,len) A[i]=mul(A[i],vn);
        }
    }
    void solve(ll A[],int n) {
        int len=1,i;
        while (len<n+n-1) len<<=1;
        ntt(A,len,1);
        REP(i,len) A[i]=mul(A[i],A[i]);
        ntt(A,len,-1);
    }
}
ll A[maxn]; //for length
int all;
int p[maxn],sum;//sub
int w[maxn]; //fft

vector<int> edge[maxn];
int sz[maxn];
bool mark[maxn];
int minweight,root;
void dfs1(int x,int fa,int n) {
    int weight=0; sz[x]=1;
    for (int v:edge[x]) {
        if (v==fa||mark[v]) continue;
        dfs1(v,x,n); sz[x]+=sz[v];
        weight=max(weight,sz[v]);
    } weight=max(weight,n-sz[x]);
    if (weight<minweight) root=x,minweight=weight;
}
int dfs2(int x,int fa,int dep) {//return maxdep
    sz[x]=1; A[dep]+=p[x]; int ret=dep;
    for (int v:edge[x]) {
        if (v==fa||mark[v]) continue;
        ret=max(ret,dfs2(v,x,dep+1));
        sz[x]+=sz[v];
    } return ret;
} ll ans;
void calc(int x){
    int maxdep=dfs2(x,0,0),i;
    NTT::solve(A,maxdep+1);
    // FOR(i,0,maxdep*2) printf("%lld ",A[i]); puts("<- maxdep");
    FOR(i,0,maxdep*2) add_(ans,A[i]*w[i]%M);
    FOR(i,0,maxdep*2) A[i]=0;//clean
    for (int v:edge[x]) {
        if (mark[v]) continue;
        maxdep=dfs2(v,x,1);
        NTT::solve(A,maxdep+1);
        FOR(i,2,maxdep*2) add_(ans,M-A[i]*w[i]%M);
        FOR(i,2,maxdep*2) A[i]=0;//clean
    }
}
void dfs3(int x) {
    debug("dfs3:%d\n",x);
    calc(x); mark[x]=1;
    for (int v:edge[x]) {
        if (mark[v]) continue;
        minweight=sz[v];
        dfs1(v,0,sz[v]);
        dfs3(root);//next_root
    }
}

int main() {
    int n; int i; scanf("%d",&n);
    FOR(i,1,n) scanf("%d",&p[i]),add_(sum,p[i]);
    FOR(i,0,n-1) scanf("%d",&w[i]);
    FOR(i,1,n-1) {
        int u,v; scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    } minweight=n;
    dfs1(1,0,n); dfs3(root);
    printf("%lld\n",ans*powMM(powMM(sum,M-2),2)%M);
}
/*
3 2 2 0 0 0 0 0 0 0
*/