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
const LL M=1e9+7;
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

ll A[maxn];
int B[maxn];
vector<int> edge[maxn];
int link[maxn];//after x->y
ll sum[maxn],ans;
pii L[maxn],R[maxn];
pii merge(pii &x,pii &y) {
    if (x.first==0) return y;
    if (y.first==0) return x;
    link[x.second]=y.first;
    // printf("merge %d->%d\n",x.second,y.first);
    return make_pair(x.first,y.second);
}
void dfs(int x) {
    sum[x]=A[x];
    L[x]=make_pair(x,x);
    R[x]=make_pair(0,0);
    for (int v:edge[x]) {
        dfs(v); R[x]=merge(R[v],R[x]);
        if (sum[v]>=0) L[x]=merge(L[v],L[x]),sum[x]+=sum[v];
        else R[x]=merge(L[v],R[x]);
    } ans+=sum[x];
}
ll noww=0;
int main() {
    int i;
    int n; scanf("%d",&n);
    FOR(i,1,n) scanf("%lld",&A[i]);
    FOR(i,1,n) {
        scanf("%d",&B[i]);
        if (B[i]!=-1) edge[B[i]].push_back(i);
        // printf("p[%d]=%d\n",B[i],i);
    } pii now=make_pair(0,0);
    FOR(i,1,n) if (B[i]==-1) {
        dfs(i);
        now=merge(now,L[i]);
        now=merge(now,R[i]);
        // printf(" -- %d %d, %d %d\n",L[i].first,L[i].second,R[i].first,R[i].second);
    } 
    printf("%lld\n",ans);
    // FOR(i,0,n) printf("%d ",link[i]); puts("<- link");
    for (int v=now.first;v;v=link[v]) {
        printf("%d ",v); if (B[v]!=-1) A[B[v]]+=A[v]; ans-=A[v];
    }
    // printf("ans=%lld\n",ans);
}
/*
7
7
23
31
36
44
100
258
*/