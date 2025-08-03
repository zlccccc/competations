#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

#define x x_x
#define y y_y
vector<int> edge[maxn];
int fa[maxn],len[maxn],mlen[maxn];
void dfs(int x,int p){
	fa[x]=p;
	len[x]=mlen[x]=len[p]+1;
	for (int v:edge[x]) if (v!=p){
		dfs(v,x);
		mlen[x]=max(mlen[x],mlen[v]);
	}
}
int n,m;
int x,t,u,v,i,ans;
bool mark;
int main(){
	scanf("%d%d",&n,&x);
	REP(i,n-1){
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	len[0]=-1;
	dfs(1,0);
	ans=len[x];
	for (u=x;len[x]-len[u]<len[u];u=fa[u]) ans=max(ans,2*mlen[u]);
	printf("%d",ans);
}
