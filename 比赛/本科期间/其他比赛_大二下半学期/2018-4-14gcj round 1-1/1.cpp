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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}

int T;
char A[107][107];
int p[107][107];
int f[107],g[107];
map<int,int> S;
vector<int> Vx,Vy;
int solve(){
	static int x=0;
	int n,m,a,b,i,j,all=0;
	scanf("%d%d%d%d",&n,&m,&a,&b);
	REP(i,n) scanf("%s",A[i]);
	printf("Case #%d: ",++x);
	REP(i,n) f[i]=0;
	REP(i,m) g[i]=0;
	REP(i,n) REP(j,m) if (A[i][j]=='@')
		all++,f[i]++,g[j]++;
	if (all%(a+1)!=0||all%(b+1)!=0)
		return 0*puts("IMPOSSIBLE");
	a=all/(a+1);b=all/(b+1);
	if (!all) return 0*puts("POSSIBLE");
	Vx.clear();Vy.clear();
	Vx.push_back(0);Vy.push_back(0);
	S.clear();
	rep(i,1,n) f[i]+=f[i-1];
	REP(i,n) S[f[i]]=i+1;
	for (i=a;i<all;i+=a)
		if (!S.count(i)) return 0*puts("IMPOSSIBLE");
		else Vx.push_back(S[i]);
	S.clear();
	rep(i,1,m) g[i]+=g[i-1];
	REP(i,m) S[g[i]]=i+1;
	for (i=b;i<all;i+=b)
		if (!S.count(i)) return 0*puts("IMPOSSIBLE");
		else Vy.push_back(S[i]);
	int one=a*b/all;
	REP(a,(int)Vx.size()-1) REP(b,(int)Vy.size()-1){
		int now=0;
		rep(i,Vx[a],Vx[a+1])
			rep(j,Vy[b],Vy[b+1])
				if (A[i][j]=='@') now++;
		if (now!=one) return 0*puts("IMPOSSIBLE");
	}
	return 0*puts("POSSIBLE");
}
int main() {
	int T;
	scanf("%d",&T);
	while (T--) solve();
	return 0;
}
/*
6
3 6 1 1
.@@..@
.....@
@.@.@@
4 3 1 1
@@@
@.@
@.@
@@@
4 5 1 1
.....
.....
.....
.....
4 4 1 1
..@@
..@@
@@..
@@..
3 4 2 2
@.@@
@@.@
@.@@
3 4 1 2
.@.@
@.@.
.@.@
*/
