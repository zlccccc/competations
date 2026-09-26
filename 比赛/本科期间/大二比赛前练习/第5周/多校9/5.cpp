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
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=1e4+7;
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
vector<int> E[maxn],edge[maxn];
int n,m;
int dfn[maxn],low[maxn],tot,cnt;
bool vis[maxn];
int id[maxn];
stack<int> S;
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
bool mark[maxn];
int pre;
void dfs(int x){
	mark[x]=1;
	for (int v:edge[x]) if (!mark[v]) dfs(v);
}
int solve(){
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) E[i].clear();
	REP(i,m){
		int u,v;
		scanf("%d%d",&u,&v);
		E[u].push_back(v);
	}
	FOR(i,1,n) dfn[i]=low[i]=vis[i]=0;tot=cnt=0;
	FOR(i,1,n) if (!dfn[i]) tarjin(i);
	FOR(i,1,cnt) edge[i].clear();
	FOR(i,1,n){
		for (int v:E[i]) edge[id[i]].push_back(id[v]);
	}
//	FOR(i,1,n) printf("%d ",id[i]);puts("");
	FOR(i,1,cnt) mark[i]=0;
	pre=0;
	FOR(i,1,cnt) if (!mark[i]){
		dfs(i);
//				int j;
// 				FOR(j,1,cnt) printf("%d ",mark[j]);puts("");
		if (pre!=0&&!mark[pre]) return 0*puts("Light my fire!");
		mark[i]=0;pre=i;
	}
	puts("I love you my love and our love save us!");
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/

