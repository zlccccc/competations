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
 
ll sum4[maxn],sum2[maxn],sum6[maxn],val[maxn];
int main() {
	ll m; ll i;
	ll inv2=powMM(2,M-2),inv6=powMM(6,M-2);
	scanf("%lld",&m);
	ll k=m%M;
	ll base=k*(k+1)%M*(k+1)%M*inv2%M;
	add_(base,M-k*(k+1)%M*(2*k+1)%M*inv6%M);
	// printf("%lld\n",base);
	FOR(i,1,1000000) {
		val[i]=i*i;
		sum2[i]=val[i]%M; add_(sum2[i],sum2[i-1]);
		sum4[i]=val[i]%M*(val[i]%M)%M; add_(sum4[i],sum4[i-1]);
		sum6[i]=val[i]%M*(val[i]%M)%M*(val[i]%M)%M; add_(sum6[i],sum6[i-1]);
	} ll ans=0;
	for (ll x=0;x*x<=m;x++) {
		ll r=upper_bound(val,val+1000001,m-x*x)-val-1;
		ll now=0;
		ll A0=1,A1=x*x%M,A2=A1*A1%M,A3=A1*A2%M;
		ll B0=(r*2+1)%M,B1=sum2[r]*2%M-0,B2=sum4[r]*2%M-0,B3=sum6[r]*2%M-0;
		ll sum0=B0;
		ll sum1=A1*B0%M+A0*B1%M; sum1%=M;
		ll sum2=A0*B2%M+2*A1*B1%M+A2*B0%M; sum2%=M;
		ll sum3=A0*B3%M+3*A1*B2%M+3*A2*B1%M+A3*B0%M; sum3%=M;
		add_(now,(sum2-sum1+M)%M*(k+1)%M*inv2%M);
		add_(now,M-(2*sum3-3*sum2+sum1+M*3)%M*inv6%M);
		now=M-now; add_(now,base*sum0%M);
		// printf("%lld : %lld; %lld %lld %lld %lld\n",x,r,B0,B1,B2,B3);
		// printf("sum %lld : %lld %lld %lld %lld; now=%lld\n",x,sum0,sum1,sum2,sum3,now);
		if (x!=0) add_(ans,now);
		add_(ans,now);
	} printf("%lld\n",ans);
}
/*
*/