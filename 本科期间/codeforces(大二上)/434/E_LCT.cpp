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
#include <unordered_map>
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
const LL maxn=5e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct LCT{
	struct node{
		int son[2],size;
		int add,val;
		LL sum;
		node(){son[0]=son[1]=val=sum=0;size=1;}
	}T[maxn];
	bool root[maxn];
	int fa[maxn];
	void Add(int x,int val){
		T[x].val+=val;
		T[x].sum+=val*T[x].size;
		T[x].add+=val;
	}
	void pushup(int x){
		T[x].sum=T[x].val;T[x].size=1;
		if (T[x].son[0]) T[x].sum+=T[T[x].son[0]].sum,T[x].size+=T[T[x].son[0]].size;
		if (T[x].son[1]) T[x].sum+=T[T[x].son[1]].sum,T[x].size+=T[T[x].son[1]].size;
	}
	void pushdown(int x){
		if (T[x].add){
			if (T[x].son[0]) Add(T[x].son[0],T[x].add);
			if (T[x].son[1]) Add(T[x].son[1],T[x].add);
			T[x].add=0;
		}
	}
	void rotate(int x,int kind){
		int y=fa[x],z=fa[y];
		T[y].son[!kind]=T[x].son[kind],fa[T[x].son[kind]]=y;
		T[x].son[kind]=y,fa[y]=x;
		if (root[y]) {root[x]=true;root[y]=false;} 
		else T[z].son[T[z].son[1]==y]=x;
		fa[x]=z;
		pushup(y);
	}
	void Prechange(int x){
		if (!root[x]) Prechange(fa[x]);
		pushdown(x);
	}
	void splay(int x){//to root
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
		}
		pushup(x);
	}
	int access(int x){//只有这条链上的是mark的 
		int y=0;
		for (;x;x=fa[x]){
			splay(x);
			root[T[x].son[1]]=true;
			T[x].son[1]=y;
			root[y]=false;
			y=x;
			pushup(x);
		}
		return y;
	}
	void add(int x){
		access(x);
		splay(x); 
		Add(x,1);
		T[x].sum--;T[x].val--;
	}
	LL ask(int x){
		access(x);
		splay(x);
		return T[x].sum;
	}
}T;
vector<int> edge[maxn],now[maxn];
LL ans[maxn];
void check(int x,int dep){//check
	printf("down %d dep=%d\n",x,dep);
	for (int v:edge[x]) check(v,dep+1);
	printf("up\n");
}
void dfs(int x,int depth){
	now[depth].push_back(x);
	for (int v:edge[x]) dfs(v,depth+1);
}
int root;
int main(){
	int n,m,i,j;
	scanf("%d",&n);
	FOR(i,1,n){
		scanf("%d",&T.fa[i]);
		if (T.fa[i]==0) root=i;
		else edge[T.fa[i]].push_back(i);
	}
	FOR(i,1,n) T.root[i]=1;
	dfs(root,0);
	FOR(i,1,n){
		for (int v:now[i]) T.add(v);
		for (int v:now[i]) ans[v]=T.ask(v);
	}
	FOR(i,1,n) printf("%I64d ",ans[i]);
}
/*
*/
