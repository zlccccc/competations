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

vector<int> edge[maxn];
int fa[maxn],son[maxn],sz[maxn],top[maxn],id[maxn],dep[maxn];
int revid[maxn];
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
	top[u]=x;id[u]=++tot;revid[tot]=u;
	if (son[u]) dfs2(son[u],x);
	for(int v:edge[u]){
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
int lca(int x,int y){
	while(top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	return x;
}
int lca_k[maxn];
set<int> pos[maxn];  
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
	int k;
	scanf("%d",&k);
	FOR(i,1,k){
		int c;
		scanf("%d",&c);
		REP(j,c){
			int u;
			scanf("%d",&u);
			if (lca_k[i]==0) lca_k[i]=u;
			else lca_k[i]=lca(lca_k[i],u);
			pos[i].insert(id[u]);//dfs–Ú
		}
	}
	int q;
	scanf("%d",&q);
	while (q--){
		int u,c;
		scanf("%d%d",&u,&c);
		int ans=INF,pre=0,suf=0,toplca=0;
		REP(j,c){
			scanf("%d",&k);
			if (toplca==0) toplca=lca_k[k];
			else toplca=lca(toplca,lca_k[k]);
			int nowlca=lca(lca_k[k],u);
			ans=min(ans,dep[lca_k[k]]+dep[u]-2*dep[nowlca]);
			set<int>::iterator it=pos[k].upper_bound(id[u]);
			int nowsuf=0,nowpre=0;
			if (it!=pos[k].end()) nowsuf=*it;
			if (it!=pos[k].begin()) it--,nowpre=*it;
			if (nowsuf&&(!suf||suf>nowsuf)) suf=nowsuf;
			if (nowpre&&(!pre||pre<nowpre)) pre=nowpre;
//			printf("now : pre,suf=%d %d\n",nowpre,nowsuf);
			if (nowlca!=u&&nowlca==lca_k[k]){
				if (nowpre) ans=min(ans,dep[u]-dep[lca(u,revid[nowpre])]);
				if (nowsuf) ans=min(ans,dep[u]-dep[lca(u,revid[nowsuf])]);
			}
		}
//		printf("final : pre,suf=%d %d,id=%d %d\n",pre,suf,revid[pre],revid[suf]);
		int nowlca=lca(u,toplca);
		ans=min(ans,dep[u]+dep[toplca]-2*dep[nowlca]);
		if (nowlca!=u&&nowlca==toplca){
			if (pre) ans=min(ans,dep[u]-dep[lca(u,revid[pre])]);
			if (suf) ans=min(ans,dep[u]-dep[lca(u,revid[suf])]);
		}
		printf("%d\n",ans);
	}
}
/*
*/
