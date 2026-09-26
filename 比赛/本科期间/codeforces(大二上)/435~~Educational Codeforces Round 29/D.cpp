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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int a[maxn],cnt;
struct splay_tree{
	struct node{
		int val,size,son[2];//add=lazy
		bool rev;
		void init(int _val){//开始时T[i].val==a[i-1](线性的); 
			val=_val;size=1;
			rev=son[0]=son[1]=0;
		}
	}T[maxn*2];//内存池 
	int fa[maxn*2],root,tot;
	void pushup(int x){
		T[x].size=1;
		if (T[x].son[0])T[x].size+=T[T[x].son[0]].size;
		if (T[x].son[1])T[x].size+=T[T[x].son[1]].size;
	}
	void pushdown(int x){
		if (x==0) return;
		if (T[x].rev){
			if (T[x].son[0]) T[T[x].son[0]].rev^=1;
			if (T[x].son[1]) T[T[x].son[1]].rev^=1;
			swap(T[x].son[0],T[x].son[1]);
			T[x].rev=0;
		}
	}
	void rotate(int x,int kind){//zig(1->) zag(0<-)都行
		int y=fa[x],z=fa[y];
		T[y].son[!kind]=T[x].son[kind],fa[T[x].son[kind]]=y;
		T[x].son[kind]=y,fa[y]=x;
		T[z].son[T[z].son[1]==y]=x,fa[x]=z;
		pushup(y);
	}
	void splay(int x,int goal){//node x->goal's son
		if (x==goal) return;
		while (fa[x]!=goal){
			int y=fa[x],z=fa[y];
			pushdown(z),pushdown(y),pushdown(x); 
			int rx=T[y].son[0]==x,ry=T[z].son[0]==y;
			if (z==goal) rotate(x,rx);
			else{
				if (rx==ry) rotate(y,ry);
				else rotate(x,rx);
				rotate(x,ry);
			}
		}
		pushup(x);
		if (goal==0) root=x;
	}
	int select(int pos){//getnode
		int u=root;
		pushdown(u);
		while (T[T[u].son[0]].size!=pos){//这里由于头节点有个-INF 所以不-1 
			if (pos<T[T[u].son[0]].size) u=T[u].son[0];
			else{
				pos-=T[T[u].son[0]].size+1;
				u=T[u].son[1];
			}
			pushdown(u);
		}
		return u;
	}
	void reverse(int l,int r){
		int u=select(l-1),v=select(r+1);
		splay(u,0);splay(v,u);
		T[T[v].son[0]].rev^=1;
	}
	void revolve(int l,int r,int x){//l~r->循环往后x位 
		int u=select(r-x),v=select(r+1);
		splay(u,0);splay(v,u);
		int tmp=T[v].son[0];T[v].son[0]=0;
		pushup(v);pushup(u); 
		u=select(l-1),v=select(l);
		splay(u,0);splay(v,u);
		fa[tmp]=v;
		T[v].son[0]=tmp;
		pushup(v);pushup(u);
	}
	int build(int l,int r){
		if (l>r) return 0;
		if (l==r) return l;
		int mid=(l+r)/2;
		T[mid].son[0]=build(l,mid-1);
		T[mid].son[1]=build(mid+1,r);
		fa[T[mid].son[0]]=fa[T[mid].son[1]]=mid;
		pushup(mid);
		return mid;
	}
	void init(int n){
		tot=0;
		int i;//0是虚的;
		T[tot++].init(INF);//空的 
		T[tot++].init(INF);//前后两个-INF节点 
		FOR(i,1,n) T[tot++].init(a[i]);
		T[tot++].init(INF);
		root=build(1,tot-1);
		fa[root]=0;
		fa[0]=0;T[0].son[1]=root;T[0].size=0;
	}
}T;
int root;
int L[maxn],R[maxn];
int main(){
	int i,j,k,n,q,m;
	scanf("%d%d%d",&n,&q,&m);
	FOR(i,1,n) scanf("%d",&a[i]);
	T.init(n);
	FOR(i,1,q){
		int k,l,r;
		scanf("%d%d%d",&k,&l,&r);
		if (k==1) T.revolve(l,r,1);
		if (k==2) T.reverse(l,r);
	}
	FOR(i,1,m){
		int pos;
		scanf("%d",&pos);
		printf("%d ",T.T[T.select(pos)].val);
	}
}
/*
*/
