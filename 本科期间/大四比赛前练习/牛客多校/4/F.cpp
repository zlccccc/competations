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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}


int A[maxn];
struct splay_tree {
	static const int maxn=1e5+7;
	struct node {
		int val,max,size,son[2];//add=lazy
		bool rev;
		void init(int _val) { //开始时T[i].val==a[i-1](线性的);
			val=max=_val; size=1;
			son[0]=son[1]=0; rev=0;
		}
	} T[maxn]; //内存池
	int fa[maxn],tot,root;
	int getroot(int x) {
		while (fa[x]) x=fa[x];
		return x;
	}
	void pushup(int x) {
		T[x].max=T[x].val; T[x].size=1;
		if (T[x].son[0]) {
			T[x].max=max(T[x].max,T[T[x].son[0]].max);
			T[x].size+=T[T[x].son[0]].size;
		}
		if (T[x].son[1]) {
			T[x].max=max(T[x].max,T[T[x].son[1]].max);
			T[x].size+=T[T[x].son[1]].size;
		}
	}
	void pushdown(int x) {
		if (x==0) return;
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
		} pushup(x);
		if (goal==0) root=x;
	}
	int select(int pos) { //getnode
		int u=root;
		pushdown(u);
		while (T[T[u].son[0]].size!=pos) { //这里由于头节点有个-INF 所以不-1
			if (pos<T[T[u].son[0]].size) u=T[u].son[0];
			else {
				pos-=T[T[u].son[0]].size+1;
				u=T[u].son[1];
			} pushdown(u);
		} return u;
	}
//下面是自己写的一点常用?函数
	void delfree(int x) {
		if (x==0) return;
		bufs++; if (bufs==maxn) bufs=1;
		nodebuff[bufs]=x;
		delfree(T[x].son[0]);
		delfree(T[x].son[1]);
	}
	int nodebuff[maxn],bufs;//bufs:position
	int build(int l,int r) { //add_list
		if (l>r) return 0;
		++tot; if (tot==maxn) tot=1;
		int ret=nodebuff[tot],mid=(l+r)/2;
		T[ret].init(A[mid]);
		if (l==r) return ret;
		int ls=build(l,mid-1),rs=build(mid+1,r);
		if (ls) fa[ls]=ret,T[ret].son[0]=ls;
		if (rs) fa[rs]=ret,T[ret].son[1]=rs;
		pushup(ret);
		return ret;
	}
	void init(int n) {
		int i; tot=0;
		REP(i,maxn) nodebuff[i]=i;
		rFOR(i,1,n) A[i+1]=A[i];
		A[1]=0; A[n+2]=INF;//no use(只用做cur-1时有作用)
		root=build(1,n+2);
		fa[root]=0;
	}
	void print(int x) {
		if (T[x].son[0]) print(T[x].son[0]);
		printf("%d ",T[x].val);
		if (T[x].son[1]) print(T[x].son[1]);
	}
	void print2(int x) {
		if (T[x].son[0]) print2(T[x].son[0]);
		printf("id=%d val=%d (%d %d); max=%d\n",x,T[x].val,T[x].son[0],T[x].son[1],T[x].max);
		if (T[x].son[1]) print2(T[x].son[1]);
	}

	int getnxtmax(int val) {
		int u=root;
		while (T[u].max>val) {
			if (T[T[u].son[0]].max<=val&&T[u].val>val) break;
			if (T[T[u].son[0]].max<=val) u=T[u].son[1];
			else u=T[u].son[0];
		} return u;
	}
	void solvemerge(int l,int m,int r,int n) {
		assert(l==1);
		//cur right
		int u=select(r),v=select(n+1);
		splay(u,0); splay(v,u);
		int tmpr=T[v].son[0];
		T[v].son[0]=0;//to_right;
		pushup(v); pushup(u);
		//cut left
		u=select(0); v=select(m+1);
		splay(u,0); splay(v,u);
		int tmpl=T[v].son[0];
		T[v].son[0]=0;//left
		pushup(v); pushup(u);
		int value=0;
		vector<int> P;//id; 相对位置(block); 剩下splay即可
		while (1) {
			int nxtid=getnxtmax(value),nxtval=T[nxtid].val;//start_position
			if (value>=T[tmpl].max) break;//剩下全是ok的
			if (value) {//cut
				v=nxtid; splay(v,u);
				int tmpid=T[v].son[0];
				T[v].son[0]=0;
				P.push_back(tmpid);//this_block
				pushup(v); pushup(u);
			}
			value=nxtval;
			if (value==INF) break;//last
		}
		//back_left
		u=select(0); v=select(1);
		splay(u,0); splay(v,u);
		T[v].son[0]=tmpl; fa[tmpl]=v;//left
		pushup(v); pushup(u);
		//insert middle
		for (int nowid:P) {
			int v=getnxtmax(T[nowid].max);//right
			splay(v,0);
			u=select(T[T[v].son[0]].size-1);
			splay(u,0); splay(v,u);
			T[v].son[0]=nowid; fa[nowid]=v;//left
			pushup(v); pushup(u);
		}
		//link right directly
		u=select(r),v=select(r+1);
		splay(u,0); splay(v,u);
		T[v].son[0]=tmpr; fa[tmpr]=v;
		pushup(v); pushup(u);
	}
	void printkth(int pos) {
		int u=select(pos);
		printf("%d\n",T[u].val);
	}
} T;
int main() {
	int n,q;
	int i;
	scanf("%d%d",&n,&q);
	FOR(i,1,n) scanf("%d",&A[i]);
	T.init(n);
	FOR(i,1,q) {
		int o; scanf("%d",&o);
		if (o==1) {
			int l,m,r;
			scanf("%d%d%d",&l,&m,&r);
			T.solvemerge(l,m,r,n);
		} else {
			int x; scanf("%d",&x);
			T.printkth(x);
		}
	}
}
/*
5 3
2 3 1 4 5
2 3
1 1 3 5
2 3

5 3
2 3 1 1 2
2 3
1 1 3 5
2 3
*/