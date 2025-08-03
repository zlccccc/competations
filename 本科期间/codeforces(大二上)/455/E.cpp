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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j;
vector<int> edge[maxn];
int e[maxn];
int deg[maxn],mark[maxn];
vector<int> Q[2];
int ans;
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&e[i]); 
	FOR(i,1,m){
		int u,v;
		scanf("%d%d",&u,&v);u++;v++;
		edge[v].push_back(u);
		deg[u]++;
	}FOR(i,1,n) if (!deg[i]) Q[e[i]].push_back(i);
	while (Q[0].size()||Q[1].size()){
		REP(i,Q[0].size()){
			int u=Q[0][i];
			for (int v:edge[u]){
				deg[v]--;
				if (!deg[v]) Q[e[v]].push_back(v);
			}
		}Q[0].clear();
		if (Q[1].size()) ans++;
		REP(i,Q[1].size()){
			int u=Q[1][i];
			for (int v:edge[u]){
				deg[v]--;
				if (!deg[v]) Q[e[v]].push_back(v);
			}
		}Q[1].clear();
	}printf("%d",ans);
}
/*
*/
