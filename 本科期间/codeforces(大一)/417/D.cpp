#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


int n,m,k,q;
int i,j;
int u,v,t;
int in[maxn],out[maxn],tot;
vector<int> edge[maxn];
int dfs(int x){
	in[x]=++tot;
	for (int v:edge[x])
		dfs(v);
	out[x]=tot;
}
int fa[maxn],a[maxn];
int len[maxn];
int main(){
	scanf("%d%d%d%d",&n,&m,&k,&q);
	REP(i,k) {
		scanf("%d%d",&v,&t);
		if (a[t]==v) continue;
		fa[v]=a[t];a[t]=v;
	}
	FOR(i,1,n) edge[fa[i]].push_back(i);
	FOR(i,1,n) if (!in[i]) dfs(i);
	REP(i,q){
		scanf("%d%d",&u,&t);
		v=a[t];
		if (in[u]<=in[v]&&in[v]<=out[u]) printf("%d\n",out[u]-in[u]+1);
		else puts("0");
	}
}
/*
*/
