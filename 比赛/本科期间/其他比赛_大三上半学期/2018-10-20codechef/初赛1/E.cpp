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

int A[307][307],B[607][307],C[607][307],ans[607];//left_up
int solve() {
	scanf("%d%d",&n,&m); int i,j,k;
	memset(A,0,sizeof(A)); memset(B,0,sizeof(B));
	memset(C,0,sizeof(C)); memset(ans,0,sizeof(ans));
	FOR(i,1,n) FOR(j,1,m) {
		scanf("%1d",&A[i][j]);
		B[i+j][i]=A[i][j]; C[i-j+m][i]=A[i][j];
	} FOR(i,1,n+m) {
		FOR(j,1,n) B[i][j]+=B[i][j-1],C[i][j]+=C[i][j-1];
	}
	// FOR(i,1,n+m){
	// 	printf("B[%d] : \n",i);
	// 	FOR(j,1,n) printf("%d ",B[i][j]); puts("");
	// } FOR(i,1,n+m){
	// 	printf("C[%d] : \n",i-m);
	// 	FOR(j,1,n) printf("%d ",C[i][j]); puts("");
	// }
	FOR(i,1,n) FOR(j,1,m) if (A[i][j]){
		FOR(k,1,n+m-2) {
			int now=0;
			if (1<=i+j-k&&i+j-k<=n+m) now+=B[i+j-k][i]-B[i+j-k][max(i-k,0)];
			// if (now) printf("B %d %d : %d  [%d](%d)\n",i,j,k,i+j-k,now);
			ans[k]+=now; now=0;
			if (1<=i-j+k+m&&i-j+k+m<=n+m) now+=C[i-j+k+m][min(i+k,n)]-C[i-j+k+m][i];
			// if (now) printf("C %d %d : %d  [%d](%d)\n",i,j,k,i-j+k,now);
			ans[k]+=now;
		}
	} FOR(i,1,n+m-2) printf("%d%c",ans[i]," \n"[i==n+m-2]);
}
int main() {
	int T; scanf("%d",&T);
	while (T--) solve();
}
/*
3
3
-1 -1 -1
5
1 -1 -1 4 1
4
4 6 7 -1

*/
