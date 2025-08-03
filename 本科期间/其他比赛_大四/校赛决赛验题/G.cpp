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
const LL maxn=1e5+107;
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

//树分治会T吧...
int m;
ll ans=0;
int A[207];
vector<pii> edge[maxn];
int pl[maxn][207],pr[maxn][207];
int tl[207],tr[207];
void dfs(int x,int fa) {
    int i;
    pl[x][0]++; pr[x][m+1]++;
    for (pii p:edge[x]) {
        int v=p.first,w=p.second;
        if (v==fa) continue;
        dfs(v,x);
        FOR(i,0,m+1) tl[i]=tr[i]=0;
        FOR(i,0,m  ) tl[i+(A[i+1]==w)]+=pl[v][i];//edge
        FOR(i,1,m+1) tr[i-(A[i-1]==w)]+=pr[v][i];//edge,from_r
        ll now=0;
        rFOR(i,0,m+1) {
            now+=tl[i]; ans-=now*tr[i+1];
            pl[x][i]+=tl[i]; pr[x][i]+=tr[i];
        }
        // printf(" (tr): %d %d:\n",x,v);
        // printf("  "); FOR(i,0,m+1) printf("%d ",tl[i]); puts("<- tl");
        // printf("  "); FOR(i,0,m+1) printf("%d ",tr[i]); puts("<- tr");
    } ll now=0;
    rFOR(i,0,m+1) {
        now+=pl[x][i]; ans+=now*pr[x][i+1];
        // printf("%d %d\n",now,pr[x][i+1]);
    }
    // printf("dfs: %d:\n",x);
    // FOR(i,0,m+1) printf("%d ",pl[x][i]); puts("<- pl");
    // FOR(i,0,m+1) printf("%d ",pr[x][i]); puts("<- pr");
}
int main() {
    int n,i;
    scanf("%d%d",&n,&m);
    FOR(i,1,n-1) {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        edge[u].push_back(make_pair(v,w));
        edge[v].push_back(make_pair(u,w));
    } FOR(i,1,m) scanf("%d",&A[i]);
    dfs(1,0);
    printf("%lld\n",ans);
}
/*
4
10 3 2
5 3 1
15 5 3
29 4 5
*/