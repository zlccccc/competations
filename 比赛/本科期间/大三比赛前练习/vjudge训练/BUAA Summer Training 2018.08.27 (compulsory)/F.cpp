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
const LL maxn=1e6+7;
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

namespace DIJ {
	struct node {
		int n; ll d;
		node(int _n=0,ll _d=0):n(_n),d(_d) {};
		const bool operator < (const node &A)const {
			if (d!=A.d) return d>A.d;
			return n>A.n;
		}
	};
	vector<node> edge[maxn];
	priority_queue<node> Q;
	void dij(int s,int n,ll dis[]) {
		int i;
		FOR(i,1,n) dis[i]=INFF;
		dis[s]=0;
		Q.push(node(s,0));
		while (Q.size()) {
			node x=Q.top(); Q.pop();
			if (dis[x.n]!=x.d) continue;//!
			for (node y:edge[x.n]) {
				if (dis[y.n]>x.d+y.d) {
					dis[y.n]=x.d+y.d;
					Q.push(node(y.n,dis[y.n]));
				}
			}
		}
	}
}
namespace DOM {
	struct Edge {
		int to,next;
		Edge(int _to=0,int _next=-1):to(_to),next(_next) {};
	} edge[maxn*4];
	int head[maxn],pre[maxn],dom[maxn],etot; //edges
	inline void addedge(int head[],int u,int v) {
		edge[++etot]=Edge(v,head[u]);
		head[u]=etot;
	}
	inline void addedge(int u,int v){
		// printf("%d -> %d\n",u,v);
		addedge(head,u,v);
		addedge(pre,v,u);
	}
	int dfn[maxn],tot,par[maxn]; //dfs-tree
	int Fa[maxn],best[maxn]; //disjoint-set
	int semi[maxn],id[maxn],idom[maxn]; //dom-tree
	inline int getfa(int x) {
		if (Fa[x]==x) return x;
		int F=getfa(Fa[x]);
		if (dfn[semi[best[x]]]>dfn[semi[best[Fa[x]]]])
			best[x]=best[Fa[x]];
		return Fa[x]=F;
	}
	void dfs(int x) {
		dfn[x]=++tot;
		id[tot]=x;
		for (int i=head[x]; ~i; i=edge[i].next) {
			int v=edge[i].to;
			if (!dfn[v]) par[v]=x,dfs(v);
		}
	}
	void tarjan(int n) {
		int i;
		FOR(i,1,n) dom[i]=-1;
		FOR(i,1,n) best[i]=semi[i]=Fa[i]=i;
		rFOR(i,2,tot) {
			int x=id[i];
			for (int j=pre[x]; ~j; j=edge[j].next) {
				int v=edge[j].to;
				if (!dfn[v]) continue; //could not reach
				getfa(v); //pre_dfn:not changed
				if (dfn[semi[best[v]]]<dfn[semi[x]])
					semi[x]=semi[best[v]];
			}
			addedge(dom,semi[x],x);
			Fa[x]=par[x];
			x=id[i-1];
			for (int j=dom[x]; ~j; j=edge[j].next) { //path
				int v=edge[j].to;
				getfa(v); //id[min{dfn[z]}];
				if (semi[best[v]]==x) idom[v]=x;
				else idom[v]=best[v];
			}
		}
		FOR(i,2,tot) {
			int x=id[i];
			if (idom[x]!=semi[x]) idom[x]=idom[idom[x]];
		}
	}
	void init(int n) {
		int i;
		FOR(i,1,n) head[i]=pre[i]=-1;
		FOR(i,1,n) dfn[i]=id[i]=idom[i]=0; etot=tot=0;
	}
}
struct enode {
	int u,v; ll d;
} e[maxn];
int ans[maxn],must[maxn];
ll disS[maxn],disT[maxn];
int main() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,m) scanf("%d%d%lld",&e[i].u,&e[i].v,&e[i].d);
	FOR(i,1,n) DIJ::edge[i].clear();
	FOR(i,1,m) DIJ::edge[e[i].u].push_back(DIJ::node(e[i].v,e[i].d));
	DIJ::dij(1,n,disS);
	FOR(i,1,n) DIJ::edge[i].clear();
	FOR(i,1,m) DIJ::edge[e[i].v].push_back(DIJ::node(e[i].u,e[i].d));
	DIJ::dij(2,n,disT);
	// FOR(i,1,n) printf("%lld ",disS[i]);puts("");
	// FOR(i,1,n) printf("%lld ",disT[i]); puts("");
	// puts("OKAY");
	DOM::init(n+m);
	FOR(i,1,m) {
		if (disS[e[i].u]+disT[e[i].v]+e[i].d==disS[2]) {
			DOM::addedge(e[i].u,n+i);
			DOM::addedge(n+i,e[i].v);
		}
		if (disS[e[i].v]+disT[e[i].u]+e[i].d<disS[2]) max_(ans[i],2);
		if (disS[e[i].v]+disT[e[i].u]+e[i].d==disS[2]) max_(ans[i],1);
	} DOM::dfs(1);
	DOM::tarjan(n+m);
	// FOR(i,1,n+m) printf("%d ",DOM::idom[i]);
	for (int v=2;v!=1;v=DOM::idom[v]) {
		// printf("v=%d\n",v);
		if (v>n) must[v-n]=1;
	}
	FOR(i,1,m){
		if (ans[i]==2) puts("HAPPY");
		else if (ans[i]==1||!must[i]) puts("SOSO");
		else puts("SAD");
	}
}
/*
*/
