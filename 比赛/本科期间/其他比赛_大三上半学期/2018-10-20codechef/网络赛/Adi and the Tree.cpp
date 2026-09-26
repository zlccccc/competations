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

vector<int> edge[maxn];
int fa[maxn],son[maxn],sz[maxn],top[maxn],id[maxn],dep[maxn];
int tot;
void dfs1(int u,int from,int depth){
	int mx=-1;
	sz[u]=1;fa[u]=from;dep[u]=depth;son[u]=0;
	for (int v:edge[u]){
		if (v==from) continue;
		dfs1(v,u,depth+1);
		sz[u]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[u]=v;
	}
}
void dfs2(int u,int x){
	top[u]=x;id[u]=++tot;
	if (son[u]) dfs2(son[u],x);
	for (int v:edge[u]){
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
int lazy[maxn*4],sum[maxn*4];
void change(int x,int ALL){
	sum[x]=ALL-sum[x]; lazy[x]^=1;
}
void update(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r){
		change(x,R-L+1);
		return;
	} int mid=(L+R)/2;
	if (lazy[x]) {
		change(x<<1,mid-L+1);
		change(x<<1|1,R-mid);
		lazy[x]=0;
	} if (l<=mid) update(x<<1,l,r,L,mid);
	if (mid<r) update(x<<1|1,l,r,mid+1,R);
	sum[x]=sum[x<<1]+sum[x<<1|1];
}
void Change(int x,int y){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,id[top[x]],id[x],1,tot);
		x=fa[top[x]];
	} if (dep[x]>dep[y]) swap(x,y);
	if (son[x]) update(1,id[son[x]],id[y],1,tot);
}
int main() {
	int T,_; T=1;
	// scanf("%d",&T);
	FOR(_,1,T){
		int i;
		scanf("%d",&n);
		FOR(i,1,n-1){
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		} dfs1(1,0,0); dfs2(1,0);
		scanf("%d",&q);
		while (q--){
			int x,y;
			scanf("%d%d",&x,&y);
			Change(x,y);
			printf("%d\n",sum[1]);
		}
	}
}
/*
*/
