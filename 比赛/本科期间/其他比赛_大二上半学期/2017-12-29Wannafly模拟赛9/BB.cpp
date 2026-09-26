#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
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
const LL M=998244353;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int T,i,n;
vector<int> edge[maxn];
int root;
int id[maxn],idd[maxn];
unordered_set<int> have[maxn];
int tot,ans;
void dfs(int x){
	id[x]=++tot;have[id[x]].insert(x);
	idd[x]=++tot;have[idd[x]].insert(x);
	have[idd[x]].insert(x-1);
	have[idd[x]].insert(x+1);
	for (int v:edge[x]){
		dfs(v);
		if (have[id[v]].size()>have[id[x]].size())
			swap(id[v],id[x]);
		for (int now:have[id[v]])
			have[id[x]].insert(now);

		if (have[idd[v]].size()>have[idd[x]].size())
			swap(idd[v],idd[x]);
		for (int now:have[idd[v]])
			have[idd[x]].insert(now);
		unordered_set<int>().swap(have[idd[v]]);
		unordered_set<int>().swap(have[id[v]]);
	}if (have[idd[x]].size()-have[id[x]].size()<=2) ans++;
//	printf("x: %d %d %d\n",x,have[id[x]].size(),have[idd[x]].size());
}int d[maxn];
int main(){
	scanf("%d",&n);
	FOR(i,1,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		d[v]++;
	}FOR(i,1,n) if (!d[i]) root=i;
	dfs(root);
	printf("%d\n",ans);
}
/*
4
3 1
1 4
4 2
*/
