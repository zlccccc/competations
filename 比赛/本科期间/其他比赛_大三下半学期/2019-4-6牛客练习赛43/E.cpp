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
const LL maxn=5e5+107;
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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}


namespace maxflow {
	typedef int type;
	const type INF=0x3f3f3f3f;
	struct node {
		int to; type cap; int next;
		node(int t=0,type c=0,int n=0):to(t),cap(c),next(n) {};
	} edge[maxn*50];
	int head[maxn],tot;
	int addedge(int from,int to,type cap,type rcap=0) {
		edge[tot]=node(to,cap,head[from]); head[from]=tot++;
		edge[tot]=node(from,rcap,head[to]); head[to]=tot++;
		return tot-2;
	}
	int dep[maxn],cur[maxn];
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
			type f;
			memcpy(cur+1,head+1,n*sizeof(int));
			while ((f=dfs(s,t))>0) ret+=f;
		} return ret;
	}
	void init(int n) {
		memset(head+1,0xff,n*sizeof(int)); tot=0;
	}
}
namespace pipeflow {
	typedef int type;
	int eid[maxn],etot;
	type in[maxn],out[maxn],flow[maxn];
	int s_s,t_t;//S,T
	int addedge(int u,int v,int low,int high) {
		eid[etot]=maxflow::addedge(u,v,high-low);
		out[u]+=low; in[v]+=low; flow[etot++]=low;
		return etot-1;
	}
	void init(int n) {
		s_s=n+1,t_t=n+2; etot=0;
		memset(in+1,0,n*sizeof(type));
		memset(out+1,0,n*sizeof(type));
		maxflow::init(n+2);
	}
	bool solve(int n) {
		int sum=0,i;
		FOR(i,1,n) {
			sum+=max(0,in[i]-out[i]);
			if (in[i]>out[i]) maxflow::addedge(s_s,i,in[i]-out[i]);
			if (in[i]<out[i]) maxflow::addedge(i,t_t,out[i]-in[i]);
		} if (maxflow::maxflow(s_s,t_t,n+2)!=sum) return 0;
		REP(i,etot) flow[i]+=maxflow::edge[eid[i]^1].cap;//more
		return 1;
	}
}

//喵的公告是谁告诉我的题意, 告错了...
struct node {
	int x,y; ll w;
} edge[maxn];
int n,m;
int A[507],B[507];
ll D[207][207];
bool solve(ll mid) {
	int s=n+n+1,t=n+n+2,i,j;
	pipeflow::init(n+n+2);
	FOR(i,1,n) {
		pipeflow::addedge(s,i,A[i],A[i]);
		pipeflow::addedge(i+n,t,0,B[i]);
	} FOR(i,1,n) FOR(j,1,n){
		if (D[i][j]<=mid) pipeflow::addedge(i,j+n,0,INF);
	}
	pipeflow::addedge(t,s,0,INF);
	return pipeflow::solve(n+n+2);
}
int main() {
	int i,j,k;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d%d",&A[i],&B[i]);
	FOR(i,1,n) FOR(j,1,n) D[i][j]=INFF*(i!=j);
	FOR(i,1,m) {
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		D[x][y]=D[y][x]=min(D[x][y],(ll)w);
	}
	FOR(i,1,n) FOR(j,1,n) FOR(k,1,n) {
		D[i][k]=min(D[i][k],D[i][j]+D[j][k]);
	} ll l=-1,r=(ll)INF*200;//l:okay, r:
	while (l+1<r) {
		ll mid=(l+r)/2;
		if (solve(mid)) r=mid;
		else l=mid;
	}
	if (r==(ll)INF*200) puts("-1");
	else printf("%lld\n",r);
}
/*
0 0
*/