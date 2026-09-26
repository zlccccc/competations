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
const LL maxn=500+7;
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
	LL to,cap,cost,rev;
	node(int t=0,int c=0,int n=0,int r=0):to(t),cap(c),cost(n),rev(r){}
};
vector<node> edge[maxn];
void addedge(int from,int to,LL cap,LL cost){
	edge[from].push_back(node(to,cap,cost,edge[to].size()));
	edge[to].push_back(node(from,0,-cost,edge[from].size()-1));
}
LL dis[maxn];
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
		for (v=t;v!=s;v=pre_v[v])
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

int n,m;
int i,j;
int id[57][57];
int VAL[57][57];
int row[57],col[57];
int in[maxn],out[maxn];
int u,v;
int s,t,S,T;
int tot;
int sum;
void add(int u,int v,int low,int high,int cost){
//	printf("%d %d %d %d %d\n",u,v,low,high,cost);
	addedge(u,v,high-low,cost);
	out[u]+=low;in[v]+=low;
}
void solve(int n){
	tot=0;
	FOR(i,1,n)
		FOR(j,1,n) id[i][j]=++tot;
	FOR(i,1,n) row[i]=++tot;
	FOR(i,1,n) col[i]=++tot;
	s=++tot;t=++tot;
	S=++tot;T=++tot;
	FOR(i,1,n)
		FOR(j,1,n) scanf("%d",&VAL[i][j]);
	FOR(i,1,n){
		FOR(j,1,n){
			if (VAL[i][j]) add(row[i],id[i][j],VAL[i][j],VAL[i][j],0);
			add(row[i],id[i][j],0,1,0);
			add(id[i][j],col[j],0,1,0);
		}
	}
	FOR(i,1,n){
		int l,r;
		scanf("%d%d",&l,&r);
		add(s,row[i],l,r,0);
	}
	FOR(i,1,n){
		int l,r;
		scanf("%d%d",&l,&r);
		add(col[i],t,l,r,0);
	}
	REP(i,n*n/2){
		int x0,y0,x1,y1;
		scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
		if (VAL[x0][y0]==VAL[x1][y1]) continue;
		if (VAL[x0][y0]==1) add(id[x0][y0],id[x1][y1],0,1,1);
		if (VAL[x1][y1]==1) add(id[x1][y1],id[x0][y0],0,1,1);
	}
	add(t,s,0,INF,0);
	sum=0;
	FOR(i,1,tot){
		sum+=max(in[i]-out[i],0);
		if (in[i]>out[i]) addedge(S,i,in[i]-out[i],0);
		if (in[i]<out[i]) addedge(i,T,out[i]-in[i],0);
	}
	pair<int,int> now=mincostflow(S,T,INF);
	printf("%d %d %d\n",sum,now.first,now.second);
	if (now.first!=sum) puts("-1");
	else printf("%d\n",now.second);
	FOR(i,1,tot) edge[i].clear();
	FOR(i,1,tot) in[i]=out[i]=0;
}
int main()
{
	while (~scanf("%d",&n)) solve(n);
}
/*
*/
