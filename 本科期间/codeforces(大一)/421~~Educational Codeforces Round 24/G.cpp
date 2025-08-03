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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

struct node{
	int to,cap,cost,rev;
	node(int t=0,int c=0,int n=0,int r=0):to(t),cap(c),cost(n),rev(r){};
};
vector<node> edge[maxn];
void addedge(int from,int to,int cap,int cost){
//	printf("%d->%d %d %d\n",from,to,cap,cost);
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
		for (v=t;v!=s;v=pre_v[v])
			d=min(d,edge[pre_v[v]][pre_e[v]].cap);
		f-=d;
		ret+=d*dis[t];
		for(v=t;v!=s;v=pre_v[v]){
			node &e=edge[pre_v[v]][pre_e[v]];
			e.cap-=d;
			edge[v][e.rev].cap+=d;
		}
		if (d==0) break;
	}
	return ret;
}
int n,s,t;
int i,k;
int tot,now,choose;
int val[maxn],mod[8];
int main(){
	scanf("%d",&n);
	tot=0;
	s=++tot;t=++tot;
	REP(i,n){
		scanf("%d",&k);
		now=++tot;choose=++tot;//now=could->choose
		if (val[k-1]) addedge(val[k-1],now,INF,0);
		if (val[k+1]) addedge(val[k+1],now,INF,0);
		if (val[k]) addedge(val[k],choose,INF,0);
		val[k]=choose;
		tot++;
		if (mod[k%7]) addedge(mod[k%7],tot,INF,0);
		if (mod[k%7]) addedge(mod[k%7],now,INF,0);
		addedge(choose,tot,INF,0);
		mod[k%7]=tot;
		addedge(now,choose,1,-1);
		addedge(s,now,INF,0);
		addedge(choose,t,INF,0);
	}
	printf("%d",-mincostflow(s,t,4));
}
/*
*/
