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
const LL maxn=5000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	int to,cap,next;
	node(int t=0,int c=0,int n=0):to(t),cap(c),next(n){}
}edge[maxn*10];
int head[maxn];
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
bool vis[maxn];
int d[maxn];
int cur[maxn];//当前弧优化 
bool bfs(int s,int t){
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
int maxflow(int s,int t){
	int ret=0;
	while (bfs(s,t)){
		int f;
		memcpy(cur,head,sizeof(head));
		while (f=dfs(s,t,INF)) ret+=f;
	}
	return ret;
}
int n,m;
int cnt[maxn];
vector<pair<int,int> > E;
int id[maxn];
bool check(int x){
	tot=0;
	memset(head,-1,sizeof(head));
	int s=n+1,t=n+2,i;
	for(pair<int,int> now:E) addedge(now.first,now.second,1);
	FOR(i,1,n) addedge(s,i,cnt[i]);
	FOR(i,1,n) addedge(i,t,x);
	if (maxflow(s,t)==m) return 1;
	return 0;
}
int L,R,mid;
int main(){
	int i,j;
	scanf("%d%d",&n,&m);
	REP(i,m){
		int u,v;
		scanf("%d%d",&u,&v);
		E.push_back(make_pair(u,v));
		cnt[u]++;
	}
	L=-1;R=m;
	while (L+1<R){
		mid=(L+R)/2;
		if (!check(mid)) L=mid;
		else R=mid;
	}
	printf("%d\n",R);
	check(R);
	REP(i,m){
		if (edge[i*2].cap) printf("%d %d\n",E[i].first,E[i].second);
		else printf("%d %d\n",E[i].second,E[i].first);
	}
}
/*
*/
