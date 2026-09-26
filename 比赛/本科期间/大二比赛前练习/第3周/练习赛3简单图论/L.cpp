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
const LL maxn=10000+7;
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

vector<int> edge[maxn],E[maxn];
int dfn[maxn],low[maxn];
bool vis[maxn];
stack<int> S;
int id[maxn];
int tot,cnt;
void tarjin(int x){
	low[x]=dfn[x]=++tot;
	S.push(x);vis[x]=1;
	for (int v:E[x]){
		if (!dfn[v]){
			tarjin(v);
			low[x]=min(low[x],low[v]);
		}else if (vis[v]){
			low[x]=min(low[x],dfn[v]);
		}
	}
	if (low[x]==dfn[x]){
		cnt++;
		while (1){
			int now=S.top();S.pop();
			vis[now]=0;
			id[now]=cnt;
			if (now==x) break;
		}
	}
}
int used[maxn];
int match[maxn];
int dfs(int u){
	for (int v:edge[u]){
		if (!used[v]){
			used[v]=1;
			if (match[v]==-1||dfs(match[v])){
				match[v]=u;
				match[u]=v;
				return 1;
			}
		}
	}
	return 0;
}
int n,m;
int i,j;
int u,v;
void solve(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) E[i].clear();
	tot=cnt=0;
	REP(i,m){
		scanf("%d%d",&u,&v);
		E[u].push_back(v);
	}
	FOR(i,1,n) dfn[i]=low[i]=vis[i]=0;
	FOR(i,1,n) if (!dfn[i]) tarjin(i);
//	puts("tarjin OK");
	FOR(i,1,cnt*2) match[i]=-1;
	FOR(i,1,cnt*2) edge[i].clear();
	FOR(i,1,n){
		for (int v:E[i]){
			if (id[v]!=id[i]){
				edge[id[i]].push_back(id[v]+cnt);
				edge[id[v]+cnt].push_back(id[i]);
			}
//			printf("%d->%d\n",id[i],id[v]+cnt);
//			printf("%d->%d\n",id[v]+cnt,id[i]);
		}
	}
	int ans=cnt;
	FOR(i,1,cnt){
		if (match[i]==-1){
			FOR(j,1,cnt*2) used[j]=0;
			if (dfs(i)) ans--;
//			printf("%d %d\n",i,ans);
		}
	}
//	puts("dfs OK");
	printf("%d\n",ans);
}
int main()
{
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
