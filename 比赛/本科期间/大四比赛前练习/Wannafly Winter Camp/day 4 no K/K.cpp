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
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
// int n,m,q;
// char str[maxn];//倒着的

const int mod=1e9+7;
int H26[maxn],PreVal[maxn];//sum
struct node {
	int hashVal;//用这个判是否全是1或者0
	int l,r;
	node() {hashVal=l=r=0;}
	node(int sameVal,int length) {
		l=r=0; hashVal=sameVal?PreVal[length-1]:0;
	}
	void setSame(int sameVal,int length) {
		hashVal=sameVal?PreVal[length-1]:0;
	}
} T[maxn*80]; int tot;
const int MAX=30+6+7;
int ans_2[maxn];
struct BIGINT {
	int root;//smsame->big
	BIGINT() {root=++tot; T[tot]=node(0,0); add(MAX);} //must!
	static void pushdown(int x,int L_length,int R_length) {
		if (T[x].hashVal==PreVal[L_length+R_length-1]) {
			if (!T[x].l) T[x].l=++tot,T[tot]=node(1,L_length);//init
			else T[T[x].l].setSame(1,L_length);
			if (!T[x].r) T[x].r=++tot,T[tot]=node(1,R_length);
			else T[T[x].r].setSame(1,R_length);
		} else if (T[x].hashVal==0) {
			if (!T[x].l) T[x].l=++tot,T[tot]=node(0,L_length);//init
			else T[T[x].l].setSame(0,L_length);
			if (!T[x].r) T[x].r=++tot,T[tot]=node(0,R_length);
			else T[T[x].r].setSame(0,R_length);
		}
	}
	static void pushup(int x,int L_length) {
		int al=T[x].l?T[T[x].l].hashVal:0;
		int ar=T[x].r?T[T[x].r].hashVal:0;
		T[x].hashVal=(al+(ll)ar*H26[L_length])%mod;
		// if (ar) printf("%d: %d\n",x,L_length);
	}
	// void update(int x,int k,int upper,int L,int R){//no use now
	// }
	static int querySame(int x,int k,int val,int L,int R) { //from k
		int mid=(L+R)/2;
		// if (k!=MAX)
		// 	printf("querysame: %d k=%d val=%d L-R=%d %d; mid=%d; val=%d\n",x,k,val,L,R,mid,T[x].hashVal);
		if (k<=mid) {
			int should=val?PreVal[R-L]:0;
			// printf("should[%d]=%d;  %d\n",R-L,should,PreVal[R-L]);
			if (T[x].hashVal==should) return R+1;
			else {
				if (L==R) return L;
				pushdown(x,mid-L+1,R-mid);
				int ret=querySame(T[x].l,k,val,L,mid);
				if (ret==mid+1) ret=querySame(T[x].r,k,val,mid+1,R);
				pushup(x,mid-L+1);
				return ret;
			}
		} else {
			pushdown(x,mid-L+1,R-mid);
			int ret=querySame(T[x].r,k,val,mid+1,R);
			pushup(x,mid-L+1);
			return ret;
		}
	}
	static void setSame(int &x,int l,int r,int val,int L,int R) {
		if (l>r) return;
		if (!x) x=++tot,T[x]=node(0,R-L+1);
		if (l<=L&&R<=r) {
			T[x].setSame(val,R-L+1);
			return;
		} int mid=(L+R)/2;
		pushdown(x,mid-L+1,R-mid);
		if (l<=mid) setSame(T[x].l,l,r,val,L,mid);
		if (mid<r) setSame(T[x].r,l,r,val,mid+1,R);
		pushup(x,mid-L+1);
		// if (l!=MAX)
		// 	printf("setSame: %d  %d-to-%d ;L-R=%d-%d mid=%d; val=%d\n",x,l,r,L,R,mid,T[x].hashVal);
	}
	void add(int k) {
		// if (k<MAX) printf("ADD: %d\n",k);
		int pos=querySame(root,k,1,0,MAX);
		// if (k<MAX) printf("query %d:pos=%d\n",k,pos);
		setSame(root,k,pos-1,0,0,MAX);
		setSame(root,pos,pos,1,0,MAX);
	}
	void del(int k) {
		// if (k<MAX) printf("DEL: %d\n",k);
		int pos=querySame(root,k,0,0,MAX);
		// if (k<MAX) printf("query %d:pos=%d\n",k,pos);
		setSame(root,k,pos-1,1,0,MAX);
		setSame(root,pos,pos,0,0,MAX);
	}
	static void print(int x,int L,int R) {
		int i; int mid=(L+R)/2;
		if (!x||T[x].hashVal==0) {FOR(i,L,R) ans_2[i]=0; return;}
		if (T[x].hashVal==PreVal[R-L]) {FOR(i,L,R) ans_2[i]=1; return;}
		pushdown(x,mid-L+1,R-mid);
		if (T[x].l) print(T[x].l,L,mid);
		if (T[x].r) print(T[x].r,mid+1,R);
		pushup(x,mid-L+1);
	}
	void print() {
		print(root,0,MAX); int i,n;
		// rFOR(i,0,10) printf("%d",ans_2[i]); puts(" <- print 10");
		if (ans_2[MAX]) {
			rFOR(n,1,MAX-1) if (ans_2[n]) break;
			rFOR(i,0,n) putchar('0'+ans_2[i]); puts("");
		} else {
			del(0); print(root,0,MAX);
			rFOR(n,1,MAX-1) if (!ans_2[n]) break;
			putchar('-'); //01010..1...1
			rFOR(i,0,n) putchar('0'+!ans_2[i]); puts("");
			add(0);
		}
	}
	void add(BIGINT x) {
		x.print(x.root,0,MAX);
		int i,n;
		if (ans_2[MAX]) {
			rFOR(n,1,MAX-1) if (ans_2[n]) break;
			rFOR(i,0,n) if (ans_2[i]) add(i);
		} else {
			x.del(0); x.print(x.root,0,MAX);
			rFOR(n,1,MAX-1) if (!ans_2[n]) break;
			rFOR(i,0,n) if (!ans_2[i]) del(i);
			x.add(0);
		}
	}
	bool query(int x,int y,int L,int R) {
		// printf("query: %d %d %d-%d  hashval=%d %d\n",x,y,L,R,T[x].hashVal,T[y].hashVal);
		int ax=x?T[x].hashVal:0;
		int ay=y?T[y].hashVal:0;
		if (L==R) return ax<ay;
		int rx=T[x].r?T[T[x].r].hashVal:0;
		int ry=T[y].r?T[T[y].r].hashVal:0;
		// printf("query: down righthashval=%d %d\n",rx,ry);
		int mid=(L+R)/2;
		pushdown(x,mid-L+1,R-mid);
		pushdown(y,mid-L+1,R-mid);
		int ret;
		if (rx!=ry) ret=query(T[x].r,T[y].r,mid+1,R);
		else ret=query(T[x].l,T[y].l,L,mid);
		pushup(x,mid-L+1);
		pushup(y,mid-L+1);
		return ret;
	}
	bool smallerThan(BIGINT x) {
		return query(root,x.root,0,MAX);
	}
};

