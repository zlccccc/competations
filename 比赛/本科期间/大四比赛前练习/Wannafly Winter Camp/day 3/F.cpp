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
const LL maxn=2e5+107;
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
char str[maxn];//倒着的


namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
	const int MAXP=6666666;
	const int MAX=20000010;
	int mu[MAX],phi[MAX];
	int p[MAXP],tot;
	ui ar[(MAX>>6)+7]= {0};
	void init() {
		setbit(ar,0); setbit(ar,1);
		int i,j; tot=0; mu[1]=1; phi[1]=1;
		rep(i,2,MAX) {
			if (isprime(i)) p[tot++]=i,mu[i]=-1,phi[i]=i-1;
			REP(j,tot) {
				if (i*p[j]>=MAX) break;
				if ((i*p[j])&1) setbit(ar,i*p[j]);
				if (i%p[j]==0) {
					mu[i*p[j]]=0; 
					phi[i*p[j]]=phi[i]*p[j];
					break;
				} else {
					phi[i*p[j]]=phi[i]*(p[j]-1);
					mu[i*p[j]]=-mu[i];
				}
			}
		}
		// FOR(i,1,10) printf("%d ",mu[i]); puts("");
		// FOR(i,1,10) printf("%d ",phi[i]); puts("");
		FOR(i,2,MAX-1) {add_(phi[i],phi[i-1]); add_(mu[i],mu[i-1]); add_(mu[i],M);}
	}
	ll get2(ll x){
		x%=M; return x*(x+1)%M*499122177%M;
	}
	map<ll,int> HASHmu;
	ll sum_mu(ll x){
		if (x<MAX) return mu[x];
		if (HASHmu.count(x)) return HASHmu[x];
		ll ret=1; ll l;
		FOR(l,2,x){
			ll t=x/l,r=x/t;
			add_(ret,(M-(r-l+1)%M)*sum_mu(t)%M);
			l=r;
		} return HASHmu[x]=ret;
	}
	ll sum_F(ll x){
		if (x<MAX) return (phi[x]*2-1)%M;
		// if (HASHphi.count(x)) return HASHphi[x];
		ll l; ll ret=0;
		FOR(l,1,x){
			ll t=x/l,r=x/t; ll _t=t%M;
			add_(ret,(sum_mu(r)-sum_mu(l-1)+M)%M*_t%M*_t%M);
			l=r;
		} return ret;
	}
}
int main() {
	// startTimer();
	seives::init();
	// printTimer();
	// int i;
	// FOR(i,1,10) printf("%lld ",seives::sum_F(i)-seives::sum_F(i-1));
	ll n;
	scanf("%lld",&n);
	// startTimer();
	ll l=1,ans=0;
	FOR(l,1,n) {
		ll t=n/l,r=n/t;
		// printf("%lld-%lld: %lld * %lld\n",l,r,seives::sum_mu(r)-seives::sum_mu(l-1),seives::sum_F(t));
		ans=(ans+(seives::sum_mu(r)-seives::sum_mu(l-1)+M)*seives::sum_F(t)%M)%M;
		l=r;
	} ans%=M; ans+=M; ans%=M;
	printf("%lld\n",ans);
	// printTimer();
}
/*
1000000000
10000000000
*/