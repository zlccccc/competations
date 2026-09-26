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

vector<int> edge[maxn*2];
bool vis[maxn*2];
LL dfs(int x,int fa){
	vis[x]=1;
	int size=1,ret=0;
	for (int v:edge[x]){
		if (!vis[v]){
			int t=dfs(v,x);
			if (t<0) ret=t;
			else size+=t;
		}else if (v==x) ret=-1;//不动 
		else if (v!=fa) ret=-2;//占位置 
	}
	if (ret) return ret;
	else return size;
}
int main(){
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	LL ans=1;
	FOR(i,1,n*2) if (!vis[i]) ans=ans*abs(dfs(i,0))%M;
	printf("%d\n",ans);
}
/*
*/
