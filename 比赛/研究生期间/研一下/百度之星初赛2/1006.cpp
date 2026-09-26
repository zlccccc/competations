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
const LL M=998244353;
const LL maxn=1e6+107;
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

int root;
vector<int> edge[maxn];
int depth[maxn],maxdep;
int CNT[maxn],cnt;
void dfs(int x,int fa,int dep){
    if (maxdep==dep) cnt++; max_(depth[x],dep);
    if (dep>maxdep) root=x,maxdep=dep; CNT[dep]++;
    for (int v:edge[x]) if (v!=fa) dfs(v,x,dep+1);
}
int main() {
    int T,_; T=1;
    scanf("%d",&T);
    FOR(_,1,T){
        int i,n,k;
        scanf("%d",&n);
        FOR(i,1,n) edge[i].clear();
        FOR(i,1,n) depth[i]=0;
        FOR(i,2,n) {
            int u,v;
            scanf("%d%d",&u,&v);
            edge[u].push_back(v);
            edge[v].push_back(u);
        } root=1;
        maxdep=0; dfs(root,0,1);
        maxdep=0; dfs(root,0,1);
        maxdep=0; dfs(root,0,1); cnt=0;
        int ans=0;
        // FOR(i,1,n) printf("%d ",depth[i]); puts("<- depth");
        FOR(i,1,n) if (depth[i]==maxdep) {
            FOR(k,1,maxdep) CNT[k]=0;
            dfs(i,0,1);
            int mul=1;
            FOR(k,1,maxdep) mul_(mul,CNT[k]);
            add_(ans,mul);
        }
        // printf("ans=%d\n",ans);
        add_(ans,M-cnt*powMM(2,M-2)%M);
        printf("%d %d\n",maxdep,ans);
    }
}
/*
10
7
1 2
1 3
1 4
2 5
3 6
4 7
6
1 2
1 3
1 4
2 5
3 6
10
1 2
2 3
3 4
4 5
5 6
4 7
7 8
3 9
9 10
*/