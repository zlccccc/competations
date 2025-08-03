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
const LL maxn=2e5+107;
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

int n,q;
inline int lowbit(int x) {return x&-x;}
int sum[maxn*2];
void update(int x,int val){
	// printf("upd: %d %d\n",x,val);
	for (;x<=n+q;x+=lowbit(x)) sum[x]+=val;
}
int getCnt(int x){
	int ret=0;
	// printf("getCnt: %d\n",x);
	for (;x;x-=lowbit(x)) ret+=sum[x];
	return ret;
}
set<pair<pair<int,int>,int> > POS;
void update(int l,int r,int x) {
	// printf("update: %d %d: %d\n",l,r,x);
	auto final=make_pair(make_pair(l,r),x);
	while (l<=r) {
		auto it=POS.lower_bound(make_pair(make_pair(l,INF),0)); it--;
		// printf("%d ",it->second);
		auto now=*it; POS.erase(it);
		// printf("%d %d %d\n",now.first.first,now.first.second,now.second);
		int nxtl=now.first.second+1;
		if (now.first.first<l) {
			pair<int,int> remain;
			remain.first=now.first.first;
			remain.second=l-1;
			if (remain.first<=remain.second)
				POS.insert(make_pair(remain,now.second));
		} if (now.first.second>r) {
			pair<int,int> remain;
			remain.first=r+1;
			remain.second=now.first.second;
			if (remain.first<=remain.second)
				POS.insert(make_pair(remain,now.second));
			nxtl=r+1;
		}
		update(now.second,-(nxtl-l));
		update(x,nxtl-l);
		l=nxtl;
	} POS.insert(final);
	// puts("after:");
	// for (auto now:POS) printf(" %d-%d : %d\n",now.first.first,now.first.second,now.second);
}
int id[maxn],sz[maxn],tot;
int son[maxn],top[maxn],fa[maxn],dep[maxn];
vector<int> edge[maxn];
inline int getPos(int x){
	x=id[x];
	auto it=POS.lower_bound(make_pair(make_pair(x,INF),0)); it--;
	return it->second;
}
void dfs1(int x,int from,int depth) {
	sz[x]=1; fa[x]=from; dep[x]=depth;
	for (int v:edge[x]) if (v!=fa[x]) {
			dfs1(v,x,depth+1); sz[x]+=sz[v];
			if (!son[x]||sz[son[x]]<sz[v]) son[x]=v;
		}
}
void dfs2(int x,int t) {
	id[x]=++tot; top[x]=t;
	if (son[x]) dfs2(son[x],t);
	for (int v:edge[x]) if (v!=fa[x]&&v!=son[x])
			dfs2(v,v);
}
void change(int x,int y,int val) { //id
	while (top[x]!=top[y]) {
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		update(id[top[x]],id[x],val); x=fa[top[x]];
	} if (dep[x]>dep[y]) swap(x,y);
	update(id[x],id[y],val);
}
int lca(int x,int y) {
	while (top[x]!=top[y]) {
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	} if (dep[x]>dep[y]) swap(x,y);
	return x;
}
int len(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}
int lsthead[maxn*2];
char op[10];
int now;
int getposition(int x){
	int pos=getPos(x);
	int ret=getCnt(pos-1);
	ret+=len(x,lsthead[pos]);
	return ret+1;//self
}
int main() {
	int i;
	scanf("%d%d",&n,&q);
	FOR(i,1,n-1) {
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} dfs1(1,0,1); dfs2(1,1);
	now=1; POS.insert(make_pair(make_pair(1,n),n+q+1));
	FOR(i,2,n) {
		change(now,i,i);
		lsthead[i]=now; now=i;
	}
	// FOR(i,1,n) printf("%d ",id[i]); puts("<- id");
	// FOR(i,1,n) printf("%d ",lsthead[i]); puts("<- lsthead");
	FOR(i,1,q) {
		int x,y;
		scanf("%s",op);
		if (op[0]=='u') {
			scanf("%d",&x);
			change(now,x,i+n);
			lsthead[i+n]=now; now=x;
		} else if (op[0]=='w'){
			scanf("%d",&x);
			printf("%d\n",getposition(x));
		} else {
			scanf("%d%d",&x,&y);
			if (getposition(x)<getposition(y)) printf("%d\n",x);
			else printf("%d\n",y);
		}
	}
}
/*
*/