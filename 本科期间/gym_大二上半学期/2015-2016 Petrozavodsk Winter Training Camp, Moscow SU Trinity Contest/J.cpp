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

int n,m;
vector<pair<int,char> > edge[maxn];
int up[maxn],dn[maxn],fu[maxn],fd[maxn];
char s[maxn];
void dfs(int x,int fa){
	up[x]=0;dn[x]=m-1;fu[x]=fd[x]=x;
	for (auto now:edge[x]) if (now.first!=fa){
		int u=now.first;dfs(u,x);
		int _u=up[u]+(now.second==s[up[u]]),_d=dn[u]-(now.second==s[dn[u]]);
		if (up[x]>_d){printf("%d %d\n",fu[x],fd[u]);exit(0);}
		if (_u>dn[x]){printf("%d %d\n",fu[u],fd[x]);exit(0);}
		if (_u>up[x]) up[x]=_u,fu[x]=fu[u];
		if (_d<dn[x]) dn[x]=_d,fd[x]=fd[u];
	}
//	printf("%d:%d %d\n",x,up[x],dn[x]);
}
int main(){
	scanf("%d%d",&n,&m);
	int i;
	REP(i,n-1){
		int u,v;char c;
		scanf("%d%d",&u,&v);cin>>c;
		edge[u].push_back(make_pair(v,c));
		edge[v].push_back(make_pair(u,c));
	}; 
	scanf("%s",s);
	dfs(1,0);
	puts("-1 -1");
}
/*
3 3
2 0 -2
0 -2 0
-2 0 2
*/
