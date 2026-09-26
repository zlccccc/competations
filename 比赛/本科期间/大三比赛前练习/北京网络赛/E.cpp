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
template<typename T>inline T powMM(T a, T b,ll MOD=M) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%MOD)
		if (b&1) ret=(LL)ret*a%MOD;
	return ret;
}
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int A[maxn];
int fac[2007];//n!
int C[2007][2007];
int dp[2007],D[2007];
int main() {
	int T,_t; scanf("%d",&T);
	FOR(_t,1,T) {
		int p,i,j,k;
		scanf("%d%d",&n,&p);
		fac[0]=1; FOR(i,1,2000) fac[i]=(ll)fac[i-1]*i%p;
		C[0][0]=1;
		FOR(i,1,2000) {
			C[0][i]=1;
			FOR(j,1,2000) C[i][j]=(C[i-1][j-1]+C[i][j-1])%p;
		}
		D[0]=0; D[1]=1%p;
		FOR(i,2,2000) D[i]=(ll)(i-1)*(D[i-1]+D[i-2])%p;
		dp[3]=1%p; dp[0]=1%p;
		printf("C=%d\n",C[10][10]);
		printf("C=%d %d\n",C[10][5],C[5][10]);
		FOR(i,1,20) printf("%d ",D[i]);puts("");
		FOR(i,1,n) {
			dp[i]=(ll)D[i]*D[i]%p;
			// int seg=-1;
			rFOR(k,1,i) {//cnt=i
				int now=p-(ll)dp[i-k]%p*D[k]%p*C[k][i]%p;
				printf("%d: (%d) : %d = %d * %d * %d\n",i,k,now,dp[i-k],D[k],C[k][i]);
				now%=p; add_(dp[i],now,p);
				// seg*=-1;
			}
		}
		FOR(i,1,n) printf("%d ",dp[i]);puts("");
		printf("%d\n",dp[n]);
	}
}
/*
0 0 1 9
*/
