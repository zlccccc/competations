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
const LL maxn=100+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;

int n,m,T;
int i,j;
int a[107][107],t,k;
int color[107];
vector<int> edge[maxn];
bool dfs(int x,int col){
	color[x]=col;
	if (col==2) col=1;
	else col=2;
	for (int v:edge[x]){
		if (color[v]==0){
			if (dfs(v,col)) return 1;
		}
		else if (color[v]!=col) return 1; 
	}
	return 0;
}
int judge(int n){
	memset(a,0,sizeof(a));
	FOR(i,1,n) edge[i].clear();
	FOR(i,1,n){
		while(~scanf("%d",&k)&&k!=0){
			a[i][k]=1;
		}
		FOR(j,1,n) if (i!=j&&a[i][j]==0){
//			printf("%d->%d\n",i,j);
			edge[i].push_back(j);
			edge[j].push_back(i);
		}
	}
	FOR(i,1,n) color[i]=0;
	FOR(i,1,n){
		if (color[i]==0){
			if (dfs(i,1)) return 0*puts("NO");
		}
	}
//	FOR(i,1,n) printf("%d ",color[i]);puts("");
	return 0*puts("YES");
}
int main(){
	while (~scanf("%d",&n)) judge(n);
    return 0;
}
/*
*/
