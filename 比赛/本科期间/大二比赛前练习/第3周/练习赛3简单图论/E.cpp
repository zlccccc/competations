#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}

vector<int> edge[maxn];
int fa[maxn];//Ëõµã 
inline int getfa(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfa(fa[x]);
}
int low[maxn],dfn[maxn];
bool vis[maxn];
int tot=0;
stack<int> S;
void tarjin(int x,int f){
	low[x]=dfn[x]=++tot;
	S.push(x);vis[x]=1;
	for (int v:edge[x]) if (v!=f){
		if (!dfn[v]){
			tarjin(v,x);
			low[x]=min(low[x],low[v]);
		}else if (vis[v]){
			low[x]=min(low[x],dfn[v]);
		}
	}
	if (low[x]==dfn[x]){
		while (1){
			int now=S.top();S.pop();
			vis[now]=0;
			int u=getfa(now),v=getfa(x);
			if (u!=v) fa[u]=v;
			if (now==x) break; 
		}
	}
}
int MX[maxn];
bool mark[maxn];
int dfs(int x){
	int ret=x;
	mark[x]=1;
	for (int v:edge[x]) if (!mark[v]){
		ret=max(ret,dfs(v));
	}
	MX[getfa(x)]=max(getfa(x),ret);
	return ret;
}
int n,m;
int i,j,k;
int U[maxn],V[maxn];
void solve(){
	scanf("%d%d",&n,&m);
	REP(i,m){
		scanf("%d%d",&U[i],&V[i]);
		edge[U[i]].push_back(V[i]);
		edge[V[i]].push_back(U[i]);
	}
	FOR(i,1,n) fa[i]=i;
	tarjin(1,0);
	dfs(n);
	REP(i,m){
		int x=getfa(U[i]),y=getfa(V[i]);
		if (x==y) puts("0 0");
		else printf("%d %d\n",min(MX[x],MX[y]),min(MX[x],MX[y])+1);
	}
	FOR(i,1,n) MX[i]=0;
	FOR(i,1,n) mark[i]=0;
	FOR(i,1,n) vector<int>().swap(edge[i]);
	FOR(i,1,n) low[i]=dfn[i]=0;
}
int main()
{
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
