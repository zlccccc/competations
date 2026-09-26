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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#define MP make_pair
typedef pair<int,int> pii;
vector<pii> edge[maxn];
vector<int> E[maxn],RE[maxn];
int n,m;
char a[maxn];
double ans;
bool vis[maxn],rvis[maxn];
void dfs(int u){
	vis[u]=1;
	for (auto x:E[u]) if (!vis[x]) dfs(x);
}
void rdfs(int u){
	rvis[u]=1;
	for (auto x:RE[u]) if (!rvis[x]) rdfs(x);
}
double _k[maxn],_x1[maxn],_x2[maxn];
bool VIS[maxn];
void DFS(int u,double k,double x1,double x2){
	if (u==n){
		ans=min(ans,x2/k-x1*x1/k/k);
		return;
	}if (VIS[u]){
		double K=k-_k[u],X1=x1-_x1[u],X2=x2-_x2[u];
		ans=min(ans,X2/K-X1*X1/K/K);
		return;
	}
	_k[u]=k;_x1[u]=x1;_x2[u]=x2;VIS[u]=1;
	for (auto now:edge[u]){
		if (vis[now.first]&&rvis[now.first])
			DFS(now.first,k+1,x1+now.second,x2+now.second*now.second);
	}
	_k[u]=_x1[u]=_x2[u]=0;VIS[u]=0;
}
int main(){
	int i;
	ans=INF;
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		int u,v,len;
		scanf("%d%d%d",&u,&v,&len);
		E[u].push_back(v);
		RE[v].push_back(u);
		edge[u].push_back(MP(v,len));
	}dfs(1);rdfs(n);
//	FOR(i,1,n) printf("%d %d\n",vis[i],rvis[i]);
	DFS(1,0,0,0);
	printf("%.10lf\n",sqrt(ans));
}
/*
2 1
1 2 3
*/
