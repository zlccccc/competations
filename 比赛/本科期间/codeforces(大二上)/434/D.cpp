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

#define MP make_pair
vector<int> edge[maxn];
bool mark[maxn];
int cnt[maxn];
vector<pair<pair<int,int>,int> > ans;
set<pair<int,int> > used;
void dfs(int u,int f){//ok_pos
	int v=0;
	mark[u]=1;
	for (int w:edge[u]){
		if (w==f) continue;
		if (used.count(MP(u,w))) continue;
		if (!mark[w]) dfs(w,u);
		if (used.count(MP(u,w))) continue;
		if (v){
			used.insert(MP(u,v));used.insert(MP(v,u));
			used.insert(MP(u,w));used.insert(MP(w,u));
			ans.push_back(MP(MP(v,u),w)),v=0;
		}else v=w;
	}
	if (v&&f){
		used.insert(MP(u,f));used.insert(MP(f,u));
		used.insert(MP(u,v));used.insert(MP(v,u));
		ans.push_back(MP(MP(f,u),v));
	}
}
int main(){
	int n,m,i,j;
	scanf("%d%d",&n,&m);
	REP(i,m){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	FOR(i,1,n) if (!mark[i]) dfs(i,0);
	printf("%d\n",ans.size());
	for (pair<pair<int,int>,int> now:ans) printf("%d %d %d\n",now.first.first,now.first.second,now.second);
}
/*
*/
