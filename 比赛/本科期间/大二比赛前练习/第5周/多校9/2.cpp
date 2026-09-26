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
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=1e5+7;
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
struct node{
	int l,r;
	LL sum;
	node(){l=r=sum=0;}
}T[maxn*35];
int cnt;
void update(int &x,int y,int pos,int l,int r){
	T[++cnt]=T[y];T[cnt].sum=T[cnt].sum+pos;x=cnt;
//	printf("U:%d %d %d %d %d\n",x,y,pos,l,r);
	if (l==r) return; 
	int mid=(l+r)/2;
	if (mid>=pos) update(T[x].l,T[y].l,pos,l,mid);
	else update(T[x].r,T[y].r,pos,mid+1,r);
}
LL Query(int x,int y,int l,int r,int L,int R){
	if (l<=L&&R<=r) return T[x].sum-T[y].sum;
	LL mid=(L+R)/2,ret=0;
	if (mid>=l) ret+=Query(T[x].l,T[y].l,l,r,L,mid);
	if (r>mid) ret+=Query(T[x].r,T[y].r,l,r,mid+1,R);
	return ret;
}
vector<int> edge[maxn];
const int MAX=1000000000;
int fa[maxn],son[maxn],sz[maxn],top[maxn],dep[maxn];
int tot;
void dfs1(int u,int from,int depth){
	int v,i,mx=-1;
	sz[u]=1;fa[u]=from;dep[u]=depth;son[u]=0;
	for (int v:edge[u]){
		if (v==from) continue;
		dfs1(v,u,depth+1);
		sz[u]+=sz[v];
		if (sz[v]>mx) mx=v,son[u]=v;
	}
}
void dfs2(int u,int x){
	top[u]=x;
	if (son[u]) dfs2(son[u],x);
	for(int v:edge[u]){
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
int query(int x,int y){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if (dep[x]>dep[y]) swap(x,y);
	return x;
}
int n,m;
int i;
int u,v;
int l,r;
int val[maxn];
int root[maxn];
void dfs(int x,int fa){
//	printf("U:%d %d %d\n",x,fa,val[x]);
	update(root[x],root[fa],val[x],1,MAX);
	for (int v:edge[x]) if (v!=fa) dfs(v,x);
}
int main(){
    while (~scanf("%d%d",&n,&m)){
		FOR(i,1,n) scanf("%d",&val[i]);
    	REP(i,n-1){
    		scanf("%d%d",&u,&v);
    		edge[u].push_back(v);
    		edge[v].push_back(u);
		}
		dfs1(1,0,1);
		dfs2(1,1);
//		puts("OK1");
		dfs(1,0);
		REP(i,m){
			scanf("%d%d",&u,&v);
			int f=query(u,v);
			scanf("%d%d",&l,&r);
			LL ans=Query(root[u],root[f],l,r,1,MAX)+Query(root[v],root[f],l,r,1,MAX);
			if (l<=val[f]&&val[f]<=r) ans=ans+val[f];
			if (i!=0) printf(" ");
			printf("%lld",ans);
//			printf("fa:%d\n",f);
		}
		puts("");
		FOR(i,1,n) vector<int>().swap(edge[i]);
		FOR(i,1,n) root[i]=0;
		FOR(i,1,cnt) T[i]=node();cnt=0;
	}
}
/*
5 3
500000000 1000000000 150000000 1500000000 1000000000
1 2
2 4
3 1
2 5
4 5 500000000 1500000000
1 1 500000000 500000000
3 5 1000000000 1500000000
*/