vector<int> edge[maxn];
void testBigintger() {
	BIGINT i,j;
	// i.add(4);
	i.del(2);
	i.del(1);
	i.add(3);
	i.add(0);
	i.print();
	i.del(10);
	j.add(i); j.add(10);
	// i.print();
	i.print();
	j.print();
	printf("%d\n",i.smallerThan(j));
	// i.del(1); i.print();
}
void init() {
	PreVal[0]=H26[0]=1; int i;
	FOR(i,1,MAX) PreVal[i]=H26[i]=(ll)H26[i-1]*26%M;
	FOR(i,1,MAX) add_(PreVal[i],PreVal[i-1]);
	// FOR(i,1,100) printf("%d ",PreVal[i]);
}
int A[maxn];
BIGINT dfs(int x,int fa) {
	BIGINT ret;
	for (int v:edge[x]) if (v!=fa) {
			BIGINT now=dfs(v,x);
			if (ret.smallerThan(now)) ret=now;
		}
	if (A[x]>0) ret.add(A[x]-1);
	if (A[x]<0)ret.del(-A[x]-1);
	return ret;
}
int main() {
	init();
	// testBigintger();
	int i,n,q;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n-1) {
		int u,v; scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	} scanf("%d",&q);
	while (q--) {
		int x; scanf("%d",&x); tot=0;//TODO:change it
		BIGINT ans[4];
		for (int v:edge[x]) {
			BIGINT now=dfs(v,x);
			rREP(i,4) if (ans[i].smallerThan(now)) swap(ans[i],now);
		} rep(i,1,4) ans[0].add(ans[i]);
		// ans[0].print(); puts("<- ans previous");
		if (A[x]>0) ans[0].add(A[x]-1);
		if (A[x]<0) ans[0].del(-A[x]-1);
		ans[0].print();
	}
}
/*
5
6 -1 2 -9 -5 
1 2
2 3
1 4
4 5
5
5
1
3
2
1

*/