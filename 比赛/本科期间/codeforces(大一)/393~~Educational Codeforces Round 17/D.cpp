#include <cstdio>
#include <cmath>
#include <cstdlib> 
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,N) for (I=1;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=1e5+10;
const double eps=0.00000001;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}


LL a[N][3],dp[N][3];
LL n,m;
LL i,j,k;
LL sum;
int main()
{
	scanf("%I64d",&n);
	REP(i,3)
		FOR(j,n) scanf("%I64d",&a[j][i]);
	dp[1][0]=a[1][0];
	dp[1][1]=a[1][0]+a[1][1];
	dp[1][2]=a[1][0]+a[1][1]+a[1][2];
	for (i=2;i<=n;i++){
		dp[i][0]=a[i][0]+max(dp[i-1][0],max(dp[i-1][1]+a[i][1],dp[i-1][2]+a[i][1]+a[i][2]));
		dp[i][1]=a[i][1]+max(dp[i-1][1],max(dp[i-1][0]+a[i][0],dp[i-1][2]+a[i][2]));
		dp[i][2]=a[i][2]+max(dp[i-1][2],max(dp[i-1][1]+a[i][1],dp[i-1][0]+a[i][1]+a[i][0]));
		sum=a[i-1][0]+a[i-1][1]+a[i-1][2]+a[i][0]+a[i][1]+a[i][2];
		dp[i][0]=max(dp[i][0],dp[i-2][2]+sum);
		dp[i][2]=max(dp[i][2],dp[i-2][0]+sum);
	}
	printf("%I64d",dp[n][2]);
	return 0;
}
/*
3
1 1 1
1 -1 1
1 1 1
5
10 10 10 -1 -1
-1 10 10 10 10
-1 10 10 10 10
*/
