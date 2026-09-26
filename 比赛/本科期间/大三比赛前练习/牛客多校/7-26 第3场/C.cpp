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
const LL maxn=2e5+7;
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

struct splay_tree {
	struct node {
		int val,size,son[2];
		bool rev;
		void init(int _val) {
			val=_val; size=1;
			son[0]=son[1]=0;
		}
	} T[maxn];
	int fa[maxn],root,tot;
	void pushup(int x) {
		T[x].size=1;
		if (T[x].son[0]) T[x].size+=T[T[x].son[0]].size;
		if (T[x].son[1]) T[x].size+=T[T[x].son[1]].size;
	}
	void pushdown(int x) {
		if (!x) return;
		if (T[x].rev) {
			if (T[x].son[0]) T[T[x].son[0]].rev^=1;
			if (T[x].son[1]) T[T[x].son[1]].rev^=1;
			swap(T[x].son[0],T[x].son[1]);
			T[x].rev=0;
		}
	}
	void rotate(int x,int kind) { //zig(1->) zag(0<-)都行
		int y=fa[x],z=fa[y];
		T[y].son[!kind]=T[x].son[kind],fa[T[x].son[kind]]=y;
		T[x].son[kind]=y,fa[y]=x;
		T[z].son[T[z].son[1]==y]=x,fa[x]=z;
		pushup(y);
	}
	void splay(int x,int goal) { //node x->goal's son
		if (x==goal) return;
		while (fa[x]!=goal) {
			int y=fa[x],z=fa[y];
			pushdown(z),pushdown(y),pushdown(x);
			int rx=T[y].son[0]==x,ry=T[z].son[0]==y;
			if (z==goal) rotate(x,rx);
			else {
				if (rx==ry) rotate(y,ry);
				else rotate(x,rx);
				rotate(x,ry);
			}
		}
		pushup(x);
		if (goal==0) root=x;
	}
	int select(int pos) { //getnode
		int u=root;
		pushdown(u);
		while (T[T[u].son[0]].size!=pos) {
			if (pos<T[T[u].son[0]].size) u=T[u].son[0];
			else {
				pos-=T[T[u].son[0]].size+1;
				u=T[u].son[1];
			} pushdown(u);
		} return u;
	}
	void revolve(int l,int r,int x) { //l~r->循环往后x位
		int u=select(r-x),v=select(r+1);
		splay(u,0); splay(v,u);
		int tmp=T[v].son[0]; T[v].son[0]=0;
		pushup(v); pushup(u);
		u=select(l-1),v=select(l);
		splay(u,0); splay(v,u);
		fa[tmp]=v;
		T[v].son[0]=tmp;
		pushup(v); pushup(u);
	}
	int build(int l,int r) { //add_list
		if (l>r) return 0;
		int mid=(l+r)/2;
		T[mid].init(mid);
		int ls=build(l,mid-1);
		int rs=build(mid+1,r);
		if (ls) fa[ls]=mid,T[mid].son[0]=ls;
		if (rs) fa[rs]=mid,T[mid].son[1]=rs;
		pushup(mid);
		return mid;
	}
	void init(int n) {
		root=build(1,n+2);
		fa[root]=0; fa[0]=0;
		T[0].son[1]=root; T[0].size=0;
	}
	void dfs(int x=0,int n=100){
		if (!x) x=root;
		if (T[x].son[0]) dfs(T[x].son[0],n);
		if (1<=x-1&&x-1<=n) printf("%d ",x-1);
		if (T[x].son[1]) dfs(T[x].son[1],n);
	}
} T;
int TaskA() {
	int i;
	scanf("%d%d",&n,&m);
	T.init(n);
	// T.dfs(0,n); puts("");
	REP(i,m){
		int l,cnt;
		scanf("%d%d",&l,&cnt);
		T.revolve(1,l+cnt-1,cnt);
		// T.dfs(0,n); puts("");
	}
	T.dfs(0,n); puts("");
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
5 2
2 3
2 3 
*/
