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
//const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
//template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n;
LL a[maxn],sum[maxn];
LL dp[1007][157][2];//i位,k,0/1 //i已选//滚动
int i,j,k;
int MAX=157;
int MMM=1000;
void solve(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%lld",&a[i]);
	FOR(i,1,n) sum[i]=sum[i-1]+a[i];
//	FOR(i,0,MMM)
//		FOR(j,1,MAX) dp[i][j][0]=dp[i][j][1]=-INFF/2;
	rFOR(i,1,n+1){
		int now=i%MMM;
		FOR(k,0,1){
			int t=150;
//			printf("%d:t=%d\n",i,t);
			FOR(j,1,t){
				int pos;
				pos=now+j;if (pos>=MMM) pos-=MMM;
				if (i+j-1==n) dp[now][j][k]=sum[n]-sum[i-1];//末尾
				else if (i+j-1>n) dp[now][j][k]=0;
				else if (i+j+j-1==n) dp[now][j][k]=sum[i+j-1]-sum[i-1]-dp[pos][j][k^1];
				else dp[now][j][k]=sum[i+j-1]-sum[i-1]-max(dp[pos][j][k^1],dp[pos][j+1][k^1]);
			}
		}
	}
//	FOR(i,1,n+1){
//		FOR(j,1,5) printf("%lld ",dp[i][j][0]);
//		puts("");
//	}
//	printf("%d %d\n",dp[1][1][0],dp[1][2][0]);
    if(n>=2)
        printf("%lld\n",max(dp[1][1][0],dp[1][2][0]));
	else
        printf("%lld\n",dp[1][1][0]);
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
10
3
1 3 2
2
0 -1
3
1 3 2
1
3
4
1 2 3 4
4
1 2 3 -3
5
1 2 3 4 5
30
1 7 4 64 6 8  2187  3267  6 45 445  74 34 554 4 668 7 178 6 78  78 1 85 18 4 4 4 1 8 72 3 5613 8 61 8 645 1478 65 76 54
*/

