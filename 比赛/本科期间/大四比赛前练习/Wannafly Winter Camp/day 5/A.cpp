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
const LL M=998244353;
const LL maxn=1e5+107;
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
// int n,m,q;
// char str[maxn];//倒着的


struct edges {
	int u,v;
} e[maxn];
vector<int> vir[maxn];
namespace tarjan { // 边双连通分量, 这里是在做仙人掌
	struct Edge {
		int to,next,id;
		Edge(int _to=0,int _next=-1,int _id=0):to(_to),next(_next),id(_id) {};
	} edge[maxn*2];
	int head[maxn],etot;
	inline void addedge(int u,int v,int id) {
		edge[++etot]=Edge(v,head[u],id); head[u]=etot;
	}
	int dfn[maxn],low[maxn],tot;
	bool vis[maxn],used[maxn];
	int S[maxn],D[maxn],top;
	void tarjan(int x,int fa) {
		low[x]=dfn[x]=++tot; vis[x]=1;
		for (int i=head[x]; ~i; i=edge[i].next) {
			int v=edge[i].to;
			if (used[edge[i].id]) continue;
			if (v==fa) continue;
			S[++top]=edge[i].id; D[top]=edge[i].to;
			used[edge[i].id]=1;
			if (!dfn[v]) {
				tarjan(v,x);
				low[x]=min(low[x],low[v]);
				if (dfn[x]<=low[v]) { //割边和边双联通
					vector<int> Eid,Did;
					while (1) {
						Did.push_back(D[top]);
						int id=S[top--];
						Eid.push_back(id);
						if (id==edge[i].id) break;
					} if (low[v]==dfn[x]) { //双联通, 在这里dp
						// printf(" one :");
						// for (auto now:Eid) printf("%d ",now); puts("");
						for (auto now:Did) if (now!=x) {
							vir[x].push_back(now);
							// printf("e0: %d->%d\n",x,now);
						}
					} else for (auto now:Did) if (now!=x) {
						vir[x].push_back(now);;//割边
						// printf("e: %d->%d\n",x,now);
					}
				}
			} else if (vis[v])
				low[x]=min(low[x],dfn[v]);
		}
	}
	void init(int n,int m) {
		int i;
		FOR(i,1,m) used[i]=0;
		FOR(i,1,n) head[i]=-1,dfn[i]=0; etot=tot=0;
		FOR(i,1,m) addedge(e[i].u,e[i].v,i),addedge(e[i].v,e[i].u,i);
		FOR(i,1,n) if (!dfn[i]) tarjan(i,0);
	}
}
int dep[maxn],dfn[maxn],tot;
void dfs(int x,int fa,int depth) {
	// printf("vir edge : %d->%d\n",fa,x);
	dfn[x]=++tot; dep[x]=depth;
	for (int v:vir[x]) dfs(v,x,depth+1);
}
int main() {
	int n,m; int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,m) {
		int u,v;
		scanf("%d%d",&u,&v);
		e[i]=edges{u,v};
	} tarjan::init(n,m);
	dfs(1,0,1);
	FOR(i,1,n) printf("%d %d\n",dep[i],dfn[i]);
}
/*
11 14
1 2
2 5
4 8
6 7
4 5
8 9
2 3
1 3
2 4
5 6
5 7
4 9
9 10
10 11
*/