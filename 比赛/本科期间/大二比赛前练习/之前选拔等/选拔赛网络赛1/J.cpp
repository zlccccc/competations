#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL MOD=1e9+7;
const LL maxn=300+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%MOD) ret=1ll*ret*a%MOD;return ret;}

#define next nxt
int n,m,K;
int i,j,k,l,r;
LL c,t;
LL val[maxn][maxn],dp[maxn][maxn];//val=l~r;dp[i][k]=to r,all k
int ans;
int main(){
	scanf("%d%d%d",&n,&m,&K);
	FOR(i,0,n)
		FOR(j,0,n) val[i][j]=dp[i][j]=INFF;
	REP(i,m){
		scanf("%d%d%I64d",&l,&r,&c);
		val[l][r]=min(val[l][r],c);
	}
	FOR(i,1,n)
		FOR(j,i,n)
			FOR(k,i,j){
				val[i][k]=min(val[i][k],val[i][j]);
				val[k][j]=min(val[k][j],val[i][j]);
			}
	//i=r,j=k
	dp[0][0]=0;
	FOR(i,1,n){
		FOR(j,0,i){
			dp[i][j]=dp[i-1][j];
			FOR(k,1,j) dp[i][j]=min(dp[i][j],dp[i-k][j-k]+val[i-k+1][i]);
		}
	}
	if (dp[n][K]==INFF) puts("-1");
	else printf("%I64d",dp[n][K]);
}
/*
*/
