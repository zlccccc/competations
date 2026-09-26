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
const LL maxn=2000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#define MP make_pair
int n;
int i,j,k;
int a[maxn],b[maxn];
LL dp[maxn][maxn];
LL cal[maxn];
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]);
	FOR(i,1,n) scanf("%d",&b[i]);
	cal[0]=1;
	FOR(i,1,n) FOR(j,0,i-1) cal[i]=(cal[i]+cal[j]*cal[i-j-1])%M;
//	FOR(i,0,n) printf("%d ",cal[i]);
	FOR(i,0,n) FOR(j,0,n){
		if (!i&&!j) dp[i][j]=1;
		else if (!i) dp[i][j]=dp[i][j-1];
		else if (!j) dp[i][j]=dp[i-1][j];
		else{
			if (a[i]!=b[j]){
				dp[i][j]=(dp[i-1][j]+dp[i][j-1])%M;
			}else{
				//相同的情况仅存在于两段相同的东西排列组合得到 
				dp[i][j]=(dp[i-1][j]+dp[i][j-1])%M;
				for (int w=0;i-w&&j-w&&a[i-w]==b[j-w];w++)
					dp[i][j]=(dp[i][j]-dp[i-w-1][j-w-1]*cal[w]%M+M)%M;
			}
		}
	}
	printf("%I64d\n",dp[n][n]);
}
/*
*/
