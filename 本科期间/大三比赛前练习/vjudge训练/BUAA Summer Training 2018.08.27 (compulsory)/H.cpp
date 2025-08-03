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
const LL maxn=2000+7;
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

//1. one task one day
//2. all task done
namespace maxflow {
	typedef int type;
	const type INF=0x3f3f3f3f;
	struct node {
		int to; type cap; int next;
		node(int t=0,type c=0,int n=0):to(t),cap(c),next(n) {};
	} edge[maxn*50];
	int head[maxn],tot;
	void addedge(int from,int to,type cap,type rcap=0) {
		edge[tot]=node(to,cap,head[from]); head[from]=tot++;
		edge[tot]=node(from,rcap,head[to]); head[to]=tot++;
	}
	int dep[maxn],cur[maxn];//当前弧优化
	bool bfs(int s,int t,int n) {
		static int Q[maxn],ST,ED;
		memset(dep+1,0,n*sizeof(int));
		ST=0; ED=-1;
		Q[++ED]=s; dep[s]=1;
		while (ST<=ED) {
			int u=Q[ST++];
			for (int i=head[u]; i!=-1; i=edge[i].next) {
				int v=edge[i].to;
				if (!dep[v]&&edge[i].cap) {
					Q[++ED]=v; dep[v]=dep[u]+1;
				}
			}
		} return (dep[t]!=0);
	}
	type dfs(int x,const int &t,type flow=INF) {
		if (x==t||flow==0) return flow;
		type ret=0;
		for (int i=cur[x]; i!=-1; i=edge[i].next) {
			if (dep[x]+1==dep[edge[i].to]&&edge[i].cap) {
				int f=dfs(edge[i].to,t,min(flow,edge[i].cap));
				edge[i].cap-=f; edge[i^1].cap+=f;
				ret+=f; flow-=f; cur[x]=i;
				if (flow==0) break;
			}
		} if (!ret) dep[x]=0;
		return ret;
	}
	type maxflow(int s,int t,int n) {
		int ret=0;
		while (bfs(s,t,n)) {
			int f;
			memcpy(cur+1,head+1,n*sizeof(int));
			while ((f=dfs(s,t))>0) ret+=f;
		} return ret;
	}
	void init(int n) {
		memset(head+1,0xff,n*sizeof(int)); tot=0;
	}
}

int s[maxn],t[maxn];
vector<int> r[maxn];
priority_queue<int> Q;
int main() {
	int i,j,ans1=0,ans2=0,lasttime=0;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) {
		scanf("%d%d",&s[i],&t[i]);
		r[s[i]].push_back(t[i]);
		max_(lasttime,t[i]);
	} FOR(i,1,lasttime) {
		while (Q.size()&&-Q.top()<i) Q.pop();
		for (auto now:r[i]) Q.push(-now);
		if (Q.size()&&-Q.top()>=i) {
			Q.pop(); ans1++;
		}
	} printf("%d\n",ans1);
	int S=n+lasttime+lasttime+1,T=n+lasttime+lasttime+2;
	maxflow::init(n+lasttime+lasttime+2);
	FOR(i,1,n) {
		if (i<=m) {
			maxflow::addedge(S,i,1);
			FOR(j,s[i],t[i]) maxflow::addedge(i,j+n,INF);
		} else {
			maxflow::addedge(i,T,1);
			FOR(j,s[i],t[i]) maxflow::addedge(j+n+lasttime,i,INF);
		}
	} FOR(i,1,lasttime) maxflow::addedge(i+n,i+n+lasttime,1);
	ans2=maxflow::maxflow(S,T,n+lasttime+lasttime+2);
	printf("%d\n",ans2);
}
/*

*/