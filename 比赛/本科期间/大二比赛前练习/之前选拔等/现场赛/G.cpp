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
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const double eps=0.000000001;
const double pi=acos(-1);
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b){return a>0?a:-a;}

int mark[maxn],cnt;
vector<int> edge[maxn];
void dfs(int x,int len){
	int i;
	cnt=max(cnt,len);
	mark[x]=1;
	if (len==5) return;
	REP(i,edge[x].size()) if (!mark[edge[x][i]]) dfs(edge[x][i],len+1);
	mark[x]=0;
	return;
}
int n,m;
int i;
void solve(){
	bool mark;
	int u,v;
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	cnt=0;
	FOR(i,1,n) dfs(i,1);
	FOR(i,1,n) edge[i].clear();
	if (cnt>=5) puts("yes");
	else puts("no");
}
int T;
int main(){
	scanf("%d",&T);
	while (T--) solve();
}
