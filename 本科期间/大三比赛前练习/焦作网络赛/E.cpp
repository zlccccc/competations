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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

ull sum[maxn<<2],mul[maxn<<2],add[maxn<<2];
int len[maxn<<2];
void changeMul(int x,ull val) {
	sum[x]-=add[x]*len[x];//every_number
	add[x]*=val; sum[x]*=val; mul[x]*=val;
	sum[x]+=add[x]*len[x];
}
void changeAdd(int x,ull val) {
	add[x]+=val;
	sum[x]+=val*len[x];
}
int op; ull val,ans;
void pushdown(int x) {
	if (mul[x]!=1) {
		changeMul(x<<1,mul[x]);
		changeMul(x<<1|1,mul[x]);
		mul[x]=1;
	}
	if (add[x]) {
		changeAdd(x<<1,add[x]);
		changeAdd(x<<1|1,add[x]);
		add[x]=0;
	}
}
void pushup(int x) {
	mul[x]=1; add[x]=0;
	sum[x]=sum[x<<1]+sum[x<<1|1];
}
void update(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) {
		if (op==1) changeMul(x,val);
		if (op==2) changeAdd(x,val);
		if (op==3) changeMul(x,-1ull),changeAdd(x,-1ull);
		if (op==4) ans+=sum[x];
		return;
	} pushdown(x);
	int mid=(L+R)/2;
	if (l<=mid) update(x<<1,l,r,L,mid);
	if (mid<r) update(x<<1|1,l,r,mid+1,R);
	pushup(x);
	// printf("  x=%d %d %d %d %d; sum=%llu mul=%llu\n",x,l,r,L,R,sum[x],mul[x]);
}
void build(int x,int L,int R){
	sum[x]=0; mul[x]=1; add[x]=0; len[x]=(R-L+1);
	if (L==R) return;
	int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
}

vector<int> edge[maxn];
int dep[maxn],sz[maxn],fa[maxn],son[maxn];
int top[maxn],id[maxn],tot;
void dfs1(int u,int from,int depth) {
	int mx=-1;
	sz[u]=1; fa[u]=from; dep[u]=depth; son[u]=0;
	for (int v:edge[u]) {
		if (v==from) continue;
		dfs1(v,u,depth+1);
		sz[u]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[u]=v;
	}
}
void dfs2(int u,int x) {
	top[u]=x; id[u]=++tot;
	if (son[u]) dfs2(son[u],x);
	for (int v:edge[u]) {
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	}
}
void Update(int x,int y){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,id[top[x]],id[x],1,tot);
		x=fa[top[x]];
	} if (dep[x]>dep[y]) swap(x,y);
	update(1,id[x],id[y],1,tot);
}

int main() {
	while (~scanf("%d",&n)) {
		int i; tot=0;
		FOR(i,1,n) edge[i].clear();
		FOR(i,2,n) {
			scanf("%d",&fa[i]);
			edge[fa[i]].push_back(i);
		} dfs1(1,0,1); dfs2(1,1);
		build(1,1,n);
		// FOR(i,1,n) printf("%d ",id[i]); puts("<- id");
		scanf("%d",&q);
		while (q--){
			int u,v;
			scanf("%d%d%d",&op,&u,&v);
			if (op==1||op==2) scanf("%llu",&val);
			if (op==4) ans=0;
			Update(u,v);
			if (op==4) printf("%llu\n",ans);
		}
	}
}
/*
*/
