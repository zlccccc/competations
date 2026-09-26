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
LL MIN[maxn*4],lazy[maxn*4];
void change(int x,LL val){
	lazy[x]=min(INFF,lazy[x]+val);
	MIN[x]=min(INFF,MIN[x]+val);
}
void pushdown(int x){
	if (lazy[x]){
		change(x<<1,lazy[x]);
		change(x<<1|1,lazy[x]);
		lazy[x]=0;
	}
}
void pushup(int x){
	MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
}
void update(int x,int l,int r,LL val,int L,int R){//add
	if (l<=L&&R<=r){
		change(x,val);
		return;
	}
	pushdown(x);
	int mid=(L+R)/2;
	if (mid>=l) update(x<<1,l,r,val,L,mid);
	if (r>mid) update(x<<1|1,l,r,val,mid+1,R);
	pushup(x);
}
LL query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r){
		return MIN[x];
	}
	pushdown(x);
	int mid=(L+R)/2;
	LL ret=INFF;
	if (mid>=l) ret=min(ret,query(x<<1,l,r,L,mid));
	if (r>mid) ret=min(ret,query(x<<1|1,l,r,mid+1,R));
	pushup(x);
	return ret;
}
vector<int> edge[maxn];
vector<int> add[maxn];
vector<int> del[maxn];
int in[maxn],out[maxn],id[maxn],tot;//ÈËµÄdfsÐò
void dfs1(int x,int fa){
	in[x]=tot+1;
	for (int i:add[x]) id[i]=++tot; 
	for (int v:edge[x]) if (v!=fa) dfs1(v,x);
	out[x]=tot;
}
int m;
LL F[maxn];
LL val[maxn];
void dfs2(int x,int fa){
	if (in[x]>out[x]) {F[x]=INFF;return;}
	LL all=0;
	for (int v:edge[x]) if (v!=fa){
		dfs2(v,x);
		all=min(INFF,all+F[v]);
	}
//	printf("  Fsub:%I64d: query: %I64d %I64d\n",Fsub,in[x],out[x]);
	for (int i:add[x]){
//		printf("x:%I64d,,insert: %I64d %I64d %I64d\n",x,id[i],id[i],val[i]+Fsub);
		update(1,id[i],id[i],val[i]+all,1,m);
	}
	for (int v:edge[x]) if (v!=fa){
//		printf("update: %I64d %I64d %I64d\n",in[x],out[x],F[v]);
		if (in[v]>out[v]) continue;
		update(1,in[v],out[v],all-F[v],1,m);
//		printf("update: %I64d %I64d %I64d\n",in[v],out[v],-F[v]);
	}
	if (x!=1) for (int i:del[x]) {
//		printf("delete: %I64d %I64d %I64d\n",id[i],id[i],INFF);
		update(1,id[i],id[i],INFF,1,m);
	}
//	printf(" :%I64d: query: %I64d %I64d\n",x,in[x],out[x]);
	F[x]=query(1,in[x],out[x],1,m);
//	printf("F[%d]:%d\n",x,F[x]);
}
int n;
int i;
int main()
{
	scanf("%d%d",&n,&m);
	REP(i,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	FOR(i,1,m){
		int u,v;
		scanf("%d%d%I64d",&u,&v,&val[i]);
		add[u].push_back(i);
		del[v].push_back(i);
	}
	if (n==1) return 0*puts("0");
	dfs1(1,0);
//	FOR(i,1,n) printf("%d's in~out=%d %d\n",i,in[i],out[i]);
//	puts("1 OK");
	dfs2(1,0);
//	printf("%d %d %d\n",query(1,3,3,1,m),query(1,4,4,1,m));
	if (F[1]>=INFF/2) puts("-1");
	else printf("%I64d",F[1]);
	return 0;
}
/*
*/
