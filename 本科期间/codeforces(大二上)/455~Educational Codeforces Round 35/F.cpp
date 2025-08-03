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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#define MP make_pair
int n,i,j,k;
vector<int> edge[maxn];
LL ans=0;
int maxlen,node;
int f[maxn][20];
int dep[maxn];
void dfs(int x,int fa,int len){
	f[x][0]=fa;int i;dep[x]=len;
	rep(i,1,20) f[x][i]=f[f[x][i-1]][i-1];
	if (len>maxlen) node=x,maxlen=len;
	for (int v:edge[x]) if (v!=fa) dfs(v,x,len+1);
}
int lca(int x,int y){
	int i;
	if (dep[x]<dep[y]) swap(x,y);
	rREP(i,20) if (dep[x]-dep[y]>=1<<i) x=f[x][i];
	if (x==y) return x;
	rREP(i,20) if (f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
	return f[x][0];
}
int dis(int x,int y){
	return dep[x]+dep[y]-2*dep[lca(x,y)];
}
queue<int> Q;
int d[maxn];
vector<pair<pair<int,int>,int> > ANS; 
int main(){
	scanf("%d",&n);
	int u,v;
	FOR(i,1,n-1){
		scanf("%d%d",&u,&v); 
		edge[v].push_back(u);
		edge[u].push_back(v);
		d[u]++;d[v]++;
	}dfs(1,0,0);
	u=node;maxlen=0;
	dfs(u,0,0);
	v=node;
//	printf("dfs:%d %d\n",u,v);
	FOR(i,1,n) if (d[i]==1) Q.push(i);
	while (Q.size()){
		int t=Q.front();Q.pop();
		if (t==u||t==v) continue;
		d[t]=-1;
		for (int x:edge[t]) {d[x]--;if (d[x]==1) Q.push(x);}
		int disu=dis(u,t),disv=dis(v,t);
		if (disu<disv) ANS.push_back(MP(MP(v,t),t)),ans+=disv;
		else ANS.push_back(MP(MP(u,t),t)),ans+=disu;
	}
//	puts("OK1");
	Q.push(v);
	while (Q.size()){
		int t=Q.front();Q.pop();
//		printf("t=%d\n",t);
//		if (t==u) continue;
		for (int x:edge[t]) {d[x]--;if (d[x]==1) Q.push(x);}
		ANS.push_back(MP(MP(u,t),t)),ans+=dis(u,t);
	}printf("%I64d\n",ans);
	for (auto now:ANS) printf("%d %d %d\n",now.first.first,now.first.second,now.second);
}
/*
*/
