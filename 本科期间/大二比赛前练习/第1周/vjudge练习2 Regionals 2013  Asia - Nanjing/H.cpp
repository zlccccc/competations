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
const LL maxn=(1<<10)+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;

int n;
const int MID=307;
vector<int> edge[maxn];
LL dp[307][3][614];//pos,num,val
//0:not choose
//1:choose,&1=1;
//2:choose,&1=0;
LL ans;
LL low[maxn],high[maxn];
void dfs(int x,int fa){
	int i,j;
	memset(dp[x],0,sizeof(dp[x]));
	low[x]=0,high[x]=1;
	dp[x][0][MID]=2;
	dp[x][1][MID]=1;
	LL t[3][614];
	for (int v:edge[x]) if (v!=fa){
		dfs(v,x);
		memset(t,0,sizeof(t));
		FOR(i,low[x],high[x]){
			FOR(j,low[v]-1,high[v]+1){
				if (i+j>n||i+j<-n) continue;
				t[0][MID+i+j]=(t[0][MID+i+j]+dp[x][0][MID+i]*dp[v][0][MID+j]%M+dp[x][0][MID+i]*dp[v][1][MID+j-1]%M+dp[x][0][MID+i]*dp[v][2][MID+j+1]%M)%M;
				t[1][MID+i+j]=(t[1][MID+i+j]+dp[x][1][MID+i]*dp[v][0][MID+j]%M+dp[x][1][MID+i]*dp[v][2][MID+j]%M+dp[x][2][MID+i]*dp[v][1][MID+j]%M)%M;
				t[2][MID+i+j]=(t[2][MID+i+j]+dp[x][2][MID+i]*dp[v][0][MID+j]%M+dp[x][1][MID+i]*dp[v][1][MID+j]%M+dp[x][2][MID+i]*dp[v][2][MID+j]%M)%M;
				if (t[0][MID+i+j]!=0||t[1][MID+i+j]!=0||t[2][MID+i+j]!=0){
					if (i+j<low[x]) low[x]=i+j;
					if (i+j>high[x]) high[x]=i+j;
				}
			}
		}
		FOR(i,low[x],high[x]){
			dp[x][0][MID+i]=t[0][MID+i];
			dp[x][1][MID+i]=t[1][MID+i];
			dp[x][2][MID+i]=t[2][MID+i];
		}
	}
}
int main()
{
	int i;
	while(~scanf("%d",&n)){
		REP(i,n-1){
			int u,v;
			scanf("%d%d",&u,&v);
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		dfs(1,0);
		ans=0;
		FOR(i,1,n+1){
			ans=(ans+(i*dp[1][0][MID+i]))%M;
			ans=(ans+(i*dp[1][1][MID+i-1]))%M;
			ans=(ans+(i*dp[1][2][MID+i+1]))%M;
		}
		ans=ans*3%M;
		printf("%d\n",ans);
		FOR(i,1,n) vector<int>().swap(edge[i]);
	}
	return 0;
}
