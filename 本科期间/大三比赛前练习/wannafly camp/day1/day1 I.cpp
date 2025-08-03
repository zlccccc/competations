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
#ifdef DEBUG1
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
const LL maxn=2e5+7;
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

vector<int> edge[maxn];
int fa[maxn],dep[maxn],sz[maxn],tot;
int top[maxn],id[maxn],rid[maxn],son[maxn];
void dfs1(int u,int father,int depth){
	int mx=-1; sz[u]=1;
	fa[u]=father; son[u]=0; dep[u]=depth;
	for (int v:edge[u]){
		if (v==father) continue;
		dfs1(v,u,depth+1); sz[u]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[u]=v;
	}
}
void dfs2(int u,int x){
	top[u]=x; id[u]=++tot; rid[tot]=u;
	if (son[u]) dfs2(son[u],x);
	for (int v:edge[u]){
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
int ans[maxn];
int cnt[maxn*4],lazy[maxn*4];
void build(int x,int L,int R){
	cnt[x]=q; lazy[x]=0;
	if (L==R) return;
	int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
}
void change(int x,int val){
	cnt[x]-=val; lazy[x]+=val;
}
void pushdown(int x){
	if (lazy[x]){
		change(x<<1,lazy[x]);
		change(x<<1|1,lazy[x]);
		lazy[x]=0;
	}
}
void update(int x,int l,int r,int color,int L,int R){
	if (l>r) return;
	if (l<=L&&R<=r){
		if (cnt[x]>1) {change(x,1); return;}
		if (L==R) {ans[rid[L]]=color; cnt[x]=INF; return;}
	} int mid=(L+R)/2;
	pushdown(x);
	if (l<=mid) update(x<<1,l,r,color,L,mid);
	if (mid<r) update(x<<1|1,l,r,color,mid+1,R);
	cnt[x]=min(cnt[x<<1],cnt[x<<1|1]);
}
void Update(int x,int y,int color){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,id[top[x]],id[x],color,1,n);
		x=fa[top[x]];
	} if (dep[x]>dep[y]) swap(x,y);
	update(1,id[x],id[y],color,1,n);
}
int X[maxn],Y[maxn],C[maxn];
int TaskA() {
	int i;
	scanf("%d%d%d",&n,&m,&q);
	FOR(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs1(1,0,1); dfs2(1,1); assert(tot==n);
	FOR(i,1,m) scanf("%d%d%d",&X[i],&Y[i],&C[i]);
	build(1,1,n);
	rFOR(i,1,m) Update(X[i],Y[i],C[i]);
	FOR(i,1,n) printf("%d%c",ans[i]," \n"[i==n]);
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
3 3 3
1 2
2 3
1 2 1
2 3 2
1 3 3
*/