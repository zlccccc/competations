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
const LL maxn=1e5+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B) {A+=B; (A>=M) &&(A-=M);}
template<typename T>inline void mul_(T &A,ll B) {(A*=B)%=M;}
template<typename T>inline void mod_(T &A,ll B=M) {A%=M;}
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
int TaskA();
void Task_one() {TaskA();}
void Task_T() {int T; scanf("%d",&T); while (T--) TaskA();}
void Task_more_n() {while (~scanf("%d",&n)) TaskA();}
void Task_more_n_m() {while (~scanf("%d%d",&n,&m)) TaskA();}
void Task_more_n_m_q() {while (~scanf("%d%d%d",&n,&m,&q)) TaskA();}
void Task_more_string() {while (~scanf("%s",str)) TaskA();}

int A[3];
struct node{
	int l,r,min,max;
	node(){l=r=0; min=INF;max=-INF;}
}T[maxn*160];
int root[maxn*4],tot;
void Update(int &x,int pos,int op,int val,int L,int R){
	if (!x) x=++tot;
	if (op==1) min_(T[x].min,val);
	else max_(T[x].max,val);
	if (L==R) return;
	int mid=(L+R)/2;
	if (pos<=mid) Update(T[x].l,pos,op,val,L,mid);
	if (mid<pos) Update(T[x].r,pos,op,val,mid+1,R);
}
void update(int x,int pos1,int pos2,int op,int val,int L,int R){
	Update(root[x],pos2,op,val,1,A[1]);
	if (L==R) return;
	int mid=(L+R)/2;
	if (pos1<=mid) update(x<<1,pos1,pos2,op,val,L,mid);
	if (mid<pos1) update(x<<1|1,pos1,pos2,op,val,mid+1,R);
}
int MAX,MIN;
void Query(int x,int l,int r,int L,int R){
	if (!x) return;
	if (l<=L&&R<=r) {
		// printf(" Query: %d %d\n",T[x].max,T[x].min);
		max_(MIN,T[x].max); min_(MAX,T[x].min);
		return;
	}int mid=(L+R)/2;
	if (l<=mid) Query(T[x].l,l,r,L,mid);
	if (mid<r) Query(T[x].r,l,r,mid+1,R);
}
void query(int x,int l1,int r1,int l2,int r2,int L,int R){
	if (l1<=L&&R<=r1) {Query(root[x],l2,r2,1,A[1]); return;}
	int mid=(L+R)/2;
	if (l1<=mid) query(x<<1,l1,r1,l2,r2,L,mid);
	if (mid<r1) query(x<<1|1,l1,r1,l2,r2,mid+1,R);
}
int _x[3],_xmax[3],_xmin[3];
int TaskA() {
	int i,j;
	REP(j,3) scanf("%d",&A[j]);
	scanf("%d%d%d",&n,&m,&q);
	REP(j,3) _xmax[j]=-INF,_xmin[j]=INF;
	FOR(i,1,n) {
		REP(j,3) {
			scanf("%d",&_x[j]);
			max_(_xmax[j],_x[j]);
			min_(_xmin[j],_x[j]);
		}
	}
	FOR(i,1,m){
		int NO=0;
		REP(j,3) {
			scanf("%d",&_x[j]);
			if (_xmin[j]<=_x[j]&&_x[j]<=_xmax[j]) NO++;
		} if (NO==3) return 0*puts("INCORRECT");
		if (_x[2]<=_xmax[2]) update(1,_x[0],_x[1],0,_x[2]+1,1,A[0]);
		if (_x[2]>=_xmin[2]) update(1,_x[0],_x[1],1,_x[2]-1,1,A[0]);
	}
	puts("CORRECT");
	FOR(i,1,q){
		int l1,r1,l2,r2;
		bool okay=1;
		REP(j,3) {
			scanf("%d",&_x[j]);
			if (_x[j]<_xmin[j]||_xmax[j]<_x[j]) okay=0;
		}if (okay) {puts("OPEN"); continue;} 
		l1=min(_xmin[0],_x[0]);
		r1=max(_xmax[0],_x[0]);
		l2=min(_xmin[1],_x[1]);
		r2=max(_xmax[1],_x[1]);
		MAX=INF; MIN=-INF;
		query(1,l1,r1,l2,r2,1,A[0]);
		// printf("l, r=%d %d\n",MIN,MAX);
		if (MIN<=min(_x[2],_xmin[2])&&max(_x[2],_xmax[2])<=MAX) puts("UNKNOWN");
		else puts("CLOSED");
	}
	return 0;
}
void initialize() {}
int main() {
	int startTime=clock();
	//initialize
	initialize();
	debug("/--- initializeTime: %ld milliseconds ---/\n",clock()-startTime);
	Task_one();
}
/*
*/