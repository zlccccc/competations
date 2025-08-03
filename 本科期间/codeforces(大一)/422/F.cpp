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
const LL maxn=5e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


int n;
int i,j,k;
int u,v;
vector<pair<int,int> > edge[maxn];
void dfs(int x,int fa,double t){
	double t_t=2.0/edge[x].size();
	int i;
	REP(i,edge[x].size()) if (edge[x][i].first!=fa){
		t+=t_t;
		if (t<0) t+=2;
		if (t>2) t-=2;
		if (t<1) printf("1 %d %d %d %.10lf\n",edge[x][i].second,x,edge[x][i].first,t);
		else printf("1 %d %d %d %.10lf\n",edge[x][i].second,edge[x][i].first,x,t-1);
		dfs(edge[x][i].first,x,t-1);
	}
}
int main(){
	scanf("%d",&n);
	FOR(i,1,n-1){
		scanf("%d%d",&u,&v);
		edge[u].push_back(make_pair(v,i));
		edge[v].push_back(make_pair(u,i));
	}
	printf("%d\n",n-1);
	dfs(1,0,0.0);
}
/*
3
1 2
2 3
*/
