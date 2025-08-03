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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


vector<int> edge[maxn],color[maxn];
int mark[maxn],ans[maxn],mx;
void dfs(int u,int from){
	int i,v,now;
	FOR(i,1,color[u].size()) mark[i]=0;
	REP(i,color[u].size()) if (ans[color[u][i]]) mark[ans[color[u][i]]]=1;
	now=1;
	REP(i,color[u].size())
		if (!ans[color[u][i]]){
			while (mark[now]) now++;
			ans[color[u][i]]=now;
			mark[now]=1;
		}
	REP(i,edge[u].size()){
		v=edge[u][i];
		if (v!=from) dfs(v,u);
	}
}
int n,m;
int i,j,k,t;
int u,v;
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n){
		scanf("%d",&k);
		FOR(j,1,k){
			scanf("%d",&t);
			color[i].push_back(t);
		}
	}
	FOR(i,1,n-1){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1,0);
	FOR(i,1,m) if (ans[i]==0) ans[i]=1;
	FOR(i,1,m) mx=max(mx,ans[i]);
	printf("%d\n",mx);
	FOR(i,1,m) printf("%d ",ans[i]);
}
