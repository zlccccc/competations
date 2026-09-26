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

#define DEBUG1
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
const LL M=2019;
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
int top[maxn],id[maxn],out[maxn],rid[maxn],son[maxn];
void dfs1(int u,int depth){
	int mx=-1; sz[u]=1;
	son[u]=0; dep[u]=depth;
	for (int v:edge[u]){
		if (v==fa[u]) continue;
		dfs1(v,depth+1); sz[u]+=sz[v];
		if (sz[v]>mx) mx=sz[v],son[u]=v;
	}
}
void dfs2(int u,int x){
	top[u]=x; id[u]=++tot; rid[tot]=u;
	if (son[u]) dfs2(son[u],x);
	for (int v:edge[u]){
		if (v==fa[u]||v==son[u]) continue;
		dfs2(v,v);
	} out[u]=tot;
}
int A[maxn],B[maxn];
struct SEG_TREE{
	ll cnt[maxn],val[maxn],lazy[maxn];
	void change(int x,ll v){
		add_(val[x],v*cnt[x]%M); add_(lazy[x],v);
	}
	void pushup(int x){
		val[x]=(val[x<<1]+val[x<<1|1])%M;
	}
	void pushdown(int x){
		if (lazy[x]){
			change(x<<1,lazy[x]);
			change(x<<1|1,lazy[x]);
			lazy[x]=0;
		}
	}
	void build(int x,int L,int R){
		val[x]=lazy[x]=0;
		if (L==R) {cnt[x]=A[L]; val[x]=A[L]*B[L]%M; return;}
		int mid=(L+R)/2;
		build(x<<1,L,mid);
		build(x<<1|1,mid+1,R);
		cnt[x]=(cnt[x<<1]+cnt[x<<1|1])%M;
		pushup(x);
	}
	void update(int x,int l,int r,int val,int L,int R){
		if (l<=L&&R<=r) {change(x,val); return;}
		int mid=(L+R)/2;
		pushdown(x);
		if (l<=mid) update(x<<1,l,r,val,L,mid);
		if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
		pushup(x);
	}
	int query(int x,int l,int r,int L,int R){
		if (l<=L&&R<=r) return val[x];
		int mid=(L+R)/2,ret=0;
		pushdown(x);
		if (l<=mid) add_(ret,query(x<<1,l,r,L,mid));
		if (mid<r) add_(ret,query(x<<1|1,l,r,mid+1,R));
		pushup(x);
		return ret;
	}
}T1,T2;
void update(int x,int y,int val){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		T1.update(1,id[top[x]],id[x],val,1,n);
		T2.update(1,id[top[x]],id[x],val,1,n);
		x=fa[top[x]];
	} if (dep[x]>dep[y]) swap(x,y);
	if (son[x]) {
		T1.update(1,id[son[x]],id[y],val,1,n);
		T2.update(1,id[son[x]],id[y],val,1,n);
	}
}
int c[maxn];
int TaskA() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,2,n) {
		scanf("%d%d",&fa[i],&c[i]);
		edge[fa[i]].push_back(i);
	} dfs1(1,1); dfs2(1,1);
	FOR(i,1,n) B[id[i]]=c[i]%M;
	FOR(i,1,n) A[id[i]]=sz[i]%M;
	T1.build(1,1,n);
	FOR(i,1,n) A[id[i]]=(ll)sz[i]%M*sz[i]%M;
	T2.build(1,1,n);
	FOR(i,1,m) {
		char op[10]; int x,u,v,val;
		scanf("%s",op);
		if (op[0]=='A'){
			scanf("%d",&x);
			ll ans=0;
			ans=((ll)T1.query(1,id[x],out[x],1,n)*(sz[x]%M)-T2.query(1,id[x],out[x],1,n))%M;
			mod_(ans);
			printf("%lld\n",ans);
		}else if (op[0]=='I'){
			scanf("%d%d%d",&u,&v,&val);
			if (u==v) continue;
			update(u,v,val);
		}
	}
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
*/
