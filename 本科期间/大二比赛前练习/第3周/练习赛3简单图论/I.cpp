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
const LL maxn=3e5+7;
const double eps=0.00000001;
//const LL INF=0x3f3f3f3f;
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
//struct
struct node{
	int sum,max;
	node(int S=0,int M=-1):sum(S),max(M){}
};
node merge(node A,node B){
	return node(A.sum+B.sum,max(A.max,B.max));
}
node min(node A,node B){
	if (A.max==-1) return B;
	if (B.max==-1) return A;
	if (A.sum==B.sum) return A.max>B.max?A:B;
	else return A.sum<B.sum?A:B;
}
//seg 
node VAL[maxn];
node A[maxn];
void build(int x,int l,int r){
//	printf("%d %d %d\n",x,l,r);
	if (l==r){
		VAL[x]=A[l];
		return;
	}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	VAL[x]=merge(VAL[x<<1],VAL[x<<1|1]);
}
node queryVAL(int x,int l,int r,int L,int R){
//	printf("%d %d %d %d %d\n",x,l,r,L,R);
	if (l<=L&&R<=r) return VAL[x];
	int mid=(L+R)/2;
	node ret;
	if (mid>=l) ret=merge(ret,queryVAL(x<<1,l,r,L,mid));
	if (r>mid) ret=merge(ret,queryVAL(x<<1|1,l,r,mid+1,R));
	return ret;
}
//dfs
vector<int> edge[maxn];
int val[maxn];
node up[maxn],down[maxn];
int fa[maxn];
node dfs(int x,node nowMAX){
	node nowval=node(val[x],val[x]);
	nowMAX=merge(nowval,nowMAX);
	node ret;
	up[x]=nowMAX;
	for (int v:edge[x]){
		if (v==fa[x]) continue;
		node sonMAX=dfs(v,nowMAX);
		ret=min(ret,merge(nowval,sonMAX));
	}
	if (ret.max==-1) ret=nowval;
	down[x]=ret;
	return ret;
}
//Ê÷ÆÊ 
int son[maxn],sz[maxn],top[maxn],id[maxn],dep[maxn];
int tot;
void dfs1(int u,int depth){
	int v,mx=-1;
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
node query(int x,int y){
	node ret;
	while (top[x]!=top[y]){
//		printf("%d %d %d %d dep=%d %d\n",x,y,top[x],top[y],dep[top[x]],dep[top[y]]);
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		ret=merge(ret,queryVAL(1,id[top[x]],id[x],1,tot));
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	if (son[x]) ret=merge(ret,queryVAL(1,id[son[x]],id[y],1,tot));
	return ret;
}
int n,m,T;
int i;
int u,v;
int main()
{
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		FOR(i,2,n) scanf("%d",&fa[i]),edge[fa[i]].push_back(i);
		FOR(i,1,n) scanf("%d",&val[i]);
		dfs(1,node());
		dfs1(1,0);
		dfs2(1,1);
		FOR(i,1,n) A[id[i]]=node(val[i],val[i]);
		build(1,1,tot);
		while (m--){
			scanf("%d%d",&u,&v);
			node ans=query(u,v);
			ans=min(ans,merge(up[u],down[v]));
			ans=min(ans,merge(up[v],down[u]));
			printf("%d %d\n",ans.sum,ans.max);
		}
		FOR(i,1,n) edge[i].clear();
	}
}
/*
*/
