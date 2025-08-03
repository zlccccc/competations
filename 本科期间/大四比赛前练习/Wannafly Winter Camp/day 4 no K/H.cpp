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

double p[7][7];
long double f[7][507][507];//第j轮之前没到过某个点的概率
double ans[7];
int main() {
	int i,j,k,l;
	scanf("%d",&n);//轮数
	FOR(i,1,6) FOR(j,1,6) scanf("%lf",&p[i][j]);
	FOR(i,1,6) {//假设从0开始走
		FOR(l,1,n) f[i][0][l]=1; f[i][0][0]=0;
		FOR(j,1,500) {
			f[i][j][0]=0;
			FOR(k,1,n) FOR(l,1,6)//1~6
				f[i][j][k]+=p[i][l]*f[i][j-1][(k-l+n*6)%n];
		}
	}
	// FOR(i,1,6){
	// 	printf("person[%d]:\n",i);
	// 	FOR(j,0,10){
	// 		REP(k,n) printf("%10.6f ",f[i][j][k]);puts("");
	// 	}
	// }
	FOR(i,1,6) FOR(j,1,500) FOR(k,1,n){
		//j轮 有k这块地
		long double now=1;
		FOR(l,1,i-1) now*=f[l][j][k];
		FOR(l,i+1,6) now*=f[l][j-1][k]; 
		now*=f[i][j-1][k]-f[i][j][k];
		ans[i]+=now;
	}
	FOR(i,1,6) printf("%.3f\n",ans[i]);
}
/*

6
0.00 0.50 0.50 0.00 0.00 0.00
0.50 0.00 0.00 0.50 0.00 0.00
0.00 0.30 0.30 0.40 0.00 0.00
0.60 0.00 0.00 0.20 0.20 0.00
0.20 0.05 0.05 0.70 0.00 0.00
0.03 0.02 0.95 0.00 0.00 0.00
*/