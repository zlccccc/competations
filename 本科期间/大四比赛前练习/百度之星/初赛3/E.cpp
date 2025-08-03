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
const LL maxn=1e3+107;
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

LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
	return fac[n]*inv[m]%M*inv[n-m]%M;
}
void init() {
	int i;
	fac[0]=1;
	FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
}
int A[maxn],cnt[maxn];
int f[maxn],g[maxn];//f:可用的空
int main() {
	init();
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T) {
		/*to solve the problem*/
		int i,n;
		scanf("%d",&n);
		memset(cnt,0,sizeof(cnt));
		FOR(i,1,n) {
			scanf("%d",&A[i]);
			cnt[A[i]]++;
		}
		int base=1;
		memset(g,0,sizeof(g));
		g[0]=1;//可用空为0; a{p+2}>=min(a{p+1},a{p})
		FOR(i,1,n) {
			int c=cnt[i];
			if (c) {
				mul_(base,fac[c]);
				int k,ini;
				// REP(ini,n+1) printf("%d ",g[ini]); puts(" <- f");
				REP(ini,n+1) f[ini]=g[ini],g[ini]=0;
				REP(ini,n+1) if (f[ini]){//开始可用空
					// printf("%d ",min(ini+1,c-o+1));
					REP(k,min(ini+1,c+1)) {//用掉了k个可用空
						// printf("%d->use(%d) (%d): nxt=%d  %lld\n",ini,k,c,c-k+ini-k,f[ini]*C(ini,k)%M);
						add_(g[c-k+ini-k],f[ini]*C(ini,k)%M);
					}
				}
				// REP(ini,n+1) printf("%d ",g[ini]); puts("");
			}
		} int ans=0;
		REP(i,n+1) add_(ans,g[i]);
		printf("%lld\n",(ll)ans*base%M);
	}
}
/*
10
4
1 2 2 3
5
1 2 3 3 4
3
1 1 1
3
1 2 3


122
212

232 322 223
2132 3221
2123 2213 2231
1232 1322
1223

1232 1322
1223
*/
