#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=2e6+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}

int dp[(1<<7)+7][207];
int dis[207][207];
int cost[207];
int n,m,o;
int i,j,t,k;
int u,v;
int ans;
inline int getid(int x,int y){return (x-1)*m+y;}
bool mark[207];
int pre[(1<<7)+7][207][2][2]; 
int Pre[(1<<7)+7][207][2];
int predis[207][207][2][2];
void dfsdis(int x,int y){
//	printf("dfsdis:%d %d\n",x,y);
	mark[x]=mark[y]=1;
	if (predis[x][y][0][0]) dfsdis(predis[x][y][0][0],predis[x][y][0][1]);
	if (predis[x][y][1][0]) dfsdis(predis[x][y][1][0],predis[x][y][1][1]);
}
void dfs(int x,int y){
//	printf("%d %d\n",x,y);
	mark[y]=1;
	if (pre[x][y][0][0]) dfs(pre[x][y][0][0],pre[x][y][0][1]);
	if (pre[x][y][1][0]) dfs(pre[x][y][1][0],pre[x][y][1][1]);
	if (Pre[x][y][0]) dfsdis(Pre[x][y][0],Pre[x][y][1]);
}
int main(){
	scanf("%d%d%d",&n,&m,&o);
	FOR(i,getid(1,1),getid(n,m))
		FOR(j,getid(1,1),getid(n,m))
			if (i!=j) dis[i][j]=INF;
			else dis[i][j]=0;
	FOR(i,1,n){
		FOR(j,1,m){
			scanf("%d",&cost[getid(i,j)]);
			if (i!=1) dis[getid(i-1,j)][getid(i,j)]=cost[getid(i,j)];
			if (i!=n) dis[getid(i+1,j)][getid(i,j)]=cost[getid(i,j)];
			if (j!=1) dis[getid(i,j-1)][getid(i,j)]=cost[getid(i,j)];
			if (j!=m) dis[getid(i,j+1)][getid(i,j)]=cost[getid(i,j)];
		}
	}
	FOR(k,getid(1,1),getid(n,m))
		FOR(i,getid(1,1),getid(n,m))
			FOR(j,getid(1,1),getid(n,m))
				if (dis[i][k]+dis[k][j]<dis[i][j]){
					predis[i][j][0][0]=i;predis[i][j][0][1]=k;
					predis[i][j][1][0]=k;predis[i][j][1][1]=j;
					dis[i][j]=dis[i][k]+dis[k][j];
				}
	FOR(i,getid(1,1),getid(n,m))
		FOR(j,getid(1,1),getid(n,m)) dis[i][j]+=cost[i];
//	puts("dis , OK :");
//	FOR(i,getid(1,1),getid(n,m)){
//		FOR(j,getid(1,1),getid(n,m)) printf("%10d ",dis[i][j]);
//		puts("");
//	}
	FOR(i,getid(1,1),getid(n,m)) dp[0][i]=cost[i];
	FOR(k,1,(1<<o)-1)
		FOR(i,getid(1,1),getid(n,m)) dp[k][i]=INF;
	REP(i,o){
		int x,y;
		scanf("%d%d",&x,&y);
		dp[1<<i][getid(x,y)]=cost[getid(x,y)];
	}
//	puts("OK2");
	for (int ii=0;ii<o;ii++)//或者queue改变顺序也可(我太懒了) 
	FOR(k,1,(1<<o)-1){
		FOR(i,getid(1,1),getid(n,m)){
			FOR(t,1,(1<<o)-1) if ((k&t)==t&&k!=t){
				if (dp[t][i]+dp[k^t][i]-cost[i]<dp[k][i]){
					dp[k][i]=dp[t][i]+dp[k^t][i]-cost[i];
					pre[k][i][0][0]=t;pre[k][i][0][1]=i;
					pre[k][i][1][0]=k^t;pre[k][i][1][1]=i;
					Pre[k][i][0]=0;Pre[k][i][1]=0;
				}
			}
			FOR(j,getid(1,1),getid(n,m)){
				if (dp[k][j]+dis[j][i]-cost[j]<dp[k][i]){
					dp[k][i]=dp[k][j]+dis[j][i]-cost[j];
					pre[k][i][0][0]=k;pre[k][i][0][1]=j;
					pre[k][i][1][0]=0;pre[k][i][1][1]=0;
					Pre[k][i][0]=j;Pre[k][i][1]=i;
				}
			}
		}
	}
	ans=1;
	FOR(i,1,n)
		FOR(j,1,m) if (dp[(1<<o)-1][getid(i,j)]<dp[(1<<o)-1][ans]) ans=getid(i,j);
//	FOR(k,1,(1<<o)-1){
//		printf("dp:%d\n",k);
//		FOR(i,getid(1,1),getid(n,m)) printf("%d ",dp[k][i]);
//		puts("");
//	}
	printf("%d\n",dp[(1<<o)-1][ans]);
	dfs((1<<o)-1,ans);
	FOR(i,1,n){
		FOR(j,1,m) if (mark[getid(i,j)]) putchar('X');
		else putchar('.');
		puts("");
	}
}
/*
*/
