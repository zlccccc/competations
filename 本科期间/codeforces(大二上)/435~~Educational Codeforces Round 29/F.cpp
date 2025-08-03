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
	return make_pair(INFF-f,ret);
}
int MIN[107],MAX[107];
int n,m;
int pre;
int S,T;
int main(){
	int i,j,k;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) MIN[i]=1,MAX[i]=n;
	REP(i,m){
		int k,l,r,val;
		scanf("%d%d%d%d",&k,&l,&r,&val);
		if (k==1) FOR(j,l,r) MIN[j]=max(MIN[j],val);
		if (k==2) FOR(j,l,r) MAX[j]=min(MAX[j],val);
	}
	S=n+1;T=n+2;
	pre=n+2;
	FOR(i,1,n){
		FOR(j,1,n) addedge(i,T,1,j*2-1);
	}
	FOR(i,1,n){
		addedge(S,n+i+2,1,0);
		FOR(j,MIN[i],MAX[i]) addedge(n+i+2,j,1,0);
	}
	pair<int,int> ans=mincostflow(S,T,INF);
//	printf("%d,%d %d\n",n,ans.first,ans.second);
	if (ans.first!=n) return 0*puts("-1");
	printf("%d\n",ans.second);
}
