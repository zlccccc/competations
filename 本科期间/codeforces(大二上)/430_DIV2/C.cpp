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
//Ã»½» 
int n,m,t;
int i;
vector<int> edge[maxn];
vector<int> DIV;
int val[maxn];
int cnt[maxn];
int ans[maxn];
void dfs(int x,int fa,int VAL){
	int i;
	REP(i,DIV.size()) if (val[x]%DIV[i]!=0) cnt[i]++;
	for (int v:edge[x]){
		if (v==fa) continue;
		if (fa==0) dfs(v,x,val[v]);
		else dfs(v,x,gcd(val[v],VAL));
	}
	REP(i,DIV.size()) if (cnt[i]<=1) ans[x]=max(ans[x],DIV[i]);
	REP(i,DIV.size()) if (val[x]%DIV[i]!=0) cnt[i]--;
	ans[x]=max(ans[x],VAL);
}
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&val[i]);
	REP(i,n-1){
		int u,v;
		scanf("%d%d",&u,&v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	FOR(i,1,val[1]) if (val[1]%i==0) DIV.push_back(i);
//	REP(i,DIV.size()) printf("%d ",DIV[i]);puts("");
	dfs(1,0,val[1]);
	FOR(i,1,n) printf("%d ",ans[i]);
}
/*
*/
