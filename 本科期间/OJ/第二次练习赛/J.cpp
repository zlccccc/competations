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
const LL M=1000007;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j,k,now; 
int dp[10007][1007];
int main(){
	int i;
	dp[1][1]=1;
	FOR(j,1,1000){
		FOR(i,1,10000){
			if (i-j>0) dp[i][j]=(0ll+dp[i][j]+dp[i-j][j])%M;
			if (j>0) dp[i][j]=(0ll+dp[i][j]+dp[i][j-1])%M;
		}
	}
	FOR(i,1,10){
		FOR(j,1,10) printf("%d ",dp[i][j]);
		puts("");
	}
	while (~scanf("%d%d",&n,&m)){
		printf("%lld\n",dp[n-m+1][m]);
	}
}
/*
*/
