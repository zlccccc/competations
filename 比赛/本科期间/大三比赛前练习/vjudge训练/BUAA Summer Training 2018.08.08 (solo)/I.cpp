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
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=4e6+4007;
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
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

struct splay_ {
	int A[maxn];
	struct node {
		int val,son[2],size;
		bool rev;
		void init(int _val) { //开始时T[i].val==a[i-1](线性的);
			val=_val; size=1;
			rev=0; son[0]=son[1]=0;
		}
	} T[maxn];
	int fa[maxn],root,tot;
	void pushup(int x) {
		T[x].size=1;
		if (T[x].son[0]) T[x].size+=T[T[x].son[0]].size;
		if (T[x].son[1]) T[x].size+=T[T[x].son[1]].size;
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
	void rotate(int x,int kind) {
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
	int select(int pos) {
		int u=root;
		pushdown(u);
		while (T[T[u].son[0]].size!=pos) { //这里由于头节点有个-INF 所以不-1
			if (pos<T[T[u].son[0]].size) u=T[u].son[0];
			else {
				pos-=T[T[u].son[0]].size+1;
				u=T[u].son[1];
			} pushdown(u);
		}
		return u;
	}
	void cut(int l,int r) {
		int u=select(l-1),v=select(r+1);
		splay(u,0); splay(v,u);
		T[v].son[0]=0;
		pushup(v); pushup(u);
	}
	void insert(int x,int val){
		x--;
		int u=select(x),v=select(x+1);
		splay(u,0); splay(v,u);
        ++tot; T[tot].init(val);
        fa[tot]=v; T[v].son[0]=tot;
		pushup(v);pushup(u);
	}
	int build(int l,int r) { //add_list
		if (l>r) return 0;
		int mid=(l+r)/2,ret=++tot;
		T[ret].init(A[mid]);
		if (l==r) return ret;
		int ls=build(l,mid-1);
		int rs=build(mid+1,r);
		if (ls) fa[ls]=ret,T[ret].son[0]=ls;
		if (rs) fa[rs]=ret,T[ret].son[1]=rs;
		pushup(ret);
		return ret;
	}
	void init(int n) {
		int i; tot=0;
		rFOR(i,1,n) A[i+1]=i+1000;
		A[1]=A[n+2]=-INF;
		root=build(1,n+2);
		fa[root]=0; T[0].init(-INF);
		fa[0]=0; T[0].son[1]=root; T[0].size=0;
	}
	void dfs(int x,int A[],int &tot){
		if (!x) return;
		dfs(T[x].son[0],A,tot);
		A[++tot]=T[x].val;
		dfs(T[x].son[1],A,tot);
	}
} splay;

const int MAX=4e6;
char op[2][maxn][2],c[2][maxn][2];
ll pos[2][maxn];
vector<ll> V;
map<ll,int> MP;
ll base,more;
void solve(char op[maxn][2],char c[maxn][2],ll pos[maxn],int A[],int n) {
	int i;
	int tot=0;
	splay.init(MAX);
	FOR(i,1,n){
		if (op[i][0]=='D') splay.cut(MP[pos[i]],MP[pos[i]]);
		else splay.insert(MP[pos[i]],c[i][0]);
	} splay.dfs(splay.root,A,tot);
}
int A[maxn],B[maxn];
int main() {
	int i=0,j,n[2]={0,0};
	REP(j,2){
		i=0;
		while (1) {
			i++; scanf("%s",op[j][i]);
			if (op[j][i][0]=='E') break;
			if (op[j][i][0]=='D') scanf("%lld",&pos[j][i]);
			if (op[j][i][0]=='I') scanf("%lld%s",&pos[j][i],c[j][i]);
			n[j]++; V.push_back(pos[j][i]);
		}
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(), V.end()),V.end());
	base=0; more=0;
	REP(i,(int)V.size()) {
		if (V[i]-base>2000) base=V[i],more+=2000;
		MP[V[i]]=V[i]-base+more;
	}
	solve(op[0],c[0],pos[0],A,n[0]);
	solve(op[1],c[1],pos[1],B,n[1]);
	// FOR(i,1,MAX) printf("%d ",A[i]);puts("");
	// FOR(i,1,MAX) printf("%d ",B[i]);puts("");
	FOR(i,1,MAX) if (A[i]!=B[i]) return 0*puts("1");
	return 0*puts("0");
}
/*
D 1
D 2
D 10000000001
D 10000000002
E
D 3
D 1
D 10000000003
D 10000000001
E
*/