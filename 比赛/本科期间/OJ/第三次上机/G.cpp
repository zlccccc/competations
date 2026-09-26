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
#include <bitset>
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
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k;
int dp[207][207][17][3];
int main(){
	int n,m,x,y;
	while (~scanf("%d%d%d%d",&n,&m,&x,&y)){
		FOR(i,0,n) FOR(j,0,m) FOR(k,0,max(x,y)) dp[i][j][k][0]=dp[i][j][k][1]=0;
		dp[0][0][0][0]=1;
		FOR(i,0,n) FOR(j,0,m){
			if (i){
				FOR(k,1,x) (dp[i][j][k][0]+=dp[i-1][j][k-1][0])%=M;//1
				FOR(k,0,y) (dp[i][j][1][0]+=dp[i-1][j][k][1])%=M;//1
			}if (j){ 
				FOR(k,1,y) (dp[i][j][k][1]+=dp[i][j-1][k-1][1])%=M;//2
				FOR(k,0,x) (dp[i][j][1][1]+=dp[i][j-1][k][0])%=M;//2
			} 
		}
		int ans=0;
		FOR(k,1,x) (ans+=dp[n][m][k][0])%=M;
		FOR(k,1,y) (ans+=dp[n][m][k][1])%=M;
		printf("%d\n",ans);
	}
}
/*
*/
