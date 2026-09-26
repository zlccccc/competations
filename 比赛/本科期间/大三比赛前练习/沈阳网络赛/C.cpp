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
const LL maxn=1e6+7;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,ll B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
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

namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
	const int MAXP=666666;
	const int MAX=1000010;
	int mu[MAX];
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
				if (i%p[j]==0) {
					mu[i*p[j]]=0; break;
				} else {
					mu[i*p[j]]=-mu[i];
				}
			}
		}
	}
}
ll mul(ll a,ll b,ll M){
	a%=M; b%=M;
	return (__int128)a*b%M;
}
ll F(ll n,ll k,ll M){//1^k+...
	if (k==2){
		ll a=n,b=n+1;
		if (a%2==0) a/=2; else b/=2;
		return (__int128)mul(a,b,M);
	} if (k==3){
		ll a=n,b=n+1,c=2*n+1;
		if (a%2==0) a/=2; else b/=2;
		if (a%3==0) a/=3; else if (b%3==0) b/=3; else c/=3;		
		return (__int128)mul(mul(a,b,M),c,M);
	} if (k==4) return mul(F(n,2,M),F(n,2,M),M);
	assert(0); return 0;
}
int main() {
	ll n,M; int i,j;
	seives::init();
	while (~scanf("%lld%lld",&n,&M)){
		ll ans=0;
		// FOR(i,1,n) FOR(j,1,n/i/i) ans+=seives::mu[i]*(j*i*i)*(j*i*i)*(n-j*i*i+1);
		for (i=1;(ll)i*i<=n;i++) if (seives::mu[i]){
			ll t=(ll)i*i%M;
			ll base=mul(M+seives::mu[i],mul(t,t,M),M);
			// FOR(j,1,n/i/i) ans+=mul(mul(base,(n-j*t+1),M),mul(j,j,M),M); ans%=M;
			ll more=mul(n+1,F(n/i/i,3,M),M)-mul(t,F(n/i/i,4,M),M)+M;
			// if (base<0||more<0) printf("base=%lld more=%lld\n",base,more);
			// printf("ans=%lld += %lld\n",ans,mul(base,more,M));
			add_(ans,mul(base,more,M),M);
		}
		printf("%lld\n",ans);
	}

}
/*
1 10
1000 50000
10000 400000000000
100000 400000000000
1000000 400000000000

1 10
1
1000 50000
33508
10000 400000000000
382961058584
100000 400000000000
185873685814
1000000 400000000000
18944642088
*/
