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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

LL m,val,k;
vector<int> edge[maxn];
LL dp[maxn][21][3];
LL now[21][3];
void dfs(int x,int fa){
	for (int v:edge[x]) if (v!=fa) dfs(v,x);
	int i,j;
	dp[x][0][0]=val-1;
	dp[x][1][1]=1;
	dp[x][0][2]=m-val;
	for (int v:edge[x]) if (v!=fa){
		memset(now,0,sizeof(now));
		FOR(i,0,10){
			FOR(j,0,10){
				now[i+j][0]=(now[i+j][0]+dp[x][i][0]*(dp[v][j][0]+dp[v][j][1]+dp[v][j][2])%M)%M;
				now[i+j][1]=(now[i+j][1]+dp[x][i][1]*dp[v][j][0])%M;
				now[i+j][2]=(now[i+j][2]+dp[x][i][2]*(dp[v][j][0]+dp[v][j][2])%M)%M;
			}
		}
		swap(dp[x],now);
	}
}
int n;
int main(){
	int i,j;
	scanf("%d%I64d",&n,&m);
	FOR(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	scanf("%I64d%I64d",&val,&k);
	dfs(1,0);
//	FOR(i,1,n){
//		printf("%d:\n",i);
//		FOR(j,0,10) printf(" %d:%d,%d,%d",j,dp[i][j][0],dp[i][j][1],dp[i][j][2]);
//		puts("");
//	}
	LL ans=0;
	FOR(i,0,k) ans=(ans+dp[1][i][0]+dp[1][i][1]+dp[1][i][2])%M;
	printf("%I64d\n",ans);
}
/*
1 1
1 0
*/
