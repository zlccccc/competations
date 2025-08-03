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
const LL maxn=1e6+7;
const double eps=0.00000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

LL dp[507][507][2];//1:OK,0:not(i-j is selected)
int a[507][507];
LL ans;
int main(){
	int i,j,k,len,n;
	scanf("%d",&n);
	FOR(i,1,n) FOR(j,1,n) scanf("%d",&a[i][j]);
	FOR(i,1,n) dp[i][i][1]=1;
	FOR(len,1,n){
		FOR(i,1,n-len){
			j=i+len;
			if (a[i][j]) FOR(k,i+1,j) (dp[i][j][0]+=(dp[i][k-1][1]*dp[k][j][1]))%=M;
			FOR(k,i,j) (dp[i][j][1]+=dp[i][k][0]*dp[k][j][1])%=M;
		}
	}
	printf("%I64d\n",dp[1][n][1]%M);
}
/*
*/
