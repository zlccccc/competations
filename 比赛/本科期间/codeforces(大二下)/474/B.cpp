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

int n,k1,k2;
int A[maxn],B[maxn];
priority_queue<int> Q;
LL ans;
int main() {
	int i;
	scanf("%d%d%d",&n,&k1,&k2);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,n) scanf("%d",&B[i]);
	// sort(A+1,A+1+n); sort(B+1,B+1+n);
	FOR(i,1,n) Q.push(abs(A[i]-B[i]));
	k1+=k2;
	while (k1--) {
		int t=Q.top(); Q.pop();
		Q.push(abs(t-1));
	} while (Q.size()) {
		int t=Q.top(); Q.pop();
		ans+=(LL)t*t;
	} printf("%I64d\n",ans);
	return 0;
}
/*
1 0 0
-1000000
1000000
*/
