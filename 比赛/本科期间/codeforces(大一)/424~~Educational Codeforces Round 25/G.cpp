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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

int n,q;
int i,j,k;
int u,v;
int ans,mn;
vector<int> edge[maxn];//∑¥œÚ¡¨±ﬂ 
int down[maxn];
void dfs(int x,int fa,int val){
	down[x]=val;
	for (int v:edge[x]) if (v!=fa){
		dfs(v,x,min(v,val));
	}
}
int main(){
	scanf("%d%d",&n,&q);
	REP(i,n-1){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	scanf("%d%d",&k,&u);
	u=(u+ans)%n+1;
	dfs(u,u,u);
	mn=INF;
	REP(i,q-1){
		scanf("%d%d",&k,&u);
		u=(u+ans)%n+1;
		if (k==1) mn=min(mn,down[u]);
		else printf("%d\n",ans=min(down[u],mn));
	}
}
/*
*/
