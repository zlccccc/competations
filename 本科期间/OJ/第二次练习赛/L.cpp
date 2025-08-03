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

//不会数论啊QwQ.. QAQ.. 我看你就是在为难我胖虎.jpg
int n,m,i,j,k,now,seg;
int dp[maxn];
int main(){
	dp[0]=1;
	FOR(i,0,50000){
		seg=1;
		for (j=1;i+j*(3*j-1)/2<=50000;j++){
			(dp[i+j*(3*j-1)/2]+=dp[i]*seg%M+M)%=M;
			(dp[i+j*(3*j+1)/2]+=dp[i]*seg%M+M)%=M;
			seg=-seg;
		}
	}
	while (~scanf("%d",&n)){
		printf("%d\n",dp[n]);
	}
}
/*
*/
