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
const LL maxn=2e5+7;
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
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
vector<pii> edge[maxn];
int root,minweight,sz[maxn],n;
void dfs1(int x,int fa){
	int weight=0;
	sz[x]=1;
	for (pii v:edge[x]){
		if (v.fi==fa) continue;
		dfs1(v.fi,x);
		sz[x]+=sz[v.fi];
		weight=max(weight,sz[v.fi]);
	}
	weight=max(weight,n-sz[x]);
	if (weight<minweight) {root=x;minweight=weight;}
}
LL ans;
void dfs2(int x,int fa,LL len){
	ans+=len*2;
	for (pii v:edge[x]){
		if (v.fi==fa) continue;
		dfs2(v.fi,x,v.se+len);
	}
}
int tot;
int in[maxn],out[maxn],top[maxn];
int val[maxn];
void dfs(int x,int fa,int TOP){
	in[x]=++tot;sz[x]=1;val[tot]=x;
	top[x]=TOP;
	for (pii v:edge[x]){
		if (v.fi==fa) continue;
		if (TOP==root) dfs(v.fi,x,v.fi);
		else dfs(v.fi,x,TOP);
		sz[x]+=sz[v.fi];
	}
	out[x]=tot;
}
int MIN[maxn<<2];
void pushup(int x){
	MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
}
void build(int x,int l,int r){
//	printf("%d %d %d\n",x,l,r);
	if (l==r) {MIN[x]=val[l];return;}
	int mid=(l+r)/2;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void update(int x,int pos,int val,int L,int R){
//	printf("U:%d %d %d %d %d %d\n",x,l,r,val,L,R);
	if (L==R){
		MIN[x]+=val;
		return;
	}
	int mid=(L+R)/2;
	if (mid>=pos) update(x<<1,pos,val,L,mid);
	else update(x<<1|1,pos,val,mid+1,R);
	pushup(x);
}
int query(int x,int l,int r,int L,int R){
//	if (l>r) return INF;
//	printf("Q:%d %d %d %d %d\n",x,l,r,L,R);
	if (l<=L&&R<=r) return MIN[x];
	int ret=INF,mid=(L+R)/2;
	if (mid>=l) ret=min(ret,query(x<<1,l,r,L,mid));
	if (r>mid) ret=min(ret,query(x<<1|1,l,r,mid+1,R));
	pushup(x);
	return ret;
}
int i;
int match[maxn];
vector<int> must;//top
set<int> now[maxn*2];
set<int>::iterator it;
int main()
{
	scanf("%d",&n);
	REP(i,n-1){
		int u,v,len;
		scanf("%d%d%d",&u,&v,&len);
		edge[u].push_back(mp(v,len));
		edge[v].push_back(mp(u,len));
	}
	minweight=n;
	dfs1(1,0);
	dfs2(root,0,0);
	printf("%I64d\n",ans);
	dfs(root,0,root);
	build(1,1,n);
	FOR(i,1,n){
		sz[top[i]]*=2;
		now[sz[top[i]]].insert(top[i]);
	}
//	FOR(i,1,n) printf("%d ",val[i]);puts("");
//	FOR(i,1,n*4) printf("%d ",MIN[i]);puts("");
//	FOR(i,1,n) printf("%d ",top[i]);puts("");
	FOR(i,1,n){
		must.clear();
		for (it=now[n+1-i].begin();it!=now[n+1-i].end();it++) must.push_back(*it);
		match[i]=INF;
		if (must.size()==2){
			if (must[0]==i) match[i]=min(match[i],query(1,in[must[1]],out[must[1]],1,n));
			if (must[1]==i) match[i]=min(match[i],query(1,in[must[0]],out[must[0]],1,n));
		}else if (must.size()==1&&must[0]!=i){
			match[i]=min(match[i],query(1,in[must[0]],out[must[0]],1,n));
		}else if (i!=root){
			if (1<=in[top[i]]-1) match[i]=min(match[i],query(1,1,in[top[i]]-1,1,n));
			if (out[top[i]]+1<=n) match[i]=min(match[i],query(1,out[top[i]]+1,n,1,n));
		}else match[i]=min(match[i],query(1,1,n,1,n));
//		printf("%d %d matchOK\n",i,match[i]);
		update(1,in[match[i]],n,1,n);
//		printf("%d updateOK\n",i);
		if (i!=root){
			now[sz[top[i]]].erase(top[i]);
			sz[top[i]]--;
			now[sz[top[i]]].insert(top[i]);
		}
		if (match[i]!=root){
			now[sz[top[match[i]]]].erase(top[match[i]]);
			sz[top[match[i]]]--;
			now[sz[top[match[i]]]].insert(top[match[i]]);
		}
//		printf("%d eraseOK\n",i);
	}
	FOR(i,1,n) printf("%d ",match[i]);
}
/*
3
1 3 4
2 3 5
*/
