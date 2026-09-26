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

struct Edges {
	int to; int next;
	Edges(int _to=0,int _next=0):to(_to),next(_next) {}
} edge[maxn*2]; int etot;
int head[maxn];
int fa[maxn];
int id[maxn],dfn[maxn],idtot;
inline void addedge(int u,int v) {
	edge[++etot]=Edges(v,head[u]); head[u]=etot;
}
namespace LCA {//内部和外部dfn不同...
	int dep[maxn];
	int st_dfn[maxn],tot;
	int ST[maxn*2][20];//only L
	void dfs(int x,int f,int d) {
		int i; dep[x]=d;
		st_dfn[x]=++tot; ST[tot][0]=x;
		::id[++idtot]=x; ::dfn[x]=idtot;
		for (i=head[x]; ~i; i=edge[i].next) if (edge[i].to!=f) {
				int v=edge[i].to;
				::fa[v]=x;
				dfs(v,x,d+1);
				ST[++tot][0]=x;
			}
	}
	int t_t[maxn*2];
	inline void initST(int n) {
		int i,j;
		FOR(i,1,n*2) t_t[i]=t_t[i>>1]+1;
		FOR(i,1,n*2) {
			rep(j,1,t_t[i]) {
				int u=ST[i][j-1],v=ST[i-(1<<(j-1))][j-1];
				ST[i][j]=dep[u]<dep[v]?u:v;
			}
		}
	}
	inline int lca(int x,int y) {
		x=st_dfn[x]; y=st_dfn[y];
		if (x>y) swap(x,y);
		int t=t_t[y-x+1]-1;
		x=ST[x+(1<<t)-1][t]; y=ST[y][t];
		return dep[x]<dep[y]?x:y;
	}
	inline int dis(int x,int y) {
		return dep[x]+dep[y]-2*dep[lca(x,y)];
	}
}

vector<int> pos[maxn];
vector<int> point[maxn];
void solve(int x) {
	if (!pos[x].size()) return;
	int u,v; u=v=pos[x][0];
	for (int y:pos[x]) if (LCA::dis(u,y)>LCA::dis(u,v)) v=y;
	point[x].push_back(v); u=v;
	for (int y:pos[x]) if (LCA::dis(u,y)>LCA::dis(u,v)) v=y;
	point[x].push_back(v); u=v;
}

vector<int> V;
int w[maxn];
inline int getid(int x){
	int ret=lower_bound(V.begin(), V.end(), x)-V.begin();
	if (V[ret]==x) return ret+1; return 0;
}
int main() {
	int n,i;
	scanf("%d%d",&n,&q);
	FOR(i,1,n) scanf("%d",&w[i]),V.push_back(w[i]);
	sort(V.begin(), V.end());
	V.erase(unique(V.begin(), V.end()),V.end());
	FOR(i,1,n) w[i]=getid(w[i]);
	// FOR(i,1,n) printf("%d ",w[i]);
	FOR(i,1,n) head[i]=-1;
	FOR(i,1,n-1) {
		int u,v;
		scanf("%d%d",&u,&v);
		addedge(u,v);
		addedge(v,u);
	} LCA::dfs(1,0,0);
	LCA::initST(n);
	FOR(i,1,n) pos[w[i]].push_back(i);
	FOR(i,1,n) solve(i);
	FOR(i,1,q){
		int x,y,ans=0;
		scanf("%d%d",&x,&y);
		x=getid(x); y=getid(y);
		for (int u:point[x]) for (int v:point[y]){
			// printf("%d - %d\n",u,v);
			max_(ans,LCA::dis(u,v));
		}
		printf("%d\n",ans);
	}
}
/*
*/
