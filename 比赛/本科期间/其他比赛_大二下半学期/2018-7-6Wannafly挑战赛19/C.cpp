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
const LL maxn=5e4+7;
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

int dp[50007][1027];
int A[maxn];
vector<int> edge[maxn];
ll Ans[17];
int CNT[maxn];
void dfs1(int x,int fa){
    int i;
    FOR(i,1,1024) dp[x][i|(1<<(A[x]-1))]+=dp[fa][i];
    dp[x][1<<(A[x]-1)]++;
//    FOR(i,1,7) printf("%d ",dp[x][i]); printf(" <- %d\n",x);
    FOR(i,1,1024) Ans[CNT[i]]+=dp[x][i];
    for (int v:edge[x]) if (v!=fa){
        dfs1(v,x);
        rFOR(i,1,1024) dp[x][(1<<(A[v]-1))|i]-=dp[x][i];
        FOR(i,1,1024) dp[x][(1<<(A[x]-1))|i]+=dp[v][i];
    }
}
void dfs2(int x,int fa){
    int i;
    FOR(i,1,1024) dp[x][i]=0;
    FOR(i,1,1024) dp[x][i|(1<<(A[x]-1))]+=dp[fa][i];
    reverse(edge[x].begin(),edge[x].end());
    for (int v:edge[x]) if (v!=fa){
        dfs2(v,x);
        rFOR(i,1,1024) dp[x][(1<<(A[v]-1))|i]-=dp[x][i];
        FOR(i,1,1024) dp[x][(1<<(A[x]-1))|i]+=dp[v][i];
    }
//    FOR(i,1,7) printf("%d ",dp[x][i]); printf(" <- %d\n",x);
    dp[x][1<<(A[x]-1)]++;
    FOR(i,1,1024) Ans[CNT[i]]+=dp[x][i];
}
int TaskA(){
    int n,m,x,y,z;
    int i,j,k;
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%d",&A[i]);
    FOR(i,1,n-1){
        int u,v;
        scanf("%d%d",&u,&v);
        edge[u].push_back(v);
        edge[v].push_back(u);
    }dfs1(1,0);
//    FOR(i,1,n) {FOR(j,1,(1<<(k-1))) printf("%d ",dp[i][j]); puts("");}
//    dfs2(1,0);
//    FOR(i,1,k) printf("%lld\n",Ans[i]);
    ll ans=0;
    FOR(i,1,k) ans=(ans+Ans[i]*powMM(131,i))%M;
    printf("%lld\n",ans);
    return 0;
}
void initialize(){
    int i=0;
    FOR(i,1,1024) CNT[i]=CNT[i>>1]+(i&1);
}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	int T=1;
//	scanf("%d",&T);
	startTime=clock();
	while (T--) TaskA();
	debug("/--- computeTime: %ld milliseconds ---/\n",clock()-startTime);
}
/*
*/
