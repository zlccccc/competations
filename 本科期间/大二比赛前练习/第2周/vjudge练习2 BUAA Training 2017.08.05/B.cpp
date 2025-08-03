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

int n,m,k;
int i,j;
int val[maxn][26];
int should[maxn][26];
int dp[maxn],ans;
int a[maxn],b[maxn];
bool judge(int l1,int r1,int l2,int r2){//a,b
	int i=0,j=0;
	while (i<=k&&j<=k){
		while (val[r1][i]-val[l1-1][i]==0&&i<=k) i++;
		while (should[r2][r2]==0&&j<=k) j++;
		if (i>k&&j>k) break;
		if (val[pos][i]-val[pos-m][i]!=should[j]) return 0;
		i++;j++;
	}
	return 1;
}
int main()
{
	int x=0;
	while (~scanf("%d%d%d",&n,&m,&k)){
		FOR(i,1,n) scanf("%d",&a[i]);
		FOR(i,1,m) scanf("%d",&b[i]);
//		puts("Ssss");
		FOR(i,1,n)
			FOR(j,0,k+1) val[i][j]=0;
		FOR(i,1,n){
			FOR(j,1,k) val[i][j]=val[i-1][j];
			val[i][a[i]]++;
			FOR(j,1,k) printf("%d ",val[i][j]);puts("");
		}
		FOR(i,1,n)
			FOR(j,0,k+1) should[i][j]=0;
		FOR(i,1,n){
			FOR(j,1,k) should[i][j]=val[i-1][j];
			val[i][a[i]]++;
			FOR(j,1,k) printf("%d ",val[i][j]);puts("");
		}
		ans=0;
		FOR(i,0,n) dp[i]=0;
		
		FOR(i,1,n) printf("%d ",dp[i]);puts("");
		printf("%d\n",ans);
	}
    return 0;
}
/*
10 2 10
1 2 2 1 1 2 1 2 1 2
1 2
*/
