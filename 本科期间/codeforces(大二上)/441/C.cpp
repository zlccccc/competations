#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
#include <ctime>
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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

vector<int> edge[maxn*2];
stack<int> S;
int belong[maxn*2];
int dfn[maxn*2],low[maxn*2];
bool vis[maxn*2];
int tot,cnt;
bool mark;
void dfs(int u){
	int i;
	dfn[u]=low[u]=++tot;
	S.push(u);vis[u]=1;
	REP(i,edge[u].size()){
		int v=edge[u][i];
		if (!dfn[v]){
			dfs(v);
			low[u]=min(low[u],low[v]);
		}else if (vis[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if (dfn[u]==low[u]){
		cnt++;
		while (1){
			int now=S.top();S.pop();
			vis[now]=0;
			belong[now]=cnt;
			if (now==u) break;
		}
	}
}
int n,m;
bool solve(){
	int i;tot=0;cnt=0;
	FOR(i,1,2*m) dfn[i]=0;
	FOR(i,1,2*m) vis[i]=0;
	FOR(i,1,2*m) if (!dfn[i]) dfs(i);
	FOR(i,1,m) if (belong[i]==belong[i+m]) return 0;
	return 1;
}
vector<int> val[maxn];
vector<int> ans;
int main(){
	int i,j,k,t;
	scanf("%d%d",&n,&m);
	FOR(i,1,n){
		scanf("%d",&k);
		while (k--) scanf("%d",&t),val[i].push_back(t);
	}
	FOR(i,1,n-1){
		int mark=0;
		REP(j,min(val[i].size(),val[i+1].size())){
			int u=val[i][j],v=val[i+1][j];
			if (u>v){//ok:u,v+m
				edge[u].push_back(u+m);
				edge[v+m].push_back(v);
				mark=1;break;
			}else if (u<v){
				edge[u].push_back(v);
				edge[v+m].push_back(u+m);
				mark=1;break;
			}
		}
		if (!mark&&val[i].size()>val[i+1].size()) return 0*puts("No");
	}
	if (!solve()) return 0*puts("No");
	puts("Yes");
	FOR(i,1,m) if (belong[i]>belong[i+m]) ans.push_back(i);
	printf("%d\n",ans.size());
	for(int now:ans) printf("%d ",now);
}
/*
*/
