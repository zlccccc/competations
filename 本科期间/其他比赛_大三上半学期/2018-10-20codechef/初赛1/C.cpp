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

int A[maxn];
int G[57][57],e[57][57];
int solve() {
	scanf("%d",&n); int i,j,k;
	FOR(i,1,n) scanf("%d",&A[i]); int g=A[1];
	FOR(i,1,n) g=gcd(A[i],g);
	bool no=0;
	FOR(i,1,n) FOR(j,1,n) e[i][j]=G[A[i]][A[j]];
	FOR(k,1,n) FOR(i,1,n) FOR(j,1,n) e[i][j]|=e[i][k]&e[k][j];
	FOR(i,1,n) FOR(j,1,n) if (i!=j&&!e[i][j]) no=1;
	if (no) {
		puts("1");
		if (A[1]==43) A[1]=47; else A[1]=43;
		FOR(i,1,n) printf("%d%c",A[i]," \n"[i==n]);
	} else {
		puts("0");
		FOR(i,1,n) printf("%d%c",A[i]," \n"[i==n]);
	}
}
int main() {
	int i,j;
	FOR(i,2,50) FOR(j,2,50) if (gcd(i,j)==1) G[i][j]=1;
	// FOR(i,2,50) {FOR(j,2,50) printf("%d",G[i][j]); puts("");}
	int T; scanf("%d",&T);
	while (T--) solve();
}
/*
2 2 2 3 2 2 4
*/
