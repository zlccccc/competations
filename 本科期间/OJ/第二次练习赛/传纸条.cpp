/* 
 Author: ’‘¡¢≥ø
 Result: AC	Submission_id: 370888
 Created at: Fri Nov 03 2017 14:10:26 GMT+0800 (CST)
 Problem_id: 51	Time: 213	Memory: 2748
*/

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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j,k,now; 
int dp[2][207][207],a[207][207];
inline void upd(int x,int y){
	
}
int main(){
	while (~scanf("%d%d",&n,&m)){
		FOR(i,1,n) FOR(j,1,m) scanf("%d",&a[i][j]);
		FOR(k,0,1) FOR(i,0,n) FOR(j,0,n) dp[k][i][j]=-INF;
		now=0;
		dp[now][1][1]=a[1][1];
		FOR(k,3,n+m-1){
			now^=1;
			FOR(i,1,n) FOR(j,1,n){
				if (i==j) continue;
				dp[now][i][j]=max(max(dp[now^1][i-1][j-1],dp[now^1][i][j]),max(dp[now^1][i-1][j],dp[now^1][i][j-1]))
							  +a[i][k-i]+a[j][k-j];
			}
//			FOR(i,1,n){FOR(j,1,n) printf("%d ",dp[now][i][j]);puts("");};puts("");
		}
		int ans=max(dp[now][n-1][n],dp[now][n][n-1])+a[n][m];
		printf("%d\n",ans);
	}
}
/*
*/
