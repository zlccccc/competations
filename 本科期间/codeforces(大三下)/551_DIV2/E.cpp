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
const LL maxn=1e6+107;
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

int query(int x1,int x2,int y1,int y2){
	int ret;
	printf("? %d %d %d %d\n",x1,y1,x2,y2);
	fflush(stdout);
	scanf("%d",&ret);
	return ret;
}
int main() {
	int n,i;
	scanf("%d",&n);
	int lx=0,rx=0,ly=0,ry=0;
	FOR(i,1,n) {
		if (query(1,i,1,n)&1) {
			if (!lx) lx=i;
		} else if (lx&&!rx) rx=i;
	}
	FOR(i,1,n) {
		if (query(1,n,1,i)&1) {
			if (!ly) ly=i;
		} else if (ly&&!ry) ry=i;
	}
	if (lx==rx) {
		assert(lx==0);
		int l=0,r=n;//r:okay
		while (l+1<r) {
			int mid=(l+r)/2;
			if (query(1,mid,1,ly)&1) r=mid;
			else l=mid;
		} lx=rx=r;
	}
	if (ly==ry) {
		assert(ly==0);
		int l=0,r=n;//r:okay
		while (l+1<r) {
			int mid=(l+r)/2;
			if (query(1,lx,1,mid)&1) r=mid;
			else l=mid;
		} ly=ry=r;
	}
	// printf("x:%d %d; y:%d %d\n",lx,rx,ly,ry);
	if (query(lx,lx,ly,ly)==1) printf("! %d %d %d %d\n",lx,ly,rx,ry);
	else printf("! %d %d %d %d\n",lx,ry,rx,ly);
}
/*
2
1 0 0 0
*/