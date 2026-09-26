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
const LL maxn=1<<20|7;
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
// char str[maxn];

int id[107];
ll get(ll x,int A){
	int l=0,i;
	while (x) id[l++]=x%10,x/=10;
	ll ret=0;
	rREP(i,l) ret=ret*A+id[i];
	return ret;
}
ll chk(ll x,int A){//转化进制->minimize
	int l=0,i,more=0;
	if (x<0) return x;
	while (x) id[l++]=x%10,x/=10;
	// REP(i,l) printf("%d",id[i]); puts("  <- id");
	rREP(i,l) {
		if (more) id[i]=A-1;
		if (id[i]>=A) id[i]=A-1,more=1;
	} ll ret=0;
	rREP(i,l) ret=ret*A+id[i];
	// REP(i,l) printf("%d",id[i]); puts("  <- id");
	// printf(" ret=%lld\n",ret);
	return ret;
}
int main() {
	int T; T=1;
	scanf("%d",&T);
	while (T--) {
		int A,B;
		scanf("%d%d",&A,&B);
		ll l1,r1,l2,r2;
		scanf("%lld%lld%lld%lld",&l1,&r1,&l2,&r2);
		if (A>B) {swap(A,B); swap(l1,l2); swap(r1,r2);}
		l1=get(l1,A);
		r1=get(r1,A);
		l2=chk(l2-1,A)+1;
		r2=chk(r2,A);
		printf("%lld\n",max(0ll,min(r1,r2)-max(l1,l2)+1));
	}
}
/*
10
3 4
1 12
2 30
3 10
1 12
2 2
*/