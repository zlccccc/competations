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

namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
	const int MAXP=66666;
	const int MAX=100010;
	int sigma[MAX],c[MAX];
	int p[MAXP],tot;
	ui ar[(MAX>>6)+7]= {0};
	void init() {//seives
		setbit(ar,0); setbit(ar,1);
		int i,j; tot=0;
		rep(i,2,MAX) {
			if (isprime(i)) p[tot++]=i;
			REP(j,tot) {
				if (i*p[j]>=MAX) break;
				if ((i*p[j])&1) setbit(ar,i*p[j]);
				if (i%p[j]==0) break;
			}
		}
	}
	ll n,m;//blocksize
	ll H[MAX],L[MAX];
	void pcf() {
		ll p,k;
		FOR(p,1,m) L[p]=p-1,H[p]=n/p-1;
		FOR(p,2,m) {
			if (L[p]==L[p-1]) continue;//not_prime
			FOR(k,1,min(m,n/p/p)) {
				if (p*k<=m) H[k]-=H[p*k]-L[p-1];
				else H[k]-=L[n/p/k]-L[p-1];
			} rFOR(k,p*p,m) L[k]-=L[k/p]-L[p-1];
		}
	}
	ll F[MAX],G[MAX];//F[n/k]:H[n/k], G[i]:L[i]
	ll getans(ll x,int i) {
		if (x<=1||p[i]>x) return 0;
		if (p[i]>m) return F[n/x]-G[m];
		ll ans=((x<=m)?G[x]:F[n/x])-G[p[i]-1];
		for (; (ll)p[i]*p[i]<=x; i++) {
			for (ll _x=x/p[i],c=1; _x>=p[i]&&c<=2; _x/=p[i],c++){
				if (c==1) ans+=getans(_x,i+1)*2+1;
				if (c==2) ans+=getans(_x,i+1);
			}
		} return ans;
	}
	ll solve() {
		int p;
		for (m=1; m*m<=n; ++m); m--; pcf();
		FOR(p,1,m) F[p]=H[p]*2,G[p]=L[p]*2;
		return getans(n,0)+1;//1:1
	}
}
int main() {
	// startTimer();
	seives::init();
	// printTimer();
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%lld",&seives::n);
		printf("%lld\n",seives::solve());
	}
}
/*
*/
