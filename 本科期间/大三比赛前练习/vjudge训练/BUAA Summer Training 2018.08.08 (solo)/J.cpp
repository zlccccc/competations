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

char A[57][57];
bool B[57][57],R[57][57];
ll f[57][57];
int main() {
	int i,j,k;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%s",A[i]+1);
	rFOR(i,1,n) rFOR(j,1,m){
		B[i][j]=B[i+1][j]|B[i][j+1];
		if (A[i][j]=='B') B[i][j]|=1;
	}
	FOR(i,1,n) FOR(j,1,m){
		R[i][j]=R[i-1][j]|R[i][j-1];
		if (A[i][j]=='R') R[i][j]|=1;
	} f[0][m]=1;
	// FOR(i,1,n) FOR(j,1,m) if (B[i][j]&&R[i][j]) return 0*puts("0");
	// FOR(i,1,n){
	// 	FOR(j,1,m) printf("%d ",B[i][j]);puts("");
	// }
	// FOR(i,1,n){
	// 	FOR(j,1,m) printf("%d ",R[i][j]);puts("");
	// }
	FOR(i,1,n) {
		FOR(j,0,m){//分割点
			if (B[i][j+1]) continue;
			if (R[i][j]) continue; 
			FOR(k,j,m){
				f[i][j]+=f[i-1][k];
			}
		}
		// FOR(j,0,m) printf("%d",f[i][j]);puts("");
	} ll ans=0;
	FOR(j,0,m) ans+=f[n][j];
	printf("%lld\n",ans);
}
/*
3 2
..
B.
.R
*/