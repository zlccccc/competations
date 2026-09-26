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
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

LL dp[507][507];
int n;
int i,j,k;
int main(){
	scanf("%d",&n);
	dp[1][0]=dp[1][1]=1;
	FOR(k,2,n){
		for(i=0;i<=n-k+2;i++){
			for(j=0;i+j-1<=n-k+2;j++){
				LL X=dp[k-1][i]*dp[k-1][j]%M;
				dp[k][i+j+1]=(dp[k][i+j+1]+X)%M;
				dp[k][i+j]=(dp[k][i+j]+X)%M;
				dp[k][i+j]=(dp[k][i+j]+X*i*2)%M;
				dp[k][i+j]=(dp[k][i+j]+X*j*2)%M;
				if (i+j-1>=1) dp[k][i+j-1]=(dp[k][i+j-1]+X*(i+j)*(i+j-1))%M;
			}
		}
	}
	FOR(j,0,10){
	FOR(i,0,10) printf("%d ",dp[j][i]);puts("");
	}
	printf("%I64d\n",dp[n][1]);
}
/*
*/
