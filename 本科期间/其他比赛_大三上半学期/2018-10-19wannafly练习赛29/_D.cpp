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
const LL maxn=1e7+7;
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

ll _m,n;
int cnt;
namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
	const int MAXP=1666666;
	const int MAX=10000010;
	ull mu[MAX];
	int p[MAXP],tot;
	ui ar[(MAX>>6)+7]= {0};
	void init() {
		setbit(ar,0); setbit(ar,1);
		int i,j; tot=0; mu[1]=1;
		rep(i,2,MAX) {
			if (isprime(i)) p[tot++]=i,mu[i]=-1;
			REP(j,tot) {
				if (i*p[j]>=MAX) break;
				if ((i*p[j])&1) setbit(ar,i*p[j]);
				if (i%p[j]==0) break;
				else mu[i*p[j]]=-mu[i];
			}
		} rep(i,1,MAX) mu[i]+=mu[i-1];
		// FOR(i,1,10) printf("%d : mu=%llu \n",i,mu[i]);
	}
	map<ull,ull> HASH;
	inline ull sum_mu(ull x) {
		if (x<MAX) return mu[x];
		if (HASH.count(x)) return HASH[x];
		ull ret=1,l;
		FOR(l,2,x){
			ull r=x/(x/l);
			ret-=(r-l+1)*sum_mu(x/l);
			l=r;
		} return HASH[x]=ret;
	}
	ull solve(ull m) { //gcd=1的方案数
		ull ans=0,l;
		FOR(l,1,m) {
			ull t=m/l,r=m/t;
			ans+=powMM(t,(ull)n)*(sum_mu(r)-sum_mu(l-1));
			l=r;
		} return ans;
	}
}
int main() {
	seives::init();
	scanf("%lld%lld",&n,&_m);
	printf("%llu\n",seives::solve(_m));
	// printf("%d\n",cnt);
}
/*

10000000
10000000

10000000000
10000000000

100000000000
*/
