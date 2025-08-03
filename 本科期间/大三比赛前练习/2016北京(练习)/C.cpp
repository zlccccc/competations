#include <sstream>
#include <fstream>
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
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=5e4+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

namespace mincostflow {
	const int INF=0x3f3f3f3f;
	struct node {
		int to; int cap,cost; int rev;
		node(int t=0,int c=0,int _c=0,int n=0):
			to(t),cap(c),cost(_c),rev(n) {};
	}; vector<node> edge[maxn];
	void addedge(int from,int to,int cap,int cost,int rcap=0) {
		edge[from].push_back(node(to,cap,cost,edge[to].size()));
		edge[to].push_back(node(from,rcap,-cost,edge[from].size()-1));
	} int dis[maxn];
	bool mark[maxn];
	void spfa(int s,int t,int n) {
		memset(dis+1,0x3f,n*sizeof(int));
		memset(mark+1,0,n*sizeof(bool));
		static int Q[maxn],st,ed;
		dis[s]=0; st=ed=0; Q[ed++]=s;
		while (st!=ed) {
			int v=Q[st]; mark[v]=0;
			if ((++st)==maxn) st=0;
			for (node &e:edge[v]) {
				if (e.cap>0&&dis[e.to]>dis[v]+e.cost) {
					dis[e.to]=dis[v]+e.cost;
					if (!mark[e.to]) {
						if (st==ed||dis[Q[st]]<=dis[e.to]) {
							Q[ed]=e.to, mark[e.to]=1;
							if ((++ed)==maxn) ed=0;
						} else {
							if ((--st)<0) st+=maxn;
							Q[st]=e.to, mark[e.to]=1;
						}
					}
				}
			}
		}
	} int cur[maxn];
	int dfs(int x,int t,int flow) {
		if (x==t||!flow) return flow;
		int ret=0; mark[x]=1;
		int i;
		rep(i,cur[x],(int) edge[x].size()) {
			node &e=edge[x][i];
			if (!mark[e.to]&&e.cap) {
				if (dis[x]+e.cost==dis[e.to]) {
					int f=dfs(e.to,t,min(flow,e.cap));
					e.cap-=f; edge[e.to][e.rev].cap+=f;
					ret+=f; flow-=f; cur[x]=i;
					if (flow==0) break;
				}
			}
		} mark[x]=0;
		return ret;
	}
	pair<int,int> mincostflow(int s,int t,int n,int flow=INF) {
		int ret=0,ans=0;
		while (flow) {
			spfa(s,t,n); if (dis[t]==INF) break;
			memset(cur+1,0,n*sizeof(int));
			int len=dis[t],f;
			while ((f=dfs(s,t,flow))>0)
				ret+=f,ans+=len*f,flow-=f;
		} return make_pair(ret,ans);
	}
	void init(int n) {
		int i; FOR(i,1,n) edge[i].clear();
	}
}
namespace pipeflow{
	typedef int type;
	int eid[maxn],etot;
	type in[maxn],out[maxn],flow[maxn];
	int s_s,t_t,ans;
	void addedge(int u,int v,int low,int high,int cost){
		// printf("%d -> %d : %d %d %d\n",u,v,low,high,cost);
		if (high!=low) mincostflow::addedge(u,v,high-low,cost);
		out[u]+=low; in[v]+=low; ans+=low*cost;
	}
	void init(int n){
		s_s=n+1,t_t=n+2; etot=0; ans=0;
		memset(in+1,0,n*sizeof(int));
		memset(out+1,0,n*sizeof(int));
		mincostflow::init(n+2);
	}
	int solve(int n){
		int sum=0,i;
		FOR(i,1,n) {
			sum+=max(0,in[i]-out[i]);
			if (in[i]>out[i]) mincostflow::addedge(s_s,i,in[i]-out[i],0);
			if (in[i]<out[i]) mincostflow::addedge(i,t_t,out[i]-in[i],0);
		} auto now=mincostflow::mincostflow(s_s,t_t,n+2);
		if (now.first!=sum) return -1;
		return now.second;
	}
}
int A[107][107];
int main() {
	while (~scanf("%d",&n)){
		int s=n+n+1,t=s+1,i,j,sum=0;
		pipeflow::init(t);
		FOR(i,1,n) FOR(j,1,n) scanf("%d",&A[i][j]),sum+=A[i][j];
		FOR(i,1,n){
			int l,r;
			scanf("%d%d",&l,&r);
			pipeflow::addedge(s,i,l,r,0);
		}
		FOR(i,1,n){
			int l,r;
			scanf("%d%d",&l,&r);
			pipeflow::addedge(i+n,t,l,r,0);
		}
		FOR(i,1,n*n/2){
			int x1,y1,x2,y2;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			if (A[x1][y1]==A[x2][y2]) {
				pipeflow::addedge(x1,y1+n,A[x1][y1],A[x1][y1],0);
				pipeflow::addedge(x2,y2+n,A[x2][y2],A[x2][y2],0);
				continue;
			} if (A[x1][y1]==0) swap(x1,x2),swap(y1,y2);
			if (x1==x2) {
				pipeflow::addedge(x1,y1+n,1,1,0);
				pipeflow::addedge(y1+n,y2+n,0,1,1);
			} else {
				pipeflow::addedge(x2,x1,0,1,1);
				pipeflow::addedge(x1,y1+n,1,1,0);
			}
		}
		pipeflow::addedge(t,s,0,INF,0);
		printf("%d\n",pipeflow::solve(t));
	}
}
/*
2
0 0
1 1
2 2
0 1
0 2
0 2
1 1 2 1
1 2 2 2
4
0 0 1 1
0 0 1 1
1 1 0 0
1 1 0 0
2 2
1 3
1 3
2 2
0 1
3 4
0 1
3 4
1 1 1 3
1 2 1 4
2 1 2 3
2 2 2 4
3 1 3 4
3 2 3 3
4 1 4 4
4 2 4 3


1001
0110
0101
0101
*/
