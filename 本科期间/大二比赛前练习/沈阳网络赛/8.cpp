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

int n,k,i;
int a[maxn];
vector<pair<int,int> > edge[maxn];
int MX[maxn],MN[maxn];
void dfs1(int x,int fa){
	MX[x]=a[x];
	for (pair<int,int> now:edge[x]){
		if (now.first==fa) continue;
		dfs1(now.first,x);
		MX[x]=max(MX[x],MX[now.first]-now.second);
	}
}
LL dfs2(int x,int fa){
	MN[x]=a[x];
	for (pair<int,int> now:edge[x]){
		if (now.first==fa) continue;
		dfs2(now.first,x);
		MN[x]=min(MN[x],MN[now.first]+now.second);
	}
}
void solve(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]);
	FOR(i,1,n-1){
		int u,v,val;
		scanf("%d%d%d",&u,&v,&val);
		edge[u].push_back(make_pair(v,val));
		edge[v].push_back(make_pair(u,val));
	}
	dfs1(1,0);
	dfs2(1,0);
	int ans=0;
	FOR(i,1,n) ans=max(ans,MX[i]-MN[i]);
	printf("%d\n",ans);
	FOR(i,1,n) edge[i].clear();
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
2  
4  
10 40 15 30  
1 2 30
1 3 2
3 4 10


*/
