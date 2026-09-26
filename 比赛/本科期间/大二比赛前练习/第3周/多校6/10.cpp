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
const LL maxn=5000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}
inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}
int n,k;
int i;
vector<int> edge[maxn];
bool mark;
int dfs(int x,int fa){
	int cnt=0;
	for (int v:edge[x]){
		int t=dfs(v,x);
		if (t!=0) cnt++;
	}
	if (cnt>1) mark=1;
	cnt^=1;
	return cnt;
}
int main()
{
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&k);
		FOR(i,1,n) edge[i].clear();
		FOR(i,2,n){
			int v;
			scanf("%d",&v);
			edge[v].push_back(i);
		}
		mark=0;
		dfs(1,0);
		if (mark) puts("Alice");
		else if (n%2==1) puts("Alice");
		else if (n/2-1>k) puts("Alice");
		else puts("Bob");
	}
}
/*
5
4 1
2 3 4
*/
