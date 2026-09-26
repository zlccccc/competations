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

struct LCT{
	struct node{
		int son[2],size;
		bool rev;
		void init(){
			son[0]=son[1]=rev=0;
			size=1;
		}
	}T[maxn];
	bool root[maxn];
	int fa[maxn];
	void Reverse(int x){
		T[x].rev^=1;
		swap(T[x].son[0],T[x].son[1]);
	}
	void pushup(int x){
		T[x].size=1;
		if (T[x].son[0]) T[x].size+=T[T[x].son[0]].size;
		if (T[x].son[1]) T[x].size+=T[T[x].son[1]].size;
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
		T[x].son[kind]=y,fa[y]=x;
		if (root[y]) {root[x]=true; root[y]=false;}
		else T[z].son[T[z].son[1]==y]=x;
		fa[x]=z;
		pushup(y);
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
			else {
				if (rx==ry) rotate(y,ry);
				else rotate(x,rx);
				rotate(x,ry);
			}
		}
		pushup(x);
	}
	int access(int x){
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
		if (judge(u,v)) return 1;
		makeroot(u); fa[u]=v;
		return 0;
	}
	bool cut(int u,int v){
		makeroot(u);
		splay(v);
		fa[T[v].son[0]]=fa[v];
		fa[v]=0;
		root[T[v].son[0]]=true;
		T[v].son[0]=0;
		pushup(v);
		return 0;
	}
}lct;
int main() {
	scanf("%d",&n);
	int i;
	FOR(i,1,n) lct.root[i]=1;
	while (1){
		char op[2]; int u,v;
		fflush(stdout);
		scanf("%s",op);
		if (op[0]=='E') return 0; 
		scanf("%d%d",&u,&v);
		if (op[0]=='C') lct.link(u,v);
		if (op[0]=='D') lct.cut(u,v);
		if (op[0]=='T') {
			if (lct.judge(u,v)) puts("YES");
			else puts("NO");
		}
	}
}
/*
*/
