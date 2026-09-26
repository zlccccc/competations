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

ll A[57][57];
ll sum[57][57];
ll B[57][57],C[57][57],D[57][57];
inline ll query(int x,int y) {
	
}
int main() {
	int n,m,i,j,x,y;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) FOR(j,1,m) scanf("%lld",&A[i][j]);
	FOR(i,1,n) FOR(j,1,m) sum[i][j]=A[i][j]+sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1];

	FOR(i,0,n) FOR(j,0,m) C[i][j]=D[i][j]=-INFF;
	ll ans=-INFF;
	FOR(i,1,n) FOR(j,1,m) {
		ll now=-INFF;
		FOR(x,1,i) FOR(y,1,j) B[x][y]=sum[i][j]-sum[i][y-1]-sum[x-1][j]+sum[x-1][y-1];
		FOR(x,1,i) FOR(y,1,j) ans=max(ans,sum[i][j]-sum[i][y-1]-sum[x-1][j]+sum[x-1][y-1]);//one
		FOR(x,1,i) FOR(y,1,j) ans=max(ans,sum[i][j]-sum[i][y-1]-sum[x-1][j]+sum[x-1][y-1]+C[x][y]);//two

		// FOR(x,1,i) FOR(y,1,j) now=max(now,sum[i][j]-sum[i][y-1]-sum[x-1][j]+sum[x-1][y-1]+D[x][y]);//two
		// if (i==2&&j==2){
		// 	FOR(x,1,i) FOR(y,1,j) {
		// 		printf("%d %d: %d %d: %lld\n",i,j,x,y,B[x][y]+C[x][y]);
		// 	}
		// }
		FOR(x,1,i) FOR(y,1,j) B[x][y]=max(max(B[x-1][y],B[x][y-1]),B[x][y]);//maximize
		FOR(x,1,i) FOR(y,1,j) C[x][y]=max(C[x][y],B[x][y]-2*(sum[i][j]-sum[i][y-1]-sum[x-1][j]+sum[x-1][y-1]));//相交 
		// FOR(x,i+1,n)
	}
	printf("%lld\n",ans);
}
/*
5 5
10 10 10 10 -1
10 -1 -1 -1 10
10 -1 -1 -1 10
10 -1 -1 -1 10
-1 10 10 10 10

3 3
-2 -2 -1
-2 -1 -2
-2 -2 -2
*/
