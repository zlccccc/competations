#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=5e5+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}

vector<int> edge[2][maxn];
int n,m;
int i;
int u,v;
int fa[maxn];//并查集的 
int father[2][maxn];
inline int getfather(int x){
	if (fa[x]==x) return x;
	return fa[x]=getfather(fa[x]);
}
void dfs1(int mark,int x,int f){
	father[mark][x]=f;
	for (int v:edge[mark][x]) if (v!=f) dfs1(mark,v,x);
}
void dfs2(int x,int f){
	for (int v:edge[0][x])if (v!=f){
		dfs2(v,x);
		if (v!=father[1][x]&&x!=father[1][v]){
			printf("%d %d %d %d\n",v,x,getfather(v),father[1][getfather(v)]);
		}
	}
}
int cnt;
int main()
{
	scanf("%d",&n);
	REP(i,n-1){
		scanf("%d%d",&u,&v);
		edge[0][u].push_back(v);
		edge[0][v].push_back(u);
	}
	REP(i,n-1){
		scanf("%d%d",&u,&v);
		edge[1][u].push_back(v);
		edge[1][v].push_back(u);
	}
	dfs1(1,1,0);
	dfs1(0,1,0);
	FOR(i,1,n) fa[i]=i;
	FOR(i,1,n){
		int v=father[1][i];
		if (v==father[0][i]||i==father[0][v])
			fa[i]=v;
		else cnt++;
	}
	printf("%d\n",cnt);
	dfs2(1,0);
	return 0;
}
/*
*/
