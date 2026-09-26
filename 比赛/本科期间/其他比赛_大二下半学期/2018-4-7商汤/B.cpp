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
#include <cassert>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

int n,m;
bitset<207> edge[207],nowu,nowv;
char A[207][207];
int solve(){
	int u,v,i,j,n;
	scanf("%d",&n);
	REP(i,n) scanf("%s",A[i]);
	REP(i,n){
		edge[i]=0;
		REP(j,n)
			if (A[i][j]=='1') edge[i][j]=1;
	}
	static int x=0;
	printf("Case #%d: ",++x);
	REP(u,n) REP(v,n) if (edge[u][v]){
		nowu=nowv=0;
		REP(i,n) if (edge[u][i]) nowu.set(i);
		nowu[v]=nowu[u]=0;
		REP(i,n) if (edge[v][i]) nowv.set(i);
		nowv[v]=nowv[u]=0;
		int x;
		REP(x,n) if (x!=u&&x!=v){
			bitset<207> noww=(edge[x]&nowu);
			bitset<207> now=(edge[x]&nowv);
			// printf("%d-%d check %d\n",u,v,x);
			// REP(i,n) if (noww[i]) printf("%d ",i);
			// puts("");
			// REP(i,n) if (now[i]) printf("%d ",i);
			// puts("");
			if (!noww.count()||!now.count()) continue;
			if ((noww&now).count()>1||(noww^now).count())
				return 0*puts("Starfish!");
		}
		// printf("%d %d\n",u,v);
		// REP(i,n) if (nowu[i]) printf("%d ",i);
		// puts("<- u");
		// REP(i,n) if (nowv[i]) printf("%d ",i);
		// puts("<- v");
	}
	return 0*puts("Walk Walk");
}
int main() {
	int T;
	scanf("%d",&T);
	while (T--) solve();
	return 0;
}
/*
8
5
01111
10111
11011
11101
11110
5
01001
10100
01010
00101
10010
*/
