#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
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
const LL maxn=1507;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


int n,m;
int i,j,k,t;
char a[maxn];
int sum[255][maxn];
int dp[255][maxn];
char c;
int solve(int *sum,int x,int mx,int mowmx){
	int l,r,mid,ret=0;
	l=x;r=n+1;
//	l=x+mowmx-1;r=n+1;//Ä©Î²Î»ÖÃ
	while (l+1<r){
		mid=(l+r)/2;
		if (mid-x+1-(sum[mid]-sum[x-1])<=mx) l=mid;
		else r=mid;
	}
//	if (i=='o') printf("%d:%d   %d\n",mx,x,l);
	return ret+l-x+1;
}
int main(){
	scanf("%d",&n);
	scanf("%s",&a);
	REP(i,n) sum[a[i]][i]=1;
	FOR(i,'a','z'){
		rep(j,1,n) sum[i][j]+=sum[i][j-1];
		REP(j,n+1)
			REP(k,n) dp[i][j]=max(dp[i][j],solve(sum[i],k,j,max(j,dp[i][j])));//k¿ªÍ· 
	}
//	FOR(i,'a','z'){
//		i='o';
//		printf("%c   ",i);
//		REP(k,n+1) printf("  %d:%d ",k,sum[i][k]);puts("");
//		REP(k,n+1) printf("  %d:%d ",k,dp[i][k]);puts("");
//	}
	scanf("%d",&m);
	REP(i,m){
		scanf("%d%*c%c",&k,&c);
//		cin>>c;
		printf("%d\n",dp[c][k]);
	}
}
