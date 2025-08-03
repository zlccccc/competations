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
const LL M=7340033;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

int n,m,T;
int i,j,k,t;
LL dp[32][2007],nm[2007];//只有中间做才可能 
int main(){
	dp[0][0]=1;
	FOR(i,1,30){
		dp[i][0]=1;
		memset(nm,0,sizeof(nm));
		FOR(j,0,1000)
			FOR(k,0,1000-j) nm[j+k]=(nm[j+k]+dp[i-1][j]*dp[i-1][k]%M)%M;
		FOR(j,0,1000)
			FOR(k,0,1000-j) dp[i][j+k+1]=(dp[i][j+k+1]+nm[j]*nm[k]%M)%M;
	}
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&k);
		t=0;
		while (n>1&&n%2==1) t++,n/=2;
		printf("%I64d\n",dp[t][k]);
	}
}
