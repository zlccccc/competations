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
const LL maxn=1.2e6+107;
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


vector<int> edge[maxn];
int dis[maxn];
void dfs(int x,int fa,int dep){
    dis[dep]++;
    for (int v:edge[x]) if (v!=fa) dfs(v,x,dep+1);
}
int U[maxn],V[maxn];
int Now[107][107];
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int n,k,i,x,y;
        scanf("%d%d",&n,&k);
        FOR(i,1,n) edge[i].clear();
        FOR(i,1,n-1) {
            scanf("%d%d",&U[i],&V[i]);
            edge[U[i]].push_back(V[i]);
            edge[V[i]].push_back(U[i]);
        } int ans=0;
        FOR(i,1,n) {
            FOR(x,1,n) FOR(y,1,k) Now[x][y]=0;
            FOR(x,1,n) Now[x][0]=1;
            for (int v:edge[i]) {
                FOR(x,1,n) dis[x]=0;
                dfs(v,i,1);
                // FOR(x,1,n) printf("%d ",dis[x]); puts("<- dis");
                FOR(x,1,n) if (dis[x])
                    rFOR(y,1,k) add_(Now[x][y],(ll)Now[x][y-1]*dis[x]%M);
            } FOR(x,1,n) add_(ans,Now[x][k]);
            // FOR(x,1,n) printf("%d ",Now[1][x]); puts("<- Now");
        }
        FOR(i,1,n-1) {//edges
            FOR(x,1,n) FOR(y,1,k) Now[x][y]=0;
            FOR(x,1,n) Now[x][0]=1;
            FOR(x,1,n) dis[x]=0;
            dfs(U[i],V[i],1);
            FOR(x,1,n) if (dis[x])
                rFOR(y,1,k) add_(Now[x][y],(ll)Now[x][y-1]*dis[x]%M);
            FOR(x,1,n) dis[x]=0;
            dfs(V[i],U[i],1);
            FOR(x,1,n) if (dis[x])
                rFOR(y,1,k) add_(Now[x][y],(ll)Now[x][y-1]*dis[x]%M);
            FOR(x,1,n) add_(ans,Now[x][k]);
        }
        printf("%d\n",ans);
    }
}
/*
8
4 4 2
10 10 10
10 11 10
11 10 10
*/