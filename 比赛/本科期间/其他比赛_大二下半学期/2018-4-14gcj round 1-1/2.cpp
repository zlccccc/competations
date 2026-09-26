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
const LL Mod=1e9+7;
const LL maxn=1000+7;
const double eps=0.00000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%Mod)
		if (b&1) ret=(LL)ret*a%Mod;
	return ret;
}

int T;
int R,B,C;
int M[maxn],S[maxn],P[maxn];
priority_queue<LL> Q;
LL get(LL x){
	int i;
	while (Q.size()) Q.pop();
	LL ret=0;
	REP(i,C)
		Q.push(max((LL)0,min((LL)M[i],(x-P[i])/S[i])));
	REP(i,R)
		ret+=Q.top(),Q.pop();
	// dbg(ret);dbgln(B);
	return ret>=B;
}
int solve(){
	static int x=0;
	int i;
	scanf("%d%d%d",&R,&B,&C);
	REP(i,C) scanf("%d%d%d",&M[i],&S[i],&P[i]);
	printf("Case #%d: ",++x);
	LL l=0,r=INFF+1;
	while (l+1<r){
		LL mid=(l+r)/2;
		if (get(mid)) r=mid;
		else l=mid;
	}cout<<r<<"\n";
	return 0;
}
int main() {
	int T;
	scanf("%d",&T);
	while (T--) solve();
	return 0;
}
/*
3
2 2 2
1 2 3
1 1 2
2 2 2
1 2 3
2 1 2
3 4 5
2 3 3
2 1 5
2 4 2
2 2 4
2 5 1
*/
