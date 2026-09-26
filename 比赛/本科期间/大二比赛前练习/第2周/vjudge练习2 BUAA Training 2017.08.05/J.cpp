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
const double eps=0.000001;

int n,m,T;
int i,j;
int a[maxn*40][2];
int num[maxn*40];
int tot;
void insert(int &x,int y,int val){
	x=++tot;
	int nowx=x,nowy=y,i;
	a[x][0]=a[y][0];a[x][1]=a[y][1];
	rREP(i,20){
		int mark=((val&(1<<i))!=0);
		a[nowx][mark]=++tot;
		nowx=a[nowx][mark];
		nowy=a[nowy][mark];
		a[nowx][0]=a[nowy][0];
		a[nowx][1]=a[nowy][1];
		num[nowx]=num[nowy]+1;
	}
}
int calc(int x,int y,int val){//x->y
	int nowx=x,nowy=y;
	int ret=0,i;
	rREP(i,20){
		int mark=((val&(1<<i))!=0);
		if (num[a[nowy][mark^1]]-num[a[nowx][mark^1]]!=0){
			nowx=a[nowx][mark^1];
			nowy=a[nowy][mark^1];
			ret+=1<<i;
		}else if (num[a[nowy][mark]]-num[a[nowx][mark]]!=0){
			nowx=a[nowx][mark];
			nowy=a[nowy][mark];
		}
	}
	return ret;
}
vector<int> edge[maxn];
int val[maxn];
int top[maxn];
int fa[maxn];
void dfs(int x){
	insert(top[x],top[fa[x]],val[x]);
	for (int v:edge[x]){
		if (v==fa[x]) continue;
		fa[v]=x;
		dfs(v);
	}
}
int SZ[maxn],SON[maxn],TOP[maxn],DEP[maxn];
int TOT=0;
void dfs1(int u,int depth){
	int v,i,mx=-1;
	SZ[u]=1;DEP[u]=depth;SON[u]=0;
	for(int v:edge[u]) if (v!=fa[u]){
		dfs1(v,depth+1);
		SZ[u]+=SZ[v];
		if (SZ[v]>mx) mx=SZ[v],SON[u]=v;
	}
}
void dfs2(int u,int x){
	int v,i;
	TOP[u]=x;
	if (SON[u]) dfs2(SON[u],x);
	for (int v:edge[u]) if (v!=fa[u]){
		if (v==SON[u]) continue;
		dfs2(v,v);
	}
}
int query(int x,int y){
	while (TOP[x]!=TOP[y]){
		if (DEP[TOP[x]]<DEP[TOP[y]]) swap(x,y);
		x=fa[TOP[x]];
	}
	if (DEP[x]>DEP[y]) swap(x,y);
	return x;
}
int u,v,VAL; 
int main(){
//	insert(top[1],top[0],1);
//	insert(top[2],top[1],2);
//	printf("%d\n",calc(top[0],top[2],7));
	while (~scanf("%d%d",&n,&m)){
		tot=TOT=0;
		FOR(i,1,n) scanf("%d",&val[i]);
		REP(i,n-1){
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		dfs(1);
//		puts("OK0");
		dfs1(1,0);
//		puts("OK1");
		dfs2(1,1);
//		puts("OK2");
		REP(i,m){
			scanf("%d%d%d",&u,&v,&VAL);
			int t=query(u,v);
			printf("%d\n",max(calc(top[fa[t]],top[u],VAL),
							  calc(top[fa[t]],top[v],VAL)));
		}
		FOR(i,1,n) edge[i].clear();
		FOR(i,1,n) top[i]=val[i]=fa[i]=0;
		FOR(i,0,tot) a[i][0]=a[i][1]=num[i]=0;
		FOR(i,1,n) SZ[i]=SON[i]=TOP[i]=DEP[i]=0;
	}
    return 0;
}
/*
*/
