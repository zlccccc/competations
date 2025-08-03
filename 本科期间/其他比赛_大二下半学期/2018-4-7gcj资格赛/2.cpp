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

int A[maxn],B[maxn],C[maxn],D[maxn];
int solve(){
	int i,n;
	scanf("%d",&n);
	REP(i,n) scanf("%d",&A[i]);
	REP(i,n) {
		if (!(i&1)) C[i/2]=A[i];
		else D[i/2]=A[i];
	}sort(C,C+n-n/2);sort(D,D+n/2);
	sort(A,A+n);
	REP(i,n) {
		if (!(i&1)) B[i]=C[i/2];
		else B[i]=D[i/2];
	}static int x=0;
	printf("Case #%d: ",++x);
	REP(i,n) if (A[i]!=B[i]) return 0*printf("%d\n",i);
	return 0*puts("OK");
}
int main() {
	int T;
	scanf("%d",&T);
	while (T--) solve();
	return 0;
}
/*
2
5
5 6 8 4 3
3
8 9 7
*/
