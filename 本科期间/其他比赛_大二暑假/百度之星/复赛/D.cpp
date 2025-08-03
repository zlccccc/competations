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
const LL maxn=1e4+7;
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

namespace KDT {
	const double alpha=0.75;
	const int DIM=4;
	int dim;
	struct point {
		int A[DIM],max[DIM],min[DIM];
		int l,r; int size; int val,sum;
		void init(int _val) {
			l=r=0; val=_val; initval();
		}
		void initval() {
			int i; size=1; sum=val;
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
		if (l) T[x].size+=T[l].size,add_(T[x].sum,T[l].sum);
		if (r) T[x].size+=T[r].size,add_(T[x].sum,T[r].sum);
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
		build(T[x].l,l,m-1,(cur+1)%dim);
		build(T[x].r,m+1,r,(cur+1)%dim);
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
		if (cmp(now,x)) insert(T[x].l,now,(cur+1)%dim);
		else insert(T[x].r,now,(cur+1)%dim);
		update(x);
		if (T[x].size*alpha+3<max(T[T[x].l].size,T[T[x].r].size))
			rebuild(x,cur);
	}
	void addnode(int &x,int A[],int val) {
		TOT++; int i; REP(i,dim) T[TOT].A[i]=A[i];
		T[TOT].init(val); insert(x,TOT,0);
		// REP(i,dim) printf("%d ",A[i]);puts("<- insert");
	}
	int x[6];//check两个=_=
	int check(int y[]) {
		int i; REP(i,dim) if (y[i]>x[i]) return 0;
		return 1;
	}
	int ok(point &A) {
		return check(A.A);
	}
	int allin(point &A) {
		int i; REP(i,dim) if (A.max[i]>x[i]) return 0;
		return 1;
	}
	int allout(point &A) {
		int i; REP(i,dim) if (x[i]<A.min[i]) return 1;
		return 0;
	}
	int ans;
	void query(int x) {
		if (!x) return;
		if (allin(T[x])) {add_(ans,T[x].sum); return;}
		if (allout(T[x])) return;
		if (ok(T[x])) add_(ans,T[x].val);
		if (T[x].size==1) return;
		int l=T[x].l,r=T[x].r;
		query(l); query(r);
	}
}
struct node {
	int val,p[6];
};
vector<node> Q;
int root;
int A[5][maxn];
vector<int> V[5][maxn];
int solve() {
	int i,j,k,ans=0;
	scanf("%d%d",&k,&n); m=0;
	REP(i,k) FOR(j,1,n) scanf("%d",&A[i][j]);
	KDT::dim=k-1; root=0; KDT::TOT=0;
	REP(i,k-1) FOR(j,1,n) V[i][j].clear();
	REP(i,k-1) {
		FOR(j,1,n) V[i][A[i][j]].push_back(j);
	} FOR(j,1,n) {
		int val=A[k-1][j];
		for (int x0:V[0][val]) {
			KDT::x[0]=x0-1;
			if (k!=2) for (int x1:V[1][val]) {
					KDT::x[1]=x1-1;
					if (k!=3) for (int x2:V[2][val]) {
							KDT::x[2]=x2-1;
							if (k!=4) for (int x3:V[3][val]) {
									KDT::x[3]=x3-1;
									KDT::ans=0;
									KDT::query(root);
									add_(ans,KDT::ans+1);
									node nxt; nxt.val=KDT::ans+1;
									REP(i,k-1) nxt.p[i]=KDT::x[i]+1;
									Q.push_back(nxt);
								} else {
								KDT::ans=0;
								KDT::query(root);
								add_(ans,KDT::ans+1);
								node nxt; nxt.val=KDT::ans+1;
								REP(i,k-1) nxt.p[i]=KDT::x[i]+1;
								Q.push_back(nxt);
							}
						} else {
						KDT::ans=0;
						KDT::ans=0;
						KDT::query(root);
						add_(ans,KDT::ans+1);
						node nxt; nxt.val=KDT::ans+1;
						REP(i,k-1) nxt.p[i]=KDT::x[i]+1;
						Q.push_back(nxt);
					}
				} else {
				// printf("%d : x0=%d  ans=%d\n",j,x0,KDT::ans);
				KDT::ans=0;
				KDT::query(root);
				add_(ans,KDT::ans+1);
				node nxt; nxt.val=KDT::ans+1;
				REP(i,k-1) nxt.p[i]=KDT::x[i]+1;
				Q.push_back(nxt);
			}
		} for (auto now:Q) {
			KDT::addnode(root,now.p,now.val);
		} Q.clear();
	}
	printf("%d\n",ans);
	return 0;
}
int main() {
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
