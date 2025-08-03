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
const LL maxn=300+7;
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
	int to,cap,cost,rev;
	node(int t=0,int c=0,int n=0,int r=0):to(t),cap(c),cost(n),rev(r){}
};
vector<node> edge[maxn];
void addedge(int from,int to,int cap,int cost){
	edge[from].push_back(node(to,cap,cost,edge[to].size()));
	edge[to].push_back(node(from,0,-cost,edge[from].size()-1));
}
int dis[maxn];
bool mark[maxn];
int pre_v[maxn],pre_e[maxn];
deque<int> Q;
int mincostflow(int s,int t,int f){
	int ret=0,d;
	int i,v;
	while (f){
		memset(dis,0x3f,sizeof(dis));
		memset(mark,0,sizeof(mark));
		while (Q.size()) Q.pop_front();
		dis[s]=0;Q.push_back(s);
		while (Q.size()){
			v=Q.front();mark[v]=0;Q.pop_front();
			REP(i,edge[v].size()){
				node &e=edge[v][i];
				if (e.cap>0&&dis[e.to]>dis[v]+e.cost){
					dis[e.to]=dis[v]+e.cost;
					pre_v[e.to]=v;
					pre_e[e.to]=i;
					if (!mark[e.to]){
						if (Q.empty()||dis[Q.front()]<dis[e.to]) Q.push_back(e.to);
						else Q.push_front(e.to);
						mark[e.to]=1;
					}
				}
			}
		}
		if (dis[t]==INF) break;
		d=f;
		for(v=t;v!=s;v=pre_v[v])
			d=min(d,edge[pre_v[v]][pre_e[v]].cap);
		f-=d;
		ret+=d*dis[t];
		for (v=t;v!=s;v=pre_v[v]){
			node &e=edge[pre_v[v]][pre_e[v]];
			e.cap-=d;
			edge[v][e.rev].cap+=d;
		}
		if (d==0) break;
	}
	return ret;
}
int n,m,k,t;
int i,j;
int K[maxn],LV[maxn],ATK[maxn],S,T;
int MX[maxn][maxn];
int u,v;
int sum,val,all;
void solve(){
	int tot=0;
	scanf("%d%d",&n,&m);
	S=n+1;T=n+2;
	FOR(i,1,n+2) edge[i].clear();
	memset(MX,0,sizeof(MX));
	all=0;
	FOR(i,1,n){
		scanf("%d%d%d",&K[i],&LV[i],&ATK[i]);
		if (K[i]==0) addedge(S,i,1,0);
		if (K[i]==1) addedge(S,i,1,0),addedge(i,T,1,0);
		all+=ATK[i];
	}
	REP(t,m){
		scanf("%d%d%d",&sum,&val,&k);
		if (k==0){
			FOR(i,1,n) if (K[i]==0){
				FOR(j,1,n) if (K[j]==1){
					if (LV[i]+LV[j]==sum&&val-ATK[i]-ATK[j]>0) MX[i][j]=min(MX[i][j],-(val-ATK[i]-ATK[j]));
				}
			}
		}else if (k==1){
			scanf("%d",&u);
			FOR(i,1,n) if (K[i]==0&&(K[i]!=K[u]||i==u)){
				FOR(j,1,n) if (K[j]==1&&(K[j]!=K[u]||j==u)){
					if (LV[i]+LV[j]==sum&&val-ATK[i]-ATK[j]>0) MX[i][j]=min(MX[i][j],-(val-ATK[i]-ATK[j]));
				}
			}
		}else if (k==2){
			scanf("%d%d",&u,&v);
			if (K[u]==0&&val-ATK[u]-ATK[v]>0) MX[u][v]=min(MX[u][v],-(val-ATK[u]-ATK[v]));
			if (K[v]==0&&val-ATK[u]-ATK[v]>0) MX[v][u]=min(MX[v][u],-(val-ATK[u]-ATK[v]));
		}
	}
	FOR(i,1,n){
		FOR(j,1,n){
			if (MX[i][j]<0) addedge(i,j,1,MX[i][j]);
		}
	}
	printf("%d\n",all-mincostflow(S,T,INF));
}
int main()
{
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
