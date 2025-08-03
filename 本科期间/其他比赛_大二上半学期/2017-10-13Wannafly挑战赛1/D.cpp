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
const LL maxn=1000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

vector<int> edge[maxn];
int color[maxn][maxn];
int used[maxn],matching[maxn];
int dfs(int u){
	for (auto v:edge[u]){
		if (!used[v]){
			used[v]=1;
			if (!matching[v]||dfs(matching[v])){
				matching[v]=u;matching[u]=v;
				return 1;
			}
		}
	}
	return 0;
}
int U[maxn*2],V[maxn*2]; 
int d[maxn],p[maxn];
int all,ans;
bool cmp(int x,int y){
	return d[x]>d[y];
}
int main(){
	int n,m,i;
	scanf("%d%d",&n,&m);
	REP(i,m) scanf("%d%d",&U[i],&V[i]),d[U[i]]++,d[V[i]]++;
	FOR(i,1,n) p[i]=i;
	while (all<m){
		ans++;
		REP(i,m) if (!color[U[i]][V[i]]){
			edge[U[i]].emplace_back(V[i]);
			edge[V[i]].emplace_back(U[i]);
		}
		sort(p+1,p+n+1,cmp);
		memset(matching,0,sizeof(matching));
		FOR(i,1,n){
			if (!matching[p[i]]){
				memset(used,0,sizeof(used));
				if (dfs(p[i])) all++;
			}
		}
		FOR(i,1,n) if (matching[i]) color[i][matching[i]]=ans,d[i]--;
		FOR(i,1,n) edge[i].clear();
//		printf("%d %d\n",ans,all);
	}
	printf("%d\n",ans);
	REP(i,m) printf("%d\n",color[U[i]][V[i]]);
    return 0;
}
/*
*/
