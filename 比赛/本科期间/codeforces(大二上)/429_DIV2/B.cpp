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
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

vector<pair<int,int> > edge[maxn];
int color[maxn];
bool mark[maxn];
vector<int> ans;
int dfs(int x){
	mark[x]=1;
	for (auto y:edge[x]){
		if (mark[y.first]) continue;
		dfs(y.first);
		if (color[y.first]==1){
			ans.push_back(y.second);
			color[x]^=1;
			color[y.first]^=1;
		}
	}
}
int root;
int main(){
	int n,m,k;
	int i,j;
	scanf("%d%d",&n,&m);
	FOR(i,1,n){
		scanf("%d",&color[i]);
		if (color[i]==-1) root=i;//如果一棵树不行，那么绝对就不行了.... 
	}
	FOR(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(make_pair(v,i));
		edge[v].push_back(make_pair(u,i));
	}
	if (root){
		dfs(root);
		printf("%d\n",ans.size());
		for(int now:ans) printf("%d ",now);
	}else{
		dfs(1);
		if (color[1]==1) return 0*puts("-1");
//		FOR(i,1,n) if (color[i]==1) return 0*puts("-1");
		printf("%d\n",ans.size());
		for(int now:ans) printf("%d ",now);
	}
}
/*
*/
