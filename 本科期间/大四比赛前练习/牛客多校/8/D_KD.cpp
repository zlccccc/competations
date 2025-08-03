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
	const int DIM=3;
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
	void build(int &x,int l,int r,int cur) {
		x=0; if (l>r) return;
		int m=(l+r)/2; Cur=cur;
		nth_element(id+l,id+m,id+r+1,cmp);
		x=id[m];
		build(T[x].l,l,m-1,(cur+1)%DIM);
		build(T[x].r,m+1,r,(cur+1)%DIM);
		update(x);
	}
	void getid(int x) {
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
		if (cmp(now,x)) insert(T[x].l,now,(cur+1)%DIM);
		else insert(T[x].r,now,(cur+1)%DIM);
		update(x);
		if (T[x].size*alpha+3<max(T[T[x].l].size,T[T[x].r].size))
			rebuild(x,cur);
	}
	void addnode(int &x,int px,int py,int pz) {
		TOT++; T[TOT].A[0]=px; T[TOT].A[1]=py; T[TOT].A[2]=pz;
		T[TOT].init(); insert(x,TOT,0);
	}
	inline int distance(point &A,point &B){
		int ret=0,i;
		REP(i,3) ret+=abs(A.A[i]-B.A[i]);
		return ret;
	}
	inline int mindistance(point &A,point &B) {
		int ret=0,i;
		REP(i,3) {
			if (A.min[i]>B.A[i]) ret+=A.min[i]-B.A[i];
			if (A.max[i]<B.A[i]) ret+=B.A[i]-A.max[i];
		}
		return ret;
	}
	int ans;
	void query(int x,point &A) {
		if (!x) return;
		ans=min(ans,distance(T[x],A));
		if (T[x].size==1) return;
		int dl=INF,dr=INF;
		if (T[x].l) dl=mindistance(T[T[x].l],A);
		if (T[x].r) dr=mindistance(T[T[x].r],A);
		if (dl<dr) {
			if (dl<ans) query(T[x].l,A);
			if (dr<ans) query(T[x].r,A);
		} else {
			if (dr<ans) query(T[x].r,A);
			if (dl<ans) query(T[x].l,A);
		}
	}
}
int root;
int main() {
	int i;
	int n,m,h,q;
	scanf("%d%d%d%d",&n,&m,&h,&q);
	FOR(i,1,q) {
		int x,y,z,op;
		scanf("%d%d%d%d",&op,&x,&y,&z);
		if (op==1) {
			KDT::addnode(root,x,y,z);
		} else {
			KDT::ans=INF;
			KDT::point Q;
			Q.A[0]=x; Q.A[1]=y; Q.A[2]=z;
			KDT::query(root,Q);
			printf("%d\n",KDT::ans);
		}
	}
}