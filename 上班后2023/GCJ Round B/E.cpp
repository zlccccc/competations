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
#include <unordered_set>
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

ll ALLIN[maxn],CIRIN[maxn],OUT[maxn]; // OUT的值是固定的!
ll current_ans;
// 注意edge一定要加上; 而且一定要dfs
int A[maxn];
vector<int> cir,edge[maxn];
int vis[maxn];
int in[maxn],out[maxn],dtot,ctot;
void dfs(int x,int fa) { // must dfs!
    vis[x]=1;
    for (int v:edge[x]) dfs(v,x);
    current_ans+=max(0ll,OUT[x]-ALLIN[x]);
    ALLIN[fa]+=OUT[x];
}
void solve(int x) {
    cir.clear(); ctot++;
    while (A[x]&&!vis[A[x]]) x=A[x],vis[x]=1;
    while (A[x]&&vis[A[x]]==1) {
        vis[A[x]]=2; cir.push_back(x); x=A[x];
    }
    for (int v:cir) for (int y:edge[v]) if (vis[y]!=2) dfs(y,v);
    for (int v:cir) CIRIN[A[v]]+=OUT[v];
    // for (int v:cir) {
    //     printf("c=%d; v=%d; allin=%lld; cirin=%lld; out=%lld\n",ctot,v,ALLIN[v],CIRIN[v],OUT[v]);
    // }
    ll all=0;
    for (int v:cir) all+=max(0ll,OUT[v]-ALLIN[v]-CIRIN[v]);
    ll curr=INFF;
    for (int v:cir) {
        curr=min(curr,all-max(0ll,OUT[v]-ALLIN[v]-CIRIN[v])+max(0ll,OUT[v]-ALLIN[v]));
    }
    current_ans+=curr;
}

int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n;
        scanf("%d",&n);
        dtot=ctot=0; current_ans=0;
        FOR_(i,1,n) vis[i]=0;
        FOR_(i,1,n) ALLIN[i]=CIRIN[i]=0; current_ans=0;
        FOR_(i,1,n) edge[i].clear();
        FOR_(i,1,n) scanf("%d",&A[i]);
        FOR_(i,1,n) scanf("%lld",&OUT[i]);
        FOR_(i,1,n) edge[A[i]].push_back(i);
        FOR_(i,1,n) if (!vis[i]) solve(i);
        printf("Case #%d: ",_);
        printf("%lld\n",current_ans);
    }

}
/*
*/