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
const LL M=1e9+7;
const LL maxn=6e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=M;}
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

struct LCT{
	struct node{
		int son[2];
		pii min,val;
		bool rev;
		void init(pii _val){
			son[0]=son[1]=rev=0;
			min=val=_val;
		}
	}T[maxn];
	bool root[maxn]; int fa[maxn];
	void Reverse(int x){
		T[x].rev^=1;
		swap(T[x].son[0],T[x].son[1]);
	}
	void pushup(int x){
		T[x].min=T[x].val;
		if (T[x].son[0]) T[x].min=min(T[x].min,T[T[x].son[0]].min);
		if (T[x].son[1]) T[x].min=min(T[x].min,T[T[x].son[1]].min);
	}
	void pushdown(int x){
		if (T[x].rev){
			if (T[x].son[0]) Reverse(T[x].son[0]);
			if (T[x].son[1]) Reverse(T[x].son[1]);
			T[x].rev=0;
		}
	}
	void rotate(int x,int kind){
		int y=fa[x],z=fa[y];
		T[y].son[!kind]=T[x].son[kind],fa[T[x].son[kind]]=y;
		T[x].son[kind]=y; fa[y]=x;
		if (root[y]) {root[x]=1,root[y]=0;}
		else T[z].son[T[z].son[1]==y]=x;
		fa[x]=z; pushup(y);
	}
	void Prechange(int x){
		if (!root[x]) Prechange(fa[x]);
		pushdown(x);
	}
	void splay(int x){
		Prechange(x);
		while (!root[x]){
			int y=fa[x],z=fa[y];
			int rx=T[y].son[0]==x,ry=T[z].son[0]==y;
			if (root[y]) rotate(x,rx);
			else{
				if (rx==ry) rotate(y,ry);
				else rotate(x,rx);
				rotate(x,ry);
			}
		} pushup(x);
	}
	int access(int x){
		int y=0;
		for (;x;x=fa[x]){
			splay(x);
			root[T[x].son[1]]=true;
			T[x].son[1]=y;
			root[y]=false;
			y=x; pushup(x);
		}return y;
	}
	bool judge(int u,int v){
		while (fa[u]) u=fa[u];
		while (fa[v]) v=fa[v];
		return u==v;
	}
	void makeroot(int x){
		access(x);
		splay(x);
		Reverse(x);
	}
	bool link(int u,int v){
		assert(!judge(u,v));
		makeroot(u); fa[u]=v;
		return 0;
	}
	bool cut(int u,int v){
		assert(judge(u,v));
		makeroot(u); splay(v);
		fa[T[v].son[0]]=fa[v]; fa[v]=0;
		root[T[v].son[0]]=1; T[v].son[0]=0;
		pushup(v); return 0;
	}
	pii query(int u,int v){
		makeroot(u);
		access(v);
		splay(v);
		return T[v].min;
	}
}lct;
struct edges{
	int u,v,id;
	edges(int u=0,int v=0,int id=0):u(u),v(v),id(id){};
}edge[maxn];
int Ans[maxn];
int cnt[maxn];
inline int lowbit(int x){return x&-x;}
inline void add(int x,int val){
	debug("add: %d %d\n",x,val);
	for (;x<=n;x+=lowbit(x)) cnt[x]+=val;
}
inline int query(int x){
	int ret=0;
	for (;x;x-=lowbit(x)) ret+=cnt[x];
	return ret;
}
int TaskA() {
	int i;
	scanf("%d%*d%d",&n,&m);
	FOR(i,1,m) {
		int u,v;
		scanf("%d%d",&u,&v);
		if (u>v) swap(u,v);
		edge[i]=edges(u,v,-i);
	} scanf("%d",&q);
	FOR(i,1,q){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[i+m]=edges(u,v,i);
	} sort(edge+1,edge+m+q+1,[](edges &A,edges &B){
		if (A.v!=B.v) return A.v<B.v;
		return A.id<B.id;
	});
	FOR(i,1,n) lct.T[i].init(make_pair(INF,-1));
	FOR(i,1,n+m) lct.root[i]=1;
	FOR(i,1,m+q){
		int u=edge[i].u,v=edge[i].v,id=edge[i].id;
		if (id<0){
			id=n-id;
			if (lct.judge(u,v)){
				pii now=lct.query(u,v);
				debug("   judge : %d %d (%d)\n",u,v,now.first);
				if (now.first>=u) continue;
				int x=now.second;
				lct.cut(u,x); lct.cut(v,x);
				add(now.first,-1);
			}
			debug("   judge : %d %d\n",u,v);
			add(u,1);
			lct.T[id].init(make_pair(u,id));
			lct.link(u,id); lct.link(v,id);
		}else{
			Ans[id]=v-u+1-query(v)+query(u-1);
			debug("  query : %d %d  %d\n",u,v,Ans[id]);
		}
	}FOR(i,1,q) printf("%d\n",Ans[i]);
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
