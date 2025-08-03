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

int ini[3007];
const int mod=1e9+7;
void mul(ll *a,ll *b,int k) {
	int i,j;
	static ll tmp[3007];
	REP(i,k+k) tmp[i]=0;
	REP(i,k) if (a[i]) REP(j,k)
		((tmp[i+j]+=a[i]*b[j])>=INFF)&&(tmp[i+j]%=mod);
	rrep(i,k,k+k) if (tmp[i]){
		tmp[i]%=mod;
		REP(j,k) ((tmp[i-k+j]+=tmp[i]*ini[k-j])>=INFF)&&(tmp[i-k+j]%=mod);
	}
	REP(i,k) a[i]=tmp[i]%mod;
}
ll A[3007],B[3007];
void power(int k,ll n) {
	if (k!=1) A[1]=1; else A[0]=ini[1]; B[0]=1;
	for (ll x=n; x; x>>=1) {
		if (x&1) mul(B,A,k);
		mul(A,A,k);
	}
}
ll f[3007];
int main() {
	int i,j,k,T,_;
	scanf("%d",&T);
	FOR(_,1,T) {
		ll n;
		memset(A,0,sizeof(A));
		memset(B,0,sizeof(B));
		memset(f,0,sizeof(f));
		memset(ini,0,sizeof(ini));
		scanf("%d%lld",&k,&n);
		if (n==-1) printf("%lld\n",(ll)2*powMM(k+1,M-2)%M);
		else {
			ll base=powMM(k,M-2);
			// printf("pow=%lld\n",base);
			f[0]=1;
			rep(i,1,k) {
				f[i]=0;
				REP(j,i) add_(f[i],f[j]*base%M);
			}
			ll ans=0;
			FOR(i,1,k) ini[i]=powMM(k,M-2);
			power(k,n);
			// REP(i,k) printf("%lld ",B[i]); puts("<-B");
			REP(i,k) add_(ans,f[i]*B[i]%M);

			printf("%lld\n",ans);
		}
	}
}
/*
*/