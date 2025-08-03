#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=3e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;

vector<int> edge[maxn]; 
int sz[maxn],fa[maxn],son[maxn],top[maxn],dep[maxn],id[maxn];
int tot=0;
void dfs1(int u,int depth){
	int v,i,mx=-1;
	sz[u]=1;dep[u]=depth;son[u]=0;
	for (int v:edge[u]){
		dfs1(v,depth+1);
		sz[u]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[u]=v;
	}
}
void dfs2(int u,int x){
	int v,i;
	top[u]=x;id[u]=++tot;
	if (son[u]) dfs2(son[u],x);
	for (int v:edge[u]){
		if (v==son[u]) continue;
		dfs2(v,v);
	}
}
int LCA(int x,int y){
	if (x>n) return x;
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	return x;
}
int dp[maxn],pre[maxn];
int val[maxn];
int n,m;
int i,j,k;
int last;
int main()
{
	while (~scanf("%d%d",&n,&k)){
		FOR(i,1,n) scanf("%d",&val[i]);
		last=1;
		REP(i,n-1){
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		tot=0;
		dfs1(1,0);
		dfs2(1,1);
		memset(dp,0x3f,sizeof(dp));
		FOR(i,1,n) pre[i]=LCA()
		FOR(i,2,k){
			nowlca=
			FOR(j,1,n) if (dp[j-1]!=INF) dp[j]=min(dp[j],LCA(dp[j-1],val[i]));
			swap(pre,dp);
		}
		printf("%d",dp[k]);
		FOR(i,1,n) vector<int>().swap(edge[i]);
	}
	return 0;
}
/*
*/
