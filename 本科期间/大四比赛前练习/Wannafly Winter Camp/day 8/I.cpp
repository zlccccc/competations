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
const LL maxn=1<<20|7;
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

/*
f0=a^2+b^2+c^2
f1=2ab+2bc
f4=2ac
*/
ll S[27][10][47];
void solve(int depth,int X[],ll T[]) {
	// 0,1,2 => 0,1,4
	// printf("depth=%d; X[0]=%d\n",depth,X[0]);
	int i; REP(i,41) T[i]=0;
	if (depth==0) {T[0]=(ll)X[0]*X[0]; return;}
	int base=1<<(depth*2-2);
	// printf("base=%d\n",base);
	REP(i,base) {
		ll A=X[i],B=X[base+i],C=X[base+base+i];
		X[base*0+i]=A+B+C;
		X[base*1+i]=A-B+C;
		X[base*2+i]=A+C;
		X[base*3+i]=A-C;
	}
	solve(depth-1,X,S[depth-1][0]);
	solve(depth-1,X+base,S[depth-1][1]);
	solve(depth-1,X+base+base,S[depth-1][2]);
	solve(depth-1,X+base+base+base,S[depth-1][3]);
	REP(i,41) T[i]=0;
	REP(i,41) {
		ll A=S[depth-1][0][i];
		ll B=S[depth-1][1][i];
		ll C=S[depth-1][2][i];
		ll D=S[depth-1][3][i];
		// if (i<=2) printf("i=%d ABCD=%lld %lld %lld %lld\n",i,A,B,C,D);
		T[i+0]+=(A+B-C+D)/2;
		T[i+1]+=(A-B)/2;
		T[i+4]+=(C-D)/2;
	}
}
int A[maxn];
ll ans[47];
int main() {
	int i,j;
	scanf("%d",&n);
	REP(i,n) {
		int now=0,k;
		REP(j,10) scanf("%d",&k),now=now<<2|k;
		A[now]++;
	} solve(10,A,ans);
	// FOR(i,0,40) printf("%lld ",ans[i]);
	int Ans=0;
	FOR(i,0,40) add_(Ans,(ans[i]%M*(ans[i]%M)%M));
	printf("%d\n",Ans);
}
/*
5
0 1 1 1 2 0 1 2 0 2
0 1 1 0 2 0 1 2 0 2
0 1 1 1 2 0 1 1 0 2
0 1 1 1 1 0 1 2 0 2
0 1 1 1 2 0 1 2 0 2

7
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 0 2
0 0 0 0 0 0 0 0 0 2

*/