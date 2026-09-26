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
const LL maxn=3e5+107;
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
	} T[maxn]; int TOT;
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
	int x0,y0,x1,y1;//check两个=_=
	int check(int x,int y) {
		return x0<=x&&x<=x1&&y0<=y&&y<=y1;
	}
	int ok(point &A) {
		return check(A.A[0],A.A[1]);
	}
	int allin(point &A) {
		return  x0<=A.min[0]&&A.max[0]<=x1&&
		        y0<=A.min[1]&&A.max[1]<=y1;
	}
	int allout(point &A) {
		return  A.max[0]<x0||x1<A.min[0]||
		        A.max[1]<y0||y1<A.min[1];
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
int root;
struct node {
	int op,x,y,id;
} p[maxn]; int tot;
int ans[maxn];
int main() {
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n) {
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		p[++tot]=node{-i,b,b,a-1};
		p[++tot]=node{i,b,b,c};
		p[++tot]=node{0,a,c,b};
	}
	sort(p+1,p+1+tot,[&](const node &a,const node &b) {
		if (a.id!=b.id) return a.id<b.id;
		return abs(a.op)<abs(b.op);
	});
	FOR(i,1,tot) {
		if (p[i].op==0) {
			// printf("insert: %d %d\n",p[i].x,p[i].y);
			KDT::addnode(root,p[i].x,p[i].y);
		} else {
			KDT::x0=-INF; KDT::x1=p[i].x;
			KDT::y0=p[i].y; KDT::y1=INF;
			// printf("%d-%d; %d-%d\n",KDT::x0,KDT::x1,KDT::y0,KDT::y1);
			int now=KDT::query(root);
			// printf("query: %d %d %d: %d\n",p[i].op,p[i].x,p[i].y,now);
			if (p[i].op<0) ans[-p[i].op]-=now;
			else ans[p[i].op]+=now;
		}
	}
	FOR(i,1,n) printf("%d\n",ans[i]-1);
}