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
int n,m,q;
// char str[maxn];//倒着的

struct node {
	ll x,y;
	node() {}
	node(ll x,ll y):x(x),y(y) {}
    inline friend ll operator *(node a,node b){return a.x*b.y-a.y*b.x;}
	inline friend node operator -(node a,node b) {return node(a.x-b.x,a.y-b.y);}
	inline friend bool operator <(node a,node b) {return a.x^b.x?a.x<b.x:a.y<b.y;}
} P[maxn];
int idl[maxn],idr[maxn];
long double getins(int i,int j) {
	long double ret;
	if (P[i].x==P[j].x) ret=-1e8;
	else ret=-1.*(P[j].y-P[i].y)/(P[j].x-P[i].x);
	// printf("%d-%d: %f\n",i,j,ret);
	return ret;
}
int main() {
	int i;
	scanf("%d",&n);
	REP(i,n) scanf("%lld%lld",&P[i].x,&P[i].y),idl[i]=i,idr[i]=i;
	sort(idl,idl+n,[](int i,int j) {return P[i].x*-1e8+P[i].y<P[j].x*-1e8+P[j].y;});
	sort(idr,idr+n,[](int i,int j) {return P[i].x*-1e8+P[i].y>P[j].x*-1e8+P[j].y;});
	int l=0,r=0,lm=1,rm=1;//more
	// REP(i,n) printf("%d ",idl[i]); puts("");
	// REP(i,n) printf("%d ",idr[i]); puts("");
	long double x=-1e7,ans=P[idr[r]].x*x+P[idr[r]].y-P[idl[l]].x*x-P[idl[l]].y;//开始位置
	int nl=0,nr=0;
	REP(i,n) {
		if (!nl||P[idl[nl-1]].x!=P[i].x){
			while (nl>1&&getins(idl[nl-1],idl[nl-2])<getins(i,idl[nl-2])) nl--;
			idl[nl++]=idl[i];
		}
		if (!nr||P[idr[nr-1]].x!=P[i].x){
			while (nr>1&&getins(idr[nr-1],idr[nr-2])<getins(i,idr[nr-2])) nr--;
			idl[nl++]=idl[i];
		}
	}
	REP(i,nl) printf("%d ",idl[i]);puts("");
	REP(i,nr) printf("%d ",idr[i]);puts("");
	while (lm<nl||rm<nr) {
		while (lm<nl&&(getins(idl[l],idl[lm])<x)) lm++;
		while (rm<nr&&(getins(idr[r],idr[rm])<x)) rm++;
		if (lm!=nl||rm!=nr) {
			if ((lm!=nl&&getins(idl[l],idl[lm])<getins(idr[r],idr[rm]))
			        ||rm==nr) {
				x=getins(idl[l],idl[lm]); l=lm; lm++;
			} else if (rm!=nr) {
				x=getins(idr[r],idr[rm]); r=rm; rm++;
			}
		} ans=min(ans,P[idr[r]].x*x+P[idr[r]].y-P[idl[l]].x*x-P[idl[l]].y);
		// printf("x=%f ans=%f: %d(nxt=%d) %d(nxt=%d); lm,rm=%d %d\n",(double)x,(double)ans,idl[l],idl[lm],idr[r],idr[rm],lm,rm);
	}
	printf("%.12f\n",(double)ans);
}
/*
5
1000000 0
-1000000 -1000000
0 0
0 -2000000
1000000 -2000000

3
0 0
-1 1
1 1

5 7
0 1
0 2
0 3
0 4
1 2
1 3
2 4
*/