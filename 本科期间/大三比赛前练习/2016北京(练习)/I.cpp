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
const LL maxn=5e4+7;
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

int sum[107];
ll fac[maxn],inv[maxn];
ll C(int n,int m) {
	return fac[n]*inv[m]%M*inv[n-m]%M;
}
int main() {
	int i; fac[0]=inv[0]=inv[1]=1;
	FOR(i,1,10000) fac[i]=i*fac[i-1]%M;
	FOR(i,2,10000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,10000) inv[i]=inv[i]*inv[i-1]%M;
	int T; scanf("%d",&T);
	while (T--) {
		int k,j;
		scanf("%d%d",&n,&k);
		scanf("%s",str); sum[0]=1;
		FOR(i,1,k) sum[i]=0; int now=0;
		REP(j,n) {
			ll pw=1,ans=0; now+=str[j]-'0'; if (k&1) pw=-1;
			FOR(i,0,k) ans=(ans+C(k,i)*sum[k-i]%M*pw%M)%M,pw=(M-pw*now%M)%M;
			pw=1;
			FOR(i,0,k) sum[i]=(sum[i]+pw)%M,pw=pw*now%M;
			// FOR(i,0,k) printf("%d ",sum[i]);
			// printf("ans=%lld\n",ans);
			printf("%lld%c",(ans+M)%M," \n"[j==n-1]);
		}
	}
}
/*
2
5 1
12345
5 2
54321
*/
