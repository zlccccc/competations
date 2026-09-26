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

char a[200][200];
bool mark[200][200][32];
int val[200][200];
int bfs(int x,int y,int kk){
	memset(mark,0,sizeof(mark));
	queue<int> Qx,Qy,Qk,Qm;
	Qx.push(x);
	Qy.push(y);
	Qk.push(0);
	Qm.push(0);
	while (Qx.size()){
		int x=Qx.front();Qx.pop();
		int y=Qy.front();Qy.pop();
		int k=Qk.front();Qk.pop();
		int t=Qm.front();Qm.pop();
//		printf("%d %d %d %d\n",x,y,k,t);
		if (val[x][y]&&!mark[x][y][t|val[x][y]]){
			Qx.push(x),Qy.push(y),Qk.push(k),Qm.push(t|val[x][y]);
			mark[x][y][t|val[x][y]]=1;
			continue;
		}
		if (t==kk) return k;
		if ((a[x+1][y]=='.'||a[x+1][y]=='@')&&!mark[x+1][y][t]) Qx.push(x+1),Qy.push(y),Qk.push(k+1),Qm.push(t),mark[x+1][y][t]=1;
		if ((a[x-1][y]=='.'||a[x-1][y]=='@')&&!mark[x-1][y][t]) Qx.push(x-1),Qy.push(y),Qk.push(k+1),Qm.push(t),mark[x-1][y][t]=1;
		if ((a[x][y+1]=='.'||a[x][y+1]=='@')&&!mark[x][y+1][t]) Qx.push(x),Qy.push(y+1),Qk.push(k+1),Qm.push(t),mark[x][y+1][t]=1;
		if ((a[x][y-1]=='.'||a[x][y-1]=='@')&&!mark[x][y-1][t]) Qx.push(x),Qy.push(y-1),Qk.push(k+1),Qm.push(t),mark[x][y-1][t]=1;
	}
	return -1;
}
bool solve(int n,int m){
	int i,j;
	FOR(i,1,n) scanf("%s",a[i]+1);
	int t;
	scanf("%d",&t);
	memset(val,0,sizeof(val));
	REP(i,t){
		int x,y;
		scanf("%d%d",&x,&y);
		val[x][y]=1<<i;
	}
	FOR(i,1,n){
		FOR(j,1,m) if (a[i][j]=='@') printf("%d\n",bfs(i,j,(1<<t)-1));
	}
}
int main(){
	int n,m;
	while (scanf("%d%d",&n,&m)&&(n||m)) solve(n,m);
}
