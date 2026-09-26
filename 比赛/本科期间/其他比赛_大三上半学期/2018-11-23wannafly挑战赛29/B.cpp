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
const LL maxn=1e7+107;
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
// char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

ll k;
map<ll,ll> MP;
ll resolve(ll C2,ll C3,ll C5,ll C7) {
	C2%=k; C3%=k; C5%=k; C7%=k;
	return C2+C3*k+C5*k*k+C7*k*k*k;
}
int main() {
	int i; ll ans=0,cnt=0,c1=0;
	scanf("%d%lld",&n,&k);
	FOR(i,1,n) {
		ll x;
		scanf("%lld",&x);
		assert(x);
		int C2=0,C3=0,C5=0,C7=0;
		ll y=1;
		if (!x) y=0;
		while (x) y=x%10*y,x/=10;
		if (!k&&y==1) ans+=c1,c1++;
		if (!k) continue;
		if (!y) continue;
		while (y%2==0) y/=2,C2++;
		while (y%3==0) y/=3,C3++;
		while (y%5==0) y/=5,C5++;
		while (y%7==0) y/=7,C7++;
		cnt++;
		C2%=k; C3%=k; C5%=k; C7%=k;
		ans+=MP[resolve(k-C2,k-C3,k-C5,k-C7)];
		// printf("%lld\n",x,resolve(C2,C3,C5,C7));
		MP[resolve(C2,C3,C5,C7)]++;
	} if (k==0) cnt=n;
	// printf("ans=%lld\n",ans);
	printf("%lld\n",cnt*(cnt-1)/2-ans);
}
/*
8 0
113 10 11 1110 33 110 1111 1
*/
