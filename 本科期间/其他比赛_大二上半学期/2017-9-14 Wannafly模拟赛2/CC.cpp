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
const LL maxn=5e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//nlog^2n空间被卡了.. 
set<int> have[maxn*4];
void Update(int x,int l,int r,int val,int L,int R){//先不改成LCA 
//	printf("Update:%d %d->%d %d %d %d\n",x, l, r, val, L, R);
	if (have[x].count(val)) return;
	if (l<=L&&R<=r){
		have[x].insert(val);
		return;
	}
	int mid=(L+R)/2;
	if (mid>=l) Update(x<<1,l,r,val,L,mid);
	if (r>mid) Update(x<<1|1,l,r,val,mid+1,R);
}
int Query(int x,int pos,int val,int L,int R){
	if (have[x].count(val)) return 1;
	if (L==R) return 0;
	int mid=(L+R)/2;
	if (mid>=pos) return Query(x<<1,pos,val,L,mid);
	return Query(x<<1|1,pos,val,mid+1,R);
}
vector<int> edge[maxn];
int fa[maxn],son[maxn],sz[maxn],top[maxn],id[maxn],dep[maxn];
int tot;
void dfs1(int x,int from,int depth){
	int i,mx=-1;
	sz[x]=1;fa[x]=from;dep[x]=depth;son[x]=0;
	for (int v:edge[x]){
		if (v==from) continue;
		dfs1(v,x,depth+1);
		sz[x]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[x]=v;
	}
}
void dfs2(int u,int x){
	top[u]=x;id[u]=++tot;
	if (son[u]) dfs2(son[u],x);
	for(int v:edge[u]){
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
void update(int x,int y,int val){
	while(top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		Update(1,id[top[x]],id[x],val,1,tot);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	Update(1,id[x],id[y],val,1,tot);
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	return x;
}
int FA[maxn][25];//加速 
void dfslcalen(int x){
	FA[x][0]=fa[x];
	int i;
	rep(i,1,25) FA[x][i]=FA[FA[x][i-1]][i-1];
	for (int v:edge[x]) if (v!=fa[x]) dfslcalen(v);
}
int lca_k[maxn];
int main(){
	int n;
	scanf("%d",&n);
	int i,j;
	REP(i,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs1(1,0,1);
//	FOR(i,1,n) printf("%d\n",top[i]);
	dfs2(1,1);
	dfslcalen(1);
	int k;
	scanf("%d",&k);
	FOR(i,1,k){
		int c;
		scanf("%d",&c);
		REP(j,c){
			int u;
			scanf("%d",&u);
			if (lca_k[i]==0) update(u,u,i),lca_k[i]=u;
			else update(u,lca_k[i],i),lca_k[i]=lca(lca_k[i],u);//刚刚这里写错了 
		}
	}
	int q;
	scanf("%d",&q);
	while (q--){
		int u,c;
		scanf("%d%d",&u,&c);
		int ans=INF,toplca=0,minlca=0;
		REP(j,c){
			scanf("%d",&k);
			if (toplca==0) toplca=lca_k[k];
			else toplca=lca(toplca,lca_k[k]);
			if (minlca==0) minlca=lca(u,lca_k[k]);
			else {
				int CMP=lca(u,lca_k[k]);
				if (dep[CMP]>dep[minlca]) minlca=CMP;
			}
			int nowlca=lca(lca_k[k],u);
			ans=min(ans,dep[u]+dep[lca_k[k]]-dep[nowlca]*2);//not
//			printf("nowlca=%d lca_k=%d\n",nowlca,lca_k[k]);
			if (nowlca==lca_k[k]){
				int x=u;
				rREP(i,25)
					if (FA[x][i]&& dep[FA[x][i]]>dep[nowlca] && !Query(1,id[FA[x][i]],k,1,tot)) x=FA[x][i];
//				printf("%d %d:%d",Query(1,id[x],k,1,tot));
				if (!Query(1,id[x],k,1,tot)) x=fa[x];
				ans=min(ans,dep[u]-dep[x]);
//				printf("nowlca : x=%d , change:%d\n",x,dep[u]-dep[x]);
			}
		}
//		printf("toplca,minlca=%d %d\n",toplca,minlca);
		ans=min(ans,dep[u]+dep[toplca]-2*dep[lca(u,toplca)]);
//		printf("change:%d\n",dep[u]+dep[toplca]-2*dep[lca(u,toplca)]);
		if (lca(toplca,minlca)==toplca) ans=min(ans,dep[u]-dep[minlca]);
//		if (lca(toplca,minlca)==toplca) printf("top,min : change:%d\n",dep[u]-dep[minlca]);
		printf("%d\n",ans);
	}
}
/*
*/
