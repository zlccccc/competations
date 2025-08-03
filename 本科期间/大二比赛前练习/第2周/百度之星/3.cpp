#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;

//维护val //left,right各一个 
int T;
int n,m;
LL dp[17][1007];
int a[100007],b[100007];
int k[1007],p[1007];
LL ans;
int solve(int n,int m){
	int i,j,P;
	FOR(i,1,n) scanf("%d%d",&a[i],&b[i]);
	FOR(i,1,m) scanf("%d%d",&k[i],&p[i]);
	FOR(P,0,10){
		dp[P][0]=0;
		FOR(i,1,1000) dp[P][i]=2000000000;
	}
	FOR(P,0,10){
		FOR(j,1,m){
			if (p[j]<=P) continue;
			FOR(i,1,1000){
				dp[P][i]=min(dp[P][i],dp[P][max(i-(p[j]-P),0)]+k[j]);
			}
		}
	}
	ans=0;
	FOR(i,1,n){
		if (dp[b[i]][a[i]]>1000000000) return 0*puts("-1");
		ans+=dp[b[i]][a[i]];
	}
	printf("%I64d\n",ans);
}
int main()
{
	while (~scanf("%d%d",&n,&m)) solve(n,m);
}
/*
*/
