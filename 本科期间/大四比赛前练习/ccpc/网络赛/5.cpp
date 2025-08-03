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
const LL maxn=3e5+107;
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

namespace seives { // 抄的define
#define clr(ar) memset(ar, 0, sizeof(ar))
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
	map<ll,int> HASH;
	const int MAXP=366666;
	const int MAX=1000010;
	int phi[MAX],F[MAX];
	int p[MAXP],tot;
	ui ar[(MAX>>6)+7]= {0};
	void init() {
		setbit(ar,0); setbit(ar,1);
		int i,j; tot=0; phi[1]=1;
		rep(i,2,MAX) {
			if (isprime(i)) p[tot++]=i,phi[i]=i-1;
			REP(j,tot) {
				if (i*p[j]>=MAX) break;
				if ((i*p[j])&1) setbit(ar,i*p[j]);
				if (i%p[j]==0) {phi[i*p[j]]=(ll)phi[i]*p[j]%M; break;}
				else phi[i*p[j]]=(ll)phi[i]*(p[j]-1)%M;
			}
		}
		rep(i,1,MAX) F[i]=(ll)phi[i]*i%M;
		rep(i,2,MAX) add_(F[i],F[i-1]);
	}
	ll get2(ll x){
		x%=M;
		return x%M*(x+1)%M*500000004%M;
	}
	ll get3(ll x){
		x%=M;
		return x*(x+1)%M*(2*x+1)%M*166666668%M;
	}
	inline int sum_F(ll x) {
		if (x<MAX) return F[x];
		if (HASH.count(x)) return HASH[x];
		int ret=get3(x); ll l;
		FOR(l,2,x){
			ll r=x/(x/l);
			add_(ret,M-(ll)(get2(r)-get2(l-1)+M)%M*sum_F(x/l)%M);
			l=r;
		} return HASH[x]=ret;
	}
}
int main(){
	// printf("%lld\n",gcd(powMM(3,6)-powMM(2,6),powMM(3,6)-powMM(2,6)));
	seives::init();
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		int n,a,b;
		scanf("%d%d%d",&n,&a,&b);
		a=gcd(a,b);
		seives::HASH.clear();
		int ans=seives::sum_F(n);
		add_(ans,M-1);
		mul_(ans,500000004);
		printf("%d\n",ans);
	}
}
/*
*/