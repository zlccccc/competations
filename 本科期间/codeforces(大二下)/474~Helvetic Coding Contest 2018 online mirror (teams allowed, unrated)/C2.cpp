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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

int A[20007];
int dp[57][107][2];
inline void update(int &x,int y){
	x=max(x,y);
}
int main() {
	int i,j,l;
	int n,k,p;
	int now=0;
	scanf("%d%d%d",&n,&k,&p);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(j,1,k) REP(l,p) dp[j][l][now]=-INF;
	dp[1][0][now]=0;
	FOR(i,1,n){
		now^=1;
		FOR(j,1,k) REP(l,p)
			dp[j][l][now]=-INF;
		FOR(j,1,k){
			REP(l,p){
				update(dp[j][(l+A[i])%p][now],dp[j][l][now^1]);
				update(dp[j+1][0][now],dp[j][l][now^1]+(l+A[i])%p);
			}
		}
		// printf("%d:\n",i);
		// FOR(j,1,k){
		// 	REP(l,p){
		// 		printf("%10d ",dp[j][l][now]);
		// 	}puts("");
		// }
	}int ans=0;
	REP(l,p) ans=max(ans,dp[k][l][now]+l);
	printf("%d\n",ans);
	return 0;
}
/*
8 3
3 3 1 2 2 1 1 3
0 0 1
*/
