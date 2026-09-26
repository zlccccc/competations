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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct SEG{
	LL sum[maxn*4];
	void update(int x,int pos,int val,int l,int r){
		sum[x]+=val;
		if (l==r) return;
		int mid=(l+r)/2;
		if (mid>=pos) update(x<<1,pos,val,l,mid);
		else update(x<<1|1,pos,val,mid+1,r);
	}
	LL query(int x,int l,int r,int L,int R){
		if (l<=L&&R<=r) return sum[x];
		int mid=(L+R)/2;
		LL ret=0;
		if (mid>=l) ret+=query(x<<1,l,r,L,mid);
		if (r>mid) ret+=query(x<<1|1,l,r,mid+1,R);
		return ret;
	}
}T;
int fa[maxn],son[maxn],sz[maxn],top[maxn],id[maxn],dep[maxn];
int tot;
vector<int> edge[maxn];
void dfs1(int u,int depth){
	int v,i,mx=-1;
	sz[u]=1;dep[u]=depth;son[u]=0;
	for(int v:edge[u]){
		dfs1(v,depth+1);
		sz[u]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[u]=v;
	}
}
void dfs2(int u,int x){
	int v,i;
	top[u]=x;id[u]=++tot;
	if (son[u]) dfs2(son[u],x);
	for(int v:edge[u]){
		if (v==son[u]) continue;
		dfs2(v,v);
	}
}
inline LL query(int x,int y){
	int ret=0;
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		ret+=T.query(1,id[top[x]],id[x],1,tot);
//	printf("Query+:%d %d,%d\n",id[top[x]],id[x],ret);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	ret+=T.query(1,id[x],id[y],1,tot);
//	printf("Query+:%d %d,%d\n",id[x],id[y],ret);
	return ret;
}
LL under[maxn];
LL nowans[maxn];
struct node{int u,v,len;};
vector<node> add[maxn];
void dfs(int x){
	for (int v:edge[x]){
		dfs(v);
		under[x]+=nowans[v];
	}
	nowans[x]=under[x];
	for (auto now:add[x]){
		LL val=now.len;
//		printf("%d:%d %d %d\n",x,now.u,now.v,val);
		if (now.u!=x) val+=query(x,now.u);
		if (now.v!=x) val+=query(x,now.v);
		val+=under[x];
//		printf("%d:%d %d %d\n",x,now.u,now.v,val);
		nowans[x]=max(nowans[x],val);
	}
//	printf("Update:%d %d\n",id[x],under[x]-nowans[x]);
	T.update(1,id[x],under[x]-nowans[x],1,tot);//对上一级贡献
}
struct getlca{
	int fa[maxn][21];
	void dfs(int x,int depth){
		dep[x]=depth;
		for (int v:edge[x]) dfs(v,depth+1); 
	}
	int lca(int x,int y){
		int i;
		if (dep[x]<dep[y]) swap(x,y);
		rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
		if (x==y) return x;
		rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
}LCA;
int n,m;
int main(){
	int i,j;
	scanf("%d%d",&n,&m);
	FOR(i,2,n){
		scanf("%d",&fa[i]);
		edge[fa[i]].push_back(i);
		LCA.fa[i][0]=fa[i];
	}
	FOR(i,1,n) rep(j,1,20) LCA.fa[i][j]=LCA.fa[LCA.fa[i][j-1]][j-1];
	LCA.dfs(1,0);
	FOR(i,1,m){
		int u,v,len;
		scanf("%d%d%d",&u,&v,&len);
//		printf("%d:%d %d %d\n",LCA.lca(u,v),u,v,len);
		add[LCA.lca(u,v)].push_back(node{u,v,len});
	}
	dfs1(1,0);
	dfs2(1,1);
	dfs(1);
//	FOR(i,1,n) printf("%d %d\n",nowans[i],under[i]);
	printf("%d\n",nowans[1]);
}
/*
7 3
1 1 2 2 3 3
5 6 1
2 7 1
2 3 1

7 6
1 2 3 4 5 6
1 2 1
2 3 1
3 4 1
4 5 1
5 6 1
6 7 1
*/
