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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	LL to,cap,cost,rev;
	node(int _t=0,int _c=0,int _n=0,LL _r=0):to(_t),cap(_c),cost(_n),rev(_r){}
};
vector<node> edge[maxn];
void addedge(int from,int to,LL cap,LL cost){
//	printf("%d->%d %d %d\n",from,to,cap,cost);
	edge[from].push_back(node(to,cap,cost,edge[to].size()));
	edge[to].push_back(node(from,0,-cost,edge[from].size()-1));
}
LL dis[maxn];
bool mark[maxn];
int pre_v[maxn],pre_e[maxn];
deque<int> Q;
pair<int,LL> mincostflow(int s,int t,int f){
	LL ret=0,d;
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
		if (dis[t]==INFF) break;
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
	return make_pair(2-f,ret);
}
int n,m;
map<string,int> MP;
int tot,S,T;
void solve(){
	scanf("%d",&m);
	int i;
	MP.clear();
	REP(i,m){
		string from,to;
		int val;
		cin>>from>>to>>val;
		if (!MP.count(from)) MP[from]=++tot;
		if (!MP.count(to)) MP[to]=++tot;
		addedge(MP[from]+m*2,MP[to],1,val);
		addedge(MP[to]+m*2,MP[from],1,val);
	}
	FOR(i,1,tot) addedge(i,i+m*2,1,0);
	S=m*4+1;T=m*4+2;
	if (!MP.count("Dalian")||!MP.count("Shanghai")||!MP.count("Xian")) puts("-1");
	else{
		addedge(S,MP["Xian"]+2*m,1,0);
		addedge(S,MP["Dalian"]+2*m,1,0);
		addedge(MP["Shanghai"],T,2,0);
		pair<int,LL> ans=mincostflow(S,T,2);
//		printf("%d %d\n",ans.first,ans.second);
		if (ans.first<2) puts("-1");
		else printf("%lld\n",ans.second);
	}
	FOR(i,1,m*4+2) edge[i].clear();
	tot=0;
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
3
*/
