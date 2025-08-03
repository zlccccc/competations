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
const double eps=0.0000001;
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

double A[3007][3007];
double ans[3007],f[3007],g[3007],t[3007];
double add[3007];
int main() {
	int i,j;
	scanf("%d",&n);
	REP(i,n) REP(j,n) {int d; scanf("%d",&d); A[i][j]=d;}
	REP(i,n) scanf("%lf",&f[i]);
	REP(i,n) scanf("%lf",&g[i]),t[i]=g[i];
	REP(i,n) REP(j,n) f[i]+=A[i][j];
	REP(i,n) REP(j,n) A[i][j]/=f[j];
	REP(i,n) REP(j,n) if (i<j) swap(A[i][j],A[j][i]);
	// REP(i,n) REP(j,n) {
	// 	t[i]-=A[i][j]/f[j]*g[j];
	// }
	bool okay=1;
	while (okay){
		okay=0;
		REP(j,n) if (abs(g[j])>eps) {
			okay=1;
			REP(i,n) add[i]+=A[j][i]*g[j];
		} REP(i,n) g[i]=add[i],t[i]+=add[i],add[i]=0;
	}
	REP(i,n) printf("%.8lf ",t[i]);
}
/*
3
1 10 1
11 1 1
1 12 1
10000000 20000000 20000000
30000000 20000000 30000000
30000014.50000887 20000035.49997725 30000016.50001112

*/
