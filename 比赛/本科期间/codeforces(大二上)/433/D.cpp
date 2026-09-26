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
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int val[maxn];
int dp[47],now[47];
int n;
int i,j;
int ans;
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&val[i]);
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	FOR(i,1,n){
		memset(now,0x3f,sizeof(now));
		FOR(j,0,40){
			now[min(40,j+val[i]/1000)]=min(now[min(40,j+val[i]/1000)],dp[j]+val[i]);
			now[j-min(j,val[i]/100)]=min(now[j-min(j,val[i]/100)],dp[j]+val[i]-min(j,val[i]/100)*100);
		}
//		rFOR(j,0,40) now[j]=min(now[j],now[j+1]);
//	FOR(j,0,10) printf("%d ",now[j]);puts("");
		memcpy(dp,now,sizeof(dp));
	}
	ans=INF;
	FOR(i,0,40) ans=min(ans,dp[i]);
	printf("%d\n",ans);
}
/*
*/
