#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=1e-7;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m,k; 
vector<int> edge[maxn];
bool used[maxn];
vector<int> visit[maxn];
int i,j,u,v;
void dfs(int u,int &x){
	int i,v;
	used[u]=1;
	REP(i,edge[u].size()){
		v=edge[u][i];
		if (used[v]) continue;
		if (visit[x].size()==2*n/k+(2*n%k!=0)) x++;
		visit[x].push_back(u);
		dfs(v,x);
	}
	if (visit[x].size()==2*n/k+(2*n%k!=0)) x++;
	visit[x].push_back(u);
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	REP(i,m){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	dfs(1,i=0);
	REP(i,k){
		if (visit[i].size()){
			printf("%d",visit[i].size());
			REP(j,visit[i].size()) printf(" %d",visit[i][j]);
			puts("");
		}
		else puts("1 1");
	}
}
/*
*/
