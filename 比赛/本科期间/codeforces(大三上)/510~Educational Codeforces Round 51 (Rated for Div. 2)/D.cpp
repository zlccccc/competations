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
const LL maxn=1e6+7;
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

int f[2007][4],g[2007][4];
int main() {
	int i,j,k,_k;
	scanf("%d%d",&n,&_k);
	f[1][0]=1; f[2][1]=1; f[2][2]=1; f[1][3]=1;
	FOR(i,2,n){
		FOR(j,1,n*2) REP(k,4) g[j][k]=f[j][k],f[j][k]=0;
		FOR(j,0,n*2){
			add_(f[j][0],g[j][0]);
			add_(f[j+1][1],g[j][0]);
			add_(f[j+1][2],g[j][0]);
			add_(f[j+1][3],g[j][0]);

			add_(f[j][0],g[j][1]);
			add_(f[j][1],g[j][1]);
			add_(f[j+2][2],g[j][1]);
			add_(f[j][3],g[j][1]);

			add_(f[j][0],g[j][2]);
			add_(f[j+2][1],g[j][2]);
			add_(f[j][2],g[j][2]);
			add_(f[j][3],g[j][2]);

			add_(f[j+1][0],g[j][3]);
			add_(f[j+1][1],g[j][3]);
			add_(f[j+1][2],g[j][3]);
			add_(f[j][3],g[j][3]);
		}
		// FOR(j,1,n*2) printf("%d|%d|%d|%d  ",f[j][0],f[j][1],f[j][2],f[j][3]);puts("");
	} int ans=0;
	REP(k,4) add_(ans,f[_k][k]);
	printf("%d\n",ans);
}
/*
*/
