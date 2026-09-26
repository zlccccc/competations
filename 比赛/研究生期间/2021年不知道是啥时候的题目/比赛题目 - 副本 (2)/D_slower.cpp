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
const LL maxn=107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,ull k=64) {ull i; REP(i,k) debug("%d",(int)((x>>i)&1)); putchar(' ');}
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

vector<pii> edge[1507];
int dis[1507][1507];
void dfs(int x,int fa,ll dist,int dis[]) {
    dis[x]=dist;
    for (auto e:edge[x]) if (e.first!=fa)
        dfs(e.first,x,dist+e.second,dis);
}
ll cost[1807][1807],f[1807][1807];
int pos[1807][1807];
int A[1807];//form prefix
void add(int n,int x) {
    //add from x
    int i,k; A[n]=x;
    FOR(i,1,n) cost[i][n]=dis[x][A[i]];
    rFOR(i,1,n-1) cost[i][n]+=cost[i+1][n];;
    FOR(i,1,n-1) cost[i][n]+=cost[i][n-1];;
    f[n][n]=cost[n][n]; pos[n][n]=n;
    rFOR(i,1,n-1) {//f[i->n]
        f[i][n]=INFF;
        FOR(k,pos[i][n-1],min(n-1,pos[i+1][n])) {
        // FOR(k,i,n-1) {
            // ll Cost=cost[1][n]-cost[i][k]-cost[k+1][n];
            ll Cost=cost[i][n];
            ll now=Cost+f[i][k]+f[k+1][n];
            if (now<f[i][n]) f[i][n]=now,pos[i][n]=k;
        }
    }
    // FOR(i,1,n) printf("%d ",A[i]); puts("<- A");
    // FOR(i,1,n) printf("%lld ",cost[i][n]); puts("<- Pre-cost");
    // int j;
    // FOR(i,1,n) FOR(j,i,n) FOR(k,j,n) cost[i][n]-=dis[A[j]][A[k]];
    // FOR(i,1,n) printf("%lld ",cost[i][n]); puts("<- check cost");
    // FOR(i,1,n) FOR(j,i,n) FOR(k,j,n) cost[i][n]+=dis[A[j]][A[k]];
    // FOR(i,1,n) printf("%lld ",f[i][n]); puts("<- f");
}
ll ans[307];
vector<pair<int,pii> > Q[307];
void solve(int x,int fa,int n) {
    for (auto e:edge[x]) {
        add(n,e.second);
        ans[e.first]=f[1][n];
        solve(e.first,x,n+1);//next;
    }
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,m,r,i;
        scanf("%d%d%d",&m,&n,&r);
        FOR(i,1,m) {
            int p,l; scanf("%d%d",&p,&l);
            edge[p].push_back(make_pair(i,l));
            edge[i].push_back(make_pair(p,l));
        }
        FOR(i,0,m) dfs(i,-1,0,dis[i]);
        // int j; FOR(i,0,m) FOR(j,0,m) printf("%d%c",dis[i][j]," \n"[j==m]);
        FOR(i,0,m) edge[i].clear();
        FOR(i,1,n) scanf("%d",&A[i]);
        FOR(i,1,n) add(i,A[i]);
        FOR(i,1,r) {
            int q,x; scanf("%d%d",&q,&x);
            edge[q].push_back(make_pair(i,x));
        } ans[0]=f[1][n];
        solve(0,-1,n+1);
        FOR(i,0,r) edge[i].clear();
        FOR(i,0,r) printf("%lld\n",ans[i]*2);
    }
}
/*
*/