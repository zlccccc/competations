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
typedef long long LL;
typedef long long ll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e5+7;
const double pi=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
    T ret=1;
    for (; b; b>>=1ll,a=(LL)a*a%M)
        if (b&1) ret=(LL)ret*a%M;
    return ret;
}

typedef pair<int,int> pii;
int A[maxn];
vector<pii> edge[maxn];
int dep[maxn];
ll len[maxn],dp_add[maxn],dp[maxn],dp_down[maxn];
int fa[maxn][20];
void dfs_up(int x,int father,int depth,ll length){
    len[x]=length; dep[x]=depth; dp[x]=0;
    int i;
    fa[x][0]=father; rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
    for (auto now:edge[x]) if (now.first!=father){
        int v=now.first;
        dfs_up(v,x,depth+1,length+now.second);
        dp_add[v]=max(0ll,dp[v]-now.second*2+A[v]);
        dp[x]+=dp_add[v];
    }
}
ll sum_dp[maxn],sum_dp_add[maxn],sum_A[maxn];
void dfs_down(int x,int fa){
    sum_A[x]=A[x]+sum_A[fa];
    sum_dp[x]=dp[x]+sum_dp[fa];
    sum_dp_add[x]=dp_add[x]+sum_dp_add[fa];
    for (auto now:edge[x]) if (now.first!=fa){
        int v=now.first;
        dp_down[v]=max(0ll,dp_down[x]+A[x]+dp[x]-dp_add[v]-now.second*2);
        dfs_down(v,x);
    }
}
inline int lca(int x,int y){
    int i;
    if (dep[x]<dep[y]) swap(x,y);
    rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
    if (x==y) return x;
    rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
int TaskA(){
    int n,q,i;
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n-1){
        int u,v,len;
        scanf("%d%d%d",&u,&v,&len);
        edge[u].push_back(make_pair(v,len));
        edge[v].push_back(make_pair(u,len));
    }dfs_up(1,0,0,0); dfs_down(1,0);
//    FOR(i,1,n) debug("%-5I64d ",dp[i]);deputs(" <- dp");
//    FOR(i,1,n) debug("%-5I64d ",dp_add[i]);deputs(" <- add");
//    FOR(i,1,n) debug("%-5I64d ",dp_down[i]);deputs(" <- down");
    FOR(i,1,q){
        int u,v;
        scanf("%d%d",&u,&v);
        int f=lca(u,v);
        ll ans=0;
        ans=sum_A[v]+sum_A[u]-sum_A[f]-sum_A[fa[f][0]];
        ans-=len[v]+len[u]-len[f]*2;
//        debug("first-ans= %I64d\n",ans);
        ans+=sum_dp[v]+sum_dp[u]-sum_dp[f]-sum_dp[fa[f][0]];
        ans-=sum_dp_add[v]+sum_dp_add[u]-sum_dp_add[f]*2;
        ans+=dp_down[f];
        printf("%I64d\n",ans);
    }return 0;
}
int main() {
	int startTime=clock();
	//initialize
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
//	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
*/
