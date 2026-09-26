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
#include <unordered_map>
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
const LL maxn=5e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

LL sum[maxn<<2],add[maxn<<2],Size[maxn<<2];
void change(int x,int val){
	sum[x]+=val*Size[x];
	add[x]+=val;
}
void pushdown(int x){
	if (add[x]){
		change(x<<1,add[x]);
		change(x<<1|1,add[x]);
		add[x]=0;
	}
}
void build(int x,int L,int R){
	Size[x]=R-L+1;
	if (L==R) return;
	int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
}
void Update(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r){change(x,1);return;}
	int mid=(L+R)/2;
	pushdown(x);
	if (mid>=l) Update(x<<1,l,r,L,mid);
	if (r>mid) Update(x<<1|1,l,r,mid+1,R);
	sum[x]=sum[x<<1]+sum[x<<1|1];
}
LL Query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) return sum[x];
	int mid=(L+R)/2;
	LL ret=0;
	pushdown(x);
	if (mid>=l) ret+=Query(x<<1,l,r,L,mid);
	if (r>mid) ret+=Query(x<<1|1,l,r,mid+1,R);
	sum[x]=sum[x<<1]+sum[x<<1|1];
	return ret;
}
vector<int> edge[maxn];
int fa[maxn],son[maxn],sz[maxn],top[maxn],id[maxn],dep[maxn];
int tot;
void dfs1(int u,int depth){
	int v,i,mx=-1;
	sz[u]=1;dep[u]=depth;son[u]=0;
	REP(i,edge[u].size()){
		v=edge[u][i];
		dfs1(v,depth+1);
		sz[u]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[u]=v;
	}
}
void dfs2(int u,int x){
	int v,i;
	top[u]=x;id[u]=++tot;
	if (son[u]) dfs2(son[u],x);
	REP(i,edge[u].size()){
		v=edge[u][i];
		if (v==son[u]) continue;
		dfs2(v,v);
	}
}
int n;
void update(int x){
	while (x){
//		printf("U:%d %d\n",id[top[x]],id[x]);
		Update(1,id[top[x]],id[x],1,n);
		x=fa[top[x]];
	}
}
LL query(int x){
	LL ret=0;
	while (x){
//		printf("Q:%d %d\n",id[top[x]],id[x]);
		ret+=Query(1,id[top[x]],id[x],1,n);
		x=fa[top[x]];
	}
	return ret; 
} 
vector<int> now[maxn];
LL ans[maxn];
void dfs(int x,int depth){
	now[depth].push_back(x);
	for (int v:edge[x]) dfs(v,depth+1);
}
int root;
int main(){
	int i,j;
	scanf("%d",&n);
	FOR(i,1,n){
		int f;
		scanf("%d",&fa[i]);
		if (fa[i]==0) root=i;
		else edge[fa[i]].push_back(i);
	}
	dfs(root,0);
	dfs1(root,0);
	dfs2(root,root);
	build(1,1,n);
	FOR(i,1,n){
		for (int v:now[i]) update(fa[v]); 
		for (int v:now[i]) ans[v]=query(v);
	}
	FOR(i,1,n) printf("%I64d ",ans[i]);
}
/*
4
0 1 2 1
*/
