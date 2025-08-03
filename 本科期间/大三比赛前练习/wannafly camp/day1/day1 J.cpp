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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
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
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

int fa[maxn][21],dep[maxn];
vector<int> edge[maxn];
int mark[maxn];
int should[maxn];
void dfs(int x,int father,int depth){
	mark[x]=0; dep[x]=depth;
	fa[x][0]=father; int i;
	rep(i,1,20) fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int v:edge[x]) if (v!=father){
		if (mark[v]!=-1) {if (v<x) should[x]=1;}
		else dfs(v,x,depth+1);
	}
}
int lca(int x,int y){
	int i;
	if (dep[x]<dep[y]) swap(x,y);
	rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=fa[x][i];
	if (x==y) return x;
	rREP(i,20) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int distance(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}
int Q[maxn],ST,ED,dis[maxn];
int ans[maxn],U[maxn],V[maxn];
void bfs(int start){
	ST=0; ED=-1;
	Q[++ED]=start; mark[start]=start; dis[start]=0;
	while (ST<=ED){
		int x=Q[ST++];
		for (int v:edge[x]) if (mark[v]!=start)
			mark[v]=start,dis[v]=dis[x]+1,Q[++ED]=v;
	} int i;
	FOR(i,1,q) min_(ans[i],dis[U[i]]+dis[V[i]]);
}
int TaskA() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} FOR(i,1,n) mark[i]=-1;
	dfs(1,0,0);
	scanf("%d",&q);
	FOR(i,1,q){
		scanf("%d%d",&U[i],&V[i]);
		ans[i]=distance(U[i],V[i]);
	}
	FOR(i,1,n) if (should[i]) bfs(i);
	FOR(i,1,q) printf("%d\n",ans[i]);
	return 0;
}
void initialize() {}
int main() {
	// int startTime=clock();
	//initialize
	initialize();
	// debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*

*/