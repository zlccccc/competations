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
const LL maxn=2000+7;
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

LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m){
    return fac[n]*inv[m]%M*inv[n-m]%M;
}
int ans[2007];
int F[2007][2007][4];
void solve(int n){
	int i,j,t;
	FOR(i,0,n) ans[i]=0;
	REP(t,4) {
		memset(F,0,sizeof(F));
		F[0][0][t]=1;
		FOR(i,1,n) {
			FOR(j,0,n){
				add_(F[i][j][0],F[i-1][j][0]);
				add_(F[i][j+1][0],F[i-1][j][0]);
				add_(F[i][j+1][1],F[i-1][j][0]);
				add_(F[i][j+1][2],F[i-1][j][0]);

				add_(F[i][j][2],F[i-1][j][1]);
				add_(F[i][j+1][2],F[i-1][j][1]);
				add_(F[i][j+1][3],F[i-1][j][1]);

				add_(F[i][j][0],F[i-1][j][2]);
				add_(F[i][j+1][1],F[i-1][j][2]);
				add_(F[i][j+1][2],F[i-1][j][2]);

				add_(F[i][j][2],F[i-1][j][3]);
				add_(F[i][j+1][3],F[i-1][j][3]);
			}
		}
		// FOR(i,0,n) printf("%d ",F[n][i][t]);puts("");
		FOR(i,0,n) add_(ans[i],F[n][i][t]*fac[n-i]%M);
	}
	// FOR(i,0,n) printf("%d ",ans[i]);puts("");
	rFOR(i,0,n) FOR(j,i+1,n) add_(ans[i],M-ans[j]*C(j,i)%M);
	rFOR(i,0,n-1) add_(ans[i],ans[i+1]);
	// FOR(i,0,n) printf("%d ",ans[i]);puts("");
}
int main() {
	int T,_T,i;
    fac[0]=1;
    FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
    inv[0]=inv[1]=1;
    FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
    FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
	scanf("%d",&T);
	FOR(_T,1,T){
		scanf("%d%d",&n,&q);
		solve(n);
		printf("Case %d: %d\n",_T,ans[q]);
	}
}
/*
*/
