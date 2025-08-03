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
const LL maxn=400+7;
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
pair<int,int> mincostflow(int s,int t,int f){
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
	return make_pair(INF-f,ret); 
}
int n,k;
int i,j;
int s,t;
int P[maxn],S,T,all;
int m,p,q;
void solve(){
	int tot=0;
	scanf("%d%d",&n,&k);
	FOR(i,1,n) scanf("%d",&P[i]);
	s=n*2+1;t=n*2+2;
	addedge(s,1+n,k,0);
	FOR(i,1,n-1){
		addedge(i,i+1,INF,0);
		addedge(i+n,i+n+1,INF,0);
	}
	all=0;
	FOR(i,1,n){
		addedge(s,i,P[i],0);
		addedge(i+n,t,P[i],0);
		all+=P[i];
	}
	scanf("%d%d%d",&m,&p,&q);
	FOR(j,p,n){
		addedge(s,j+n,INF,q);
	}
	REP(j,m){
		int S,T;
		scanf("%d%d",&S,&T);
		FOR(i,1,n-T){
			addedge(i,i+T+n,INF,S);
		}
	}
	pair<int,int> ans=mincostflow(s,t,INF);
	if (ans.first!=all) puts("No solution");
	else printf("%d\n",ans.second);
	FOR(i,1,n*2+2) edge[i].clear();
}
int main()
{
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
