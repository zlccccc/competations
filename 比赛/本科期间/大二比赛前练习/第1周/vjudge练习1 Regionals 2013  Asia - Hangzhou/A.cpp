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
const int INF=0x3f3f3f3f;

char a[407][407];
int num[407][407];
int posx[20],posy[20];
int n,m,k;
int ans;
bool mark[(1<<16)+7][20];
int dfs(int t,int len){
//	printf("t,len=%d %d\n",t,len);
	int ret=INF,i;
	if (t==(1<<k)-1) return len;
	if (mark[t][len]) return INF;
	mark[t][len]=1;
	REP(i,k){
		int tt=t | (1<<i) | num[posx[i]-1][posy[i]] | num[posx[i]][posy[i]+1];
		if (a[posx[i]-1][posy[i]]!='#'&&a[posx[i]][posy[i]+1]!='#'&&tt!=t)
			ret=min(ret,dfs(tt,len+1));
	}
	return ret;
}
void solve(){
	int i,j;
	memset(a,0,sizeof(a));
	FOR(i,1,n) scanf("%s",a[i]+1);
	memset(num,0,sizeof(num));
	k=0;
	FOR(i,1,n){
		FOR(j,1,m) if (a[i][j]=='.'){
			num[i][j]=1<<k;
			posx[k]=i;
			posy[k]=j;
			k++;
		}
	}
	memset(mark,0,sizeof(mark));
	int ans=dfs(0,0);
	FOR(i,1,n){
		FOR(j,1,m) if (a[i][j]=='.'){
			if (a[i][j-1]!='#'&&a[i-1][j]!='#') {
				memset(mark,0,sizeof(mark));
				ans=min(ans,dfs(num[i-1][j] | num[i][j-1] | num[i][j],0)+1);
			}
			if (a[i][j-1]!='#'&&a[i+1][j]!='#') {
				memset(mark,0,sizeof(mark));
				ans=min(ans,dfs(num[i+1][j] | num[i][j-1] | num[i][j],0)+1);
			}
			if (a[i][j+1]!='#'&&a[i-1][j]!='#') {
				memset(mark,0,sizeof(mark));
				ans=min(ans,dfs(num[i-1][j] | num[i][j+1] | num[i][j],0)+1);
			}
			if (a[i][j+1]!='#'&&a[i+1][j]!='#') {
				memset(mark,0,sizeof(mark));
				ans=min(ans,dfs(num[i+1][j] | num[i][j+1] | num[i][j],0)+1);
			}
		}
	}
	if (ans!=INF) printf("%d\n",ans);
	else puts("-1");
}
int main(){
	while (~scanf("%d%d",&n,&m)&&(n||m)) solve();
}
