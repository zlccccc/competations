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
const LL maxn=1e6+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const double eps=0.000001;

int n,m,T;
int i,j;
vector<int> val[3];
vector<pair<int,int> > V[3];
int ans[20000][3];
int pos[3];
int tot;
int TTT,now;
int solve(){
	tot=0,TTT=0;now=0;
	pos[0]=pos[1]=pos[2]=0;
	V[0].clear(),V[1].clear(),V[2].clear();
	val[0].clear(),val[1].clear(),val[2].clear();
	FOR(i,1,n-1){
		val[(i-1)%3].push_back(i);
		tot++;now++;
		ans[now][0]=i;
		ans[now][1]=i+1;
		ans[now][2]=tot;
		TTT=(TTT+tot)%3;
	}
	now++;
	val[(n-1)%3].push_back(n);
	TTT=tot+3-TTT;
	ans[now][0]=n;
	ans[now][1]=1;
	ans[now][2]=TTT;
	for(int u:val[0]) 
		for(int v:val[1])
			if (v>u&&v!=u+1&&u!=v+1&&!(v==1&&u==n)&&!(v==n&&u==1)) V[1].push_back(make_pair(u,v));
	for(int u:val[0]) 
		for(int v:val[2])
			if (v>u&&v!=u+1&&u!=v+1&&!(v==1&&u==n)&&!(v==n&&u==1)) V[0].push_back(make_pair(u,v));
	for(int u:val[1])
		for(int v:val[0])
			if (v>u&&v!=u+1&&u!=v+1&&!(v==1&&u==n)&&!(v==n&&u==1)) V[2].push_back(make_pair(u,v));
	for(int u:val[1]) 
		for(int v:val[2])
			if (v>u&&v!=u+1&&u!=v+1&&!(v==1&&u==n)&&!(v==n&&u==1)) V[2].push_back(make_pair(u,v));
	for(int u:val[2]) 
		for(int v:val[0])
			if (v>u&&v!=u+1&&u!=v+1&&!(v==1&&u==n)&&!(v==n&&u==1)) V[0].push_back(make_pair(u,v));
	for(int u:val[2]) 
		for(int v:val[1])
			if (v>u&&v!=u+1&&u!=v+1&&!(v==1&&u==n)&&!(v==n&&u==1)) V[1].push_back(make_pair(u,v));
	for(int u:val[0]) 
		for(int v:val[0])
			if (v>u&&v!=u+1&&u!=v+1&&!(v==1&&u==n)&&!(v==n&&u==1)) V[0].push_back(make_pair(u,v));
	for(int u:val[1]) 
		for(int v:val[1])
			if (v>u&&v!=u+1&&u!=v+1&&!(v==1&&u==n)&&!(v==n&&u==1)) V[0].push_back(make_pair(u,v));
	for(int u:val[2]) 
		for(int v:val[2])
			if (v>u&&v!=u+1&&u!=v+1&&!(v==1&&u==n)&&!(v==n&&u==1)) V[0].push_back(make_pair(u,v));
	while (tot<m){
		tot++;
		if (tot==TTT) tot++;
		if (tot>m) break;
		now++;
		if (pos[tot%3]==V[tot%3].size()) return 0*puts("-1");
		ans[now][0]=V[tot%3][pos[tot%3]].first;
		ans[now][1]=V[tot%3][pos[tot%3]].second;
		ans[now][2]=tot;
		pos[tot%3]++;
	}
	FOR(i,1,m) printf("%d %d %d\n",ans[i][0],ans[i][1],ans[i][2]);
}
int main()
{
	int x=0;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		printf("Case #%d:\n",++x);
		solve();
	}
    return 0;
}
/*
*/
