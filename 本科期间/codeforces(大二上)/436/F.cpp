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
const LL maxn=3000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

struct node{
	int to,k,i;
	node(int _to=0,int _k=0,int _i=0):to(_to),k(_k),i(_i){}
};
vector<int> edge[maxn];
vector<node> Q[maxn];
vector<node> A[maxn];
int ans[400007];
int mark[maxn],vis[maxn];//okay
vector<int> S;
void DFS(int x){
	vis[x]=2;//not dfs!
	for (int v:edge[x]) if (vis[v]!=2) DFS(v);
}
void dfs(int x){
	S.push_back(x);mark[x]=1;vis[x]=1;
	for (node now:A[x]) if (now.k<=S.size()) ans[now.i]=S[now.k-1];
	for (int v:edge[x]){
		if (!vis[v]) dfs(v);
		else if (vis[v]==1&&mark[v]){
			while (S.size()&&S.back()!=v) mark[S.back()]=0,S.pop_back();
			DFS(x);break;
		}
	}
	if (S.back()==x) mark[x]=0,S.pop_back();
}
int main(){
	int i,j;
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	FOR(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
	}
	FOR(i,1,n) sort(edge[i].begin(),edge[i].end()); 
	FOR(i,1,q){
		int u,v,k;
		scanf("%d%d%d",&u,&v,&k);
		Q[u].push_back(node(v,k,i));
	}
	memset(ans,0xff,sizeof(ans));
	FOR(i,1,n){
		FOR(j,1,n) A[j].clear();
		for (node now:Q[i]) A[now.to].push_back(now);
		memset(mark,0,sizeof(mark));
		memset(vis,0,sizeof(vis));
		dfs(i);
	}
	FOR(i,1,q) printf("%d\n",ans[i]);
}
/*
*/
