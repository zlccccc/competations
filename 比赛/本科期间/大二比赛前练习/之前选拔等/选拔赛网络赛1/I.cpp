#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
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
const LL MOD=1e9+7;
const LL maxn=300+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%MOD) ret=1ll*ret*a%MOD;return ret;}

#define next nxt
#define x x_x
int n,m;
struct node{
	int to,cap,next;
}edge[maxn*2];
int head[maxn],tot;
void addedge(int from,int to,int cap){
	edge[tot].to=to;
	edge[tot].next=head[from];
	edge[tot].cap=cap;
	head[from]=tot++;
	swap(to,from);
	edge[tot].to=to;
	edge[tot].next=head[from];
	edge[tot].cap=0;
	head[from]=tot++;
//	printf("%d %d %d\n",from,to,cap);
}
queue<int>Q;
bool vis[maxn];
int d[maxn];
int bfs(int s,int t){
	memset(vis,0,sizeof(vis));
	while (Q.size()) Q.pop();
	Q.push(s);
	d[s]=0;vis[s]=1;
	int i;
	while (Q.size()){
		int x=Q.front();Q.pop();
		for (i=head[x];~i;i=edge[i].next){
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
	for (i=head[x];~i;i=edge[i].next){
		if (d[x]+1==d[edge[i].to]&&((f=dfs(edge[i].to,t,min(flow,edge[i].cap)))>0)){
			edge[i].cap-=f;
			edge[i^1].cap+=f;
			ret+=f;
			flow-=f;
			if (flow==0) break;
		}
	}
//	printf("%d %d %d %d\n",x,t,flow,ret);
	return ret;
}
int a[maxn];
int u[maxn],v[maxn];
int cnt[maxn];
int solve(int x){
	int i;
	tot=0;
	memset(head,-1,sizeof(head));
	FOR(i,1,n){
		cnt[i]=0;
		while (a[i]%x==0) {a[i]/=x;cnt[i]++;}
	}
	REP(i,m) if (min(cnt[u[i]],cnt[v[i]])!=0){
		addedge(u[i],v[i],min(cnt[u[i]],cnt[v[i]]));
	}
	FOR(i,1,n){
		if (i&1) addedge(n+1,i,cnt[i]);
		else addedge(i,n+2,cnt[i]);
	}
	int ret=0,t;
	while (bfs(n+1,n+2)){
		while (t=dfs(n+1,n+2,INF)) ret+=t;
	}
	return ret;
}
int last(){
	tot=0;
	memset(head,-1,sizeof(head));
	int i;
	REP(i,m) if (a[u[i]]!=1&&a[u[i]]==a[v[i]]){
		addedge(u[i],v[i],1);
	}
	FOR(i,1,n){
		if (i&1) addedge(n+1,i,1);
		else addedge(i,n+2,1);
	}
	int ret=0,t;
	while (bfs(n+1,n+2)){
		while (t=dfs(n+1,n+2,INF)) ret+=t;
	}
	return ret;
}
bool mark[100007];
int i,j,k;
int ans;
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&a[i]);
	REP(i,m){
		scanf("%d%d",&u[i],&v[i]);
		if (v[i]&1) swap(u[i],v[i]);
	}
	mark[2]=0;
	FOR(i,2,100000){
		if (mark[i]) continue;
		for (j=i;j<=100000;j+=i) mark[j]=1;
//		printf("OK===%d\n",i);
		ans+=solve(i);
//		printf("ans==%d\n",ans);
	}
	ans+=last();
	printf("%d",ans);
}
/*
*/
