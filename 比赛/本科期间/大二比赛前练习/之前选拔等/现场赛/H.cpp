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
const LL maxn=1e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const double eps=0.000000001;
const double pi=acos(-1);
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b){return a>0?a:-a;}


vector<int> edge[maxn];
int fat[maxn];
inline int getfa(int x){
	if (fat[x]==x) return x;
	return fat[x]=getfa(fat[x]);
}
int fa[maxn],son[maxn],sz[maxn],top[maxn],id[maxn],dep[maxn],tot;
void dfs1(int u,int from,int depth){//求LCS...竟然没板子 
	int v,i,mx=-1;
	sz[u]=1;fa[u]=from;dep[u]=depth;son[u]=0;
	REP(i,edge[u].size()){
		v=edge[u][i];
		if (v==from) continue;
		dfs1(v,u,depth+1);
		sz[u]+=sz[v];
		if (sz[v]>mx) son[u]=v,mx=sz[v];
	}
}
void dfs2(int u,int x){
	int v,i;
	top[u]=x;id[u]=++tot;
	if (son[u]) dfs2(son[u],x);
	REP(i,edge[u].size()){
		v=edge[u][i];
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
inline int query(int x,int y){
	int ret;
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	return x;
}
int n,m,q;
int i;
int u,v;
int k[maxn],qu[maxn],qv[maxn];
void solve(){
	tot=0;
	scanf("%d%d%d",&n,&m,&q);
	FOR(i,1,n) fat[i]=i;
	REP(i,m){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
		fat[v]=u;
	}
	REP(i,q){
		scanf("%d%d%d",&k[i],&qu[i],&qv[i]);
		if (k[i]==1) {
//			printf("%d %d\n",getfa(qu[i]),getfa(qv[i]));
			if (getfa(qu[i])!=getfa(qv[i])) k[i]=-1;
		}else{
			edge[qu[i]].push_back(qv[i]);
			edge[qv[i]].push_back(qu[i]);
			fat[qv[i]]=qu[i];
			k[i]=-2;
		}
	}
	FOR(i,1,n) if (fat[i]==i){
		dfs1(i,0,1);
		dfs2(i,i);
	}
	REP(i,q){
		if (k[i]==1)
			k[i]=query(qu[i],qv[i]);
	}
	FOR(i,1,n) edge[i].clear();
	REP(i,q) if (k[i]!=-2) printf("%d\n",k[i]);
}
int T;
int main(){
	scanf("%d",&T);
	while (T--) solve();
}
