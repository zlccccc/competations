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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#define MP make_pair
int n;
vector<int> edge[maxn];
int S[maxn],W[maxn];//size,weight
vector<pair<int,pair<int,int> > > ans;
vector<int> V;int minweight;
void dfs(int x,int fa){
	S[x]=1;
	for (int v:edge[x]) if (v!=fa){
		dfs(v,x);
		S[x]+=S[v];
		W[x]=max(W[x],S[v]); 
	}
	W[x]=max(W[x],n-S[x]);
	if (minweight>W[x]) V.clear(),minweight=W[x];
	if (minweight==W[x]) V.emplace_back(x);
}
void cal(int u,int v,int &nowv,int x,int fa){
	for (int y:edge[x]) if (y!=fa){
		if (y!=nowv&&x!=v){
			ans.push_back(MP(u,MP(nowv,y)));
			nowv=y;
			ans.push_back(MP(y,MP(x,v)));
		}
		cal(u,v,nowv,y,x);
	}
}
int main(){
	int i,j;
	scanf("%d",&n);
	REP(i,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}minweight=INF;
	dfs(1,0);
	for (int u:V){
		for (int x:edge[u]) if (W[x]!=minweight){
			int nowv=x,v=x;
			cal(u,v,nowv,x,u);
			if (nowv!=v) ans.push_back(MP(u,MP(nowv,v)));
		}
	}
	printf("%d\n",ans.size());
	for (auto now:ans) printf("%d %d %d\n",now.first,now.second.first,now.second.second);
}
/*
*/
