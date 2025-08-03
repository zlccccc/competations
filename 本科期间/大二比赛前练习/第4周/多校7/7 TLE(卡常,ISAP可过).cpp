#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
const LL INF=1000000000;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
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
	int to,cap,next;
	node(int t=0,int c=0,int n=0):to(t),cap(c),next(n){}
}edge[maxn];
int head[2507];
int tot;
void addedge(int from,int to,int cap){
	edge[tot].to=to;
	edge[tot].next=head[from];
	edge[tot].cap=cap;
	head[from]=tot++;
	edge[tot].to=from;
	edge[tot].next=head[to];
	edge[tot].cap=0;
	head[to]=tot++;
}
queue<int> Q;
bool vis[2507];
int d[2507];
int cur[2507];//当前弧优化 
bool bfs(int s,int t){
//	printf("B:%d %d\n",s,t);
	memset(vis,0,sizeof(vis));
	while (Q.size()) Q.pop();
	Q.push(s);
	d[s]=0;vis[s]=1;
	int i;
	while (!Q.empty()){
		int x=Q.front();Q.pop();
		for(i=head[x];i!=-1;i=edge[i].next){
			if (!vis[edge[i].to]&&edge[i].cap){
				vis[edge[i].to]=1;
				d[edge[i].to]=d[x]+1;
				Q.push(edge[i].to);
			}
		}
	}
	return vis[t];
}
int dfs(int x,int t,int flow){
//	printf("%d %d %d\n",x,t,flow);
	if (x==t||flow==0) return flow;
	int i,ret=0,f;
	for (i=cur[x];i!=-1;i=edge[i].next){
		if (d[x]+1==d[edge[i].to]&&((f=dfs(edge[i].to,t,min(flow,edge[i].cap)))>0)){
			edge[i].cap-=f;
			edge[i^1].cap+=f;
			ret+=f;
			flow-=f;
			cur[x]=i;
			if (flow==0) break;
		}
	}
	return ret;
}
int n,m,k;
int i,j;
int s,t;
int flow;
int id[57][57];
int main(){
    int T;
    scanf("%d",&T);
    while (T--){
		scanf("%d%d%d",&n,&m,&k);
		tot=0;
		int tot=0;
		s=++tot;t=++tot;
		FOR(i,1,n){
			id[i][1]=s;
			FOR(j,2,m) id[i][j]=++tot;
		}
		FOR(i,1,tot) head[i]=-1;
		FOR(i,1,n){
        	FOR(j,1,m){
        		int k;
				scanf("%d",&k);
				if (j!=m) addedge(id[i][j],id[i][j+1],1000-k);
				else addedge(id[i][j],t,1000-k);
			}
		}
		REP(i,k){
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			FOR(j,1,m) {
				if (1<j-z&&j-z<=m) addedge(id[x][j],id[y][j-z],INF);
				if (j-z==m+1) addedge(id[x][j],t,INF);
			}
		}
//		printf("%d\n",tot);
//		printf("%d\n",::tot);
		flow=0;
		while (bfs(s,t)){
			int f;
			memcpy(cur,head,sizeof(head));
			while (f=dfs(s,t,INF)) flow+=f;
//			printf("f=%d\n",f);
//			printf("flow=%d\n",flow);
		}
		if (flow>=n*1000) puts("-1");
		else printf("%d\n",n*1000-flow);
    }
}
/*
*/

