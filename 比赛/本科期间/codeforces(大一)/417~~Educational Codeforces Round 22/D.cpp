#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
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
const LL maxn=5007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

//l~r不少于k次的连续子序列最大长度 
#define x x_x
#define y y_y
int a[maxn];
int dp[maxn][maxn];
int maxmod[7],maxnum[100007];
int n,m;
int i,j,k;
int x,y;
int ans;
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]);
	FOR(x,0,n){
		REP(k,7) maxmod[k]=0;
		FOR(k,1,n) maxnum[a[k]+1]=maxnum[a[k]-1]=maxnum[a[k]]=0;
		dp[x][0]=dp[0][x];
		FOR(y,1,n){
			if (x<y){
				dp[x][y]=dp[x][0]+1;
				dp[x][y]=max(dp[x][y],maxnum[a[y]-1]+1);
				dp[x][y]=max(dp[x][y],maxnum[a[y]+1]+1);
				dp[x][y]=max(dp[x][y],maxmod[a[y]%7]+1);
				dp[y][x]=dp[x][y];
				ans=max(ans,dp[x][y]);
			}else dp[x][y]=dp[y][x];
			maxnum[a[y]]=max(maxnum[a[y]],dp[x][y]);
			maxmod[a[y]%7]=max(maxmod[a[y]%7],dp[x][y]);
		}
	}
	printf("%d",ans);
}
/*
*/
