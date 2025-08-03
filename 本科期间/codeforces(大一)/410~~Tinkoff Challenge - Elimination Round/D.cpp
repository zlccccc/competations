#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=82;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m,kk;
int i,j,k,t;
int edge[maxn][maxn];
int dp[maxn][maxn][maxn][maxn];//i~j   k offices 
int ans;
int u,v,c;
int dfs(int pos,int l,int r,int k){
	if (k==1) return 0;
	if (dp[pos][l][r][k]!=-1) return dp[pos][l][r][k];
	int ret=INF;
	int i;
	FOR(i,l,r) if (edge[pos][i]!=INF){
		if (i<pos) ret=min(ret,dfs(i,l,pos-1,k-1)+edge[pos][i]);
		if (i>pos) ret=min(ret,dfs(i,pos+1,r,k-1)+edge[pos][i]);
	}
//	printf("%d %d %d %d  %d\n",pos,l,r,k,ret);
	return dp[pos][l][r][k]=ret;
}
int main()
{
	scanf("%d%d",&n,&kk);
	scanf("%d",&m);
	FOR(i,1,n)
		FOR(j,1,n) edge[i][j]=INF;
	REP(i,m){
		scanf("%d%d%d",&u,&v,&c);
		edge[u][v]=min(edge[u][v],c);
	}
	memset(dp,-1,sizeof(dp));
	ans=INF;
	FOR(i,1,n)
		ans=min(ans,dfs(i,1,n,kk));
	if (ans!=INF) printf("%d",ans);
	else puts("-1");
}
