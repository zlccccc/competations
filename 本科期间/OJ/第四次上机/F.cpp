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
#include <functional>
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
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

char a[maxn],b[maxn];
int dp[1007][1007];
int i,j;
int main(){
	int T;
	while (~scanf("%s%s",a+1,b+1)){
		int len1=strlen(a+1),len2=strlen(b+1);
		FOR(i,0,len1) FOR(j,0,len2) dp[i][j]=INF;
		dp[0][0]=0;
		FOR(i,0,len1){
			FOR(j,0,len2){
				if (i) dp[i][j]=min(dp[i][j],dp[i-1][j]+1);
				if (j) dp[i][j]=min(dp[i][j],dp[i][j-1]+1);
				if (i&&j){
					if (a[i]==b[j]) dp[i][j]=min(dp[i][j],dp[i-1][j-1]);
					else dp[i][j]=min(dp[i][j],dp[i-1][j-1]+1);
				}
			}
		}printf("%d\n",dp[len1][len2]);
	} 
}
/*
*/
