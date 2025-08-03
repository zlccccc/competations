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
#include <cassert>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

vector<int> edge[maxn];
LL A[maxn];
LL f[maxn][2],g[maxn][2];//g:cnt
LL dfs(int x,int fa){
	f[x][1]=0;f[x][0]=A[x];
	LL ret=f[x][0]%M;
	f[x][1]=0;g[x][0]=1;
	for (int v:edge[x]) if (v!=fa){
		ret+=dfs(v,x);
		(ret+=g[x][0]*f[v][1]*2)%=M;
		(ret+=g[x][1]*f[v][0]*2)%=M;
		(ret+=g[v][0]*f[x][1]*2)%=M;
		(ret+=g[v][1]*f[x][0]*2)%=M;
		(f[x][0]+=f[v][1]+g[v][1]*A[x])%=M;
		(f[x][1]+=f[v][0]-g[v][0]*A[x])%=M;
		g[x][0]+=g[v][1];
		g[x][1]+=g[v][0];
		// dbg(x);dbgln(ret);
		// printf(" %I64d %I64d  %I64d %I64d\n",g[x][0],g[x][1],f[x][0],f[x][1]);
	}
	// dbg(x);dbgln(ret);
	return ret;
}
int main() {
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%I64d",&A[i]);
	FOR(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}LL ans=dfs(1,0);
	(ans+=M)%=M;
	printf("%I64d\n",ans);
}
/*
5
3 14
1 5 -3
3 14
1 3 1
3 14
*/
