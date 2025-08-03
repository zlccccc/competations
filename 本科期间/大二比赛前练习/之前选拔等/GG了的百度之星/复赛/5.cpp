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
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

char a[maxn]; 
LL n,m,T;
int i,j,k;
LL dp[107][17][2][2];
LL all,t,ans;



int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%s",&a);
		all=0;//ǰ׺ 
		int len=strlen(a);
		t=1;ans=all=0;
		memset(dp,0,sizeof(dp));
		FOR(i,1,len){
			char now=a[i-1];
			printf("%d\n",now[])
			FOR(j,0,9){
				FOR(k,0,j-1) dp[i][j][0]=(dp[i][j][0]+dp[i-1][j][0])%M;
				FOR(k,j+1,9) dp[i][j][1]=(dp[i][j][1]+dp[i-1][j][0]+dp[i-1][j][1])%M;
				FOR(k,0,min(now-'0',j-1)) dp[i][j][0]=(dp[i][j][0]+t)%M;
				FOR(k,j+1,min(now-'0',9)) dp[i][j][1]=(dp[i][j][1]+t)%M;
			}
			t=t*10%M;
		}
		FOR(j,1,9) ans=(ans+dp[len][j][0]+dp[len][j][1])%M;
		printf("%I64d\n",ans);
	}
}
/*
2
1 3
*/
