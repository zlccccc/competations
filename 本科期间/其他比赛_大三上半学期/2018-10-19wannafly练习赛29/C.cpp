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
	for (; b; b>>=1ll,a=a*a)
		if (b&1) ret=ret*a;
	return ret;
}
int q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

namespace KDT {
	const double alpha=0.75;
	const int DIM=2;
	struct point {
		int A[DIM],max[DIM],min[DIM];
		int l,r; int size;
		void init() {
			l=r=0; initval();
		}
		void initval() {
			int i; size=1;
			REP(i,DIM) min[i]=max[i]=A[i];
		}
	} T[maxn*30]; int TOT;
	int Cur;
	bool cmp(int x,int y) {
		return T[x].A[Cur]<T[y].A[Cur];
	}
	void update(int x) {
		int i; T[x].initval();
		int l=T[x].l,r=T[x].r;
		if (l) T[x].size+=T[l].size;
		if (r) T[x].size+=T[r].size;
		REP(i,DIM) {
			if (l) {
				T[x].max[i]=max(T[x].max[i],T[l].max[i]);
				T[x].min[i]=min(T[x].min[i],T[l].min[i]);
			}
			if (r) {
				T[x].max[i]=max(T[x].max[i],T[r].max[i]);
				T[x].min[i]=min(T[x].min[i],T[r].min[i]);
			}
		}
	}
	int id[maxn],tot;
	void build(int &x,int l,int r,int cur) { //should have id
		x=0; if (l>r) return;
		int m=(l+r)/2; Cur=cur;
		nth_element(id+l,id+m,id+r+1,cmp);
		x=id[m];
		build(T[x].l,l,m-1,cur^1);
		build(T[x].r,m+1,r,cur^1);
		update(x);
	}
	void getid(int x) { //没有顺序=_=
		id[++tot]=x;
		if (T[x].l) getid(T[x].l);
		if (T[x].r) getid(T[x].r);
	}
	void rebuild(int &x,int cur) {
		tot=0; getid(x);
		build(x,1,tot,cur);
	}
	void insert(int &x,int now,int cur) {
		if (!x) {x=now; return;}
		Cur=cur;
		if (cmp(now,x)) insert(T[x].l,now,cur^1);
		else insert(T[x].r,now,cur^1);
		update(x);
		if (T[x].size*alpha+3<max(T[T[x].l].size,T[T[x].r].size))
			rebuild(x,cur);
	}
	void addnode(int &x,int px,int py) {
		TOT++; T[TOT].A[0]=px; T[TOT].A[1]=py;
		T[TOT].init(); insert(x,TOT,0);
	}
	int x1,y1,x2,d;//check两个=_=
	int check(int x,int y) {
		return x1<=x&&x+y<=x2+y1+d&&y1<=y&&y<=y1+d;
	}
	int ok(point &A) {
		return check(A.A[0],A.A[1]);
	}
	int allin(point &A) {
		return  x1<=A.min[0]&&A.max[0]+A.max[1]<=x2+y1+d&&
		        y1<=A.min[1]&&A.max[1]<=y1+d;
	}
	int allout(point &A) {
		return  A.max[0]<x1||x2+y1+d<A.min[0]+A.min[1]||
		        A.max[1]<y1||y1+d<A.min[1];
	}
	int query(int x) {
		if (!x) return 0;
		if (allin(T[x])) return T[x].size;
		if (allout(T[x])) return 0;
		int ret=0;
		if (ok(T[x])) ret++;
		if (T[x].size==1) return ret;
		ret+=query(T[x].l);
		ret+=query(T[x].r);
		return ret;
	}
}
int main() {
	int n,i; int root=0;
	scanf("%d",&n);
	FOR(i,1,n){
		int op;
		scanf("%d",&op);
		if (op==1){
			int x,y;
			scanf("%d%d",&x,&y);
			KDT::addnode(root,x,y);
		} else {
			scanf("%d%d%d%d",&KDT::x1,&KDT::y1,&KDT::x2,&KDT::d);
			printf("%d\n",KDT::query(root));
		}
	}
}
/*

10000000
10000000

10000000000
10000000000

100000000000
*/
