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

int T;
int n,m;
int i,j;
struct node{
	int val,id,pos;
	vector<int> ans;
	node(){vector<int>().swap(ans);val=id=pos=0;}
}dp[1007];
int score[1007],cost[1007];
LL ans;
node max(node a,node b){
	if (a.val>b.val) return a;
	if (a.val<b.val) return b;
	if (a.id<b.id) return a;
	if (a.id>b.id) return b;
	int i;
	REP(i,min(a.ans.size(),b.ans.size())){
//		printf("%d %d\n",a.ans[i],b.ans[i]); 
		if (a.ans[i]<b.ans[i]) return a;
		if (a.ans[i]>b.ans[i]) return b;
	}
	if (a.ans.size()<b.ans.size()) return a;
	else return b;
}
int main()
{
	int x=0,T;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		FOR(i,0,n) dp[i]=node();
		FOR(i,1,m) scanf("%d%d",&score[i],&cost[i]);
		FOR(j,1,m){
			rFOR(i,cost[j],n){
				node now=dp[i-cost[j]];
				now.id+=j;
				now.val+=score[j];
				now.ans.push_back(j);
				dp[i]=max(dp[i],now);
			}
		}
		node ans;
		rFOR(i,0,n){
			dp[i].pos=i;
			ans=max(ans,dp[i]);
		}
		printf("Case #%d:\n",++x);
		printf("%d %d\n",ans.val,ans.pos);
		REP(i,ans.ans.size()){
			printf("%d",ans.ans[i]);
			if (i==ans.ans.size()-1) puts("");
			else printf(" ");
		}
	}
}
/*
*/
