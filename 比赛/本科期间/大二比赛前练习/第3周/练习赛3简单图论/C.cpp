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
const LL maxn=1e6+7;
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

vector<LL> edge[maxn];
LL sz[maxn],fa[maxn],son[maxn],top[maxn],dep[maxn];
LL tot;
void dfs1(LL u,LL depth){
	LL mx=-1;
	sz[u]=1;dep[u]=depth;son[u]=0;
	for (LL v:edge[u]){
		if (v==fa[u]) continue;
		dfs1(v,depth+1);
		sz[u]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[u]=v;
	}
}
void dfs2(LL u,LL x){
	top[u]=x;
	if (son[u]) dfs2(son[u],x);
	for (LL v:edge[u]){
		if (v==son[u]||v==fa[u]) continue;
		dfs2(v,v);
	}
}
LL query(LL x,LL y){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	return x;
}
LL len(LL x,LL y){
	return dep[x]+dep[y]-dep[query(x,y)]*2;
}
LL maxlen,maxpos;
void dfs(LL x,LL fa,LL length){
//	prLLf("dfs:%d %d\n",x,length);
	if (length>maxlen) maxpos=x,maxlen=length; 
	for (LL v:edge[x]){
		if (v==fa) continue;
		dfs(v,x,length+1);
	}
}
LL n,m,q;
LL i,j;
LL ans[maxn];
LL u,v,d;
LL U,V;
LL A,B,C;
LL all;
void solve(){
	scanf("%d%d%d",&n,&q,&m);
	FOR(i,2,n){
		scanf("%d",&fa[i]);
		edge[fa[i]].push_back(i);
		edge[i].push_back(fa[i]);
	}
	tot=0;
	dfs1(1,0);
	dfs2(1,1);
	maxlen=0;
	dfs(1,0,0);U=maxpos;
	maxlen=0;
	dfs(U,0,0);V=maxpos;
	scanf("%lld%lld%lld%lld%lld%lld",&u,&v,&d,&A,&B,&C);
//	printf("%d %d\n",U,V);
	FOR(i,1,q){
		if (u==v) ans[i]=0;
		else if (len(u,v)>=d) ans[i]=1;
		else{
			LL Uu=len(U,u),Vu=len(V,u),Uv=len(U,v),Vv=len(V,v);
			if ((Uu>=d&&Uv>=d)||(Vu>=d&&Vv>=d)) ans[i]=2;
			else if ((Uu>=d&&Vv>=d)||(Uv>=d&&Vu>=d)) ans[i]=3;
			else ans[i]=-1;
		}
//		printf("ask:%d %d %d    %d\n",u,v,d,ans[i]);
		u=(A*u+B+ans[i])%n+1;
		v=(B*v+C+ans[i])%n+1;
		d=(C*d+A+ans[i])%m;
	}
	all=0;
	FOR(i,1,q) all+=i*(ans[i]+1);
	printf("%lld\n",all);
	FOR(i,1,n) edge[i].clear();
}
int main(){
	LL T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
