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

int n,m,all;
int A[maxn],B[maxn];
int used[maxn];
bool check(int s){
	int i;
	FOR(i,1,m) used[i]=0;
	FOR(i,1,all) used[A[s+i-1]]++;
	// printf("s=%d\n",s);
	// FOR(i,1,m) printf("%d ",used[i]);
	FOR(i,1,m) if (used[i]!=B[i]) return 0;
	return 1;
}
int main() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&A[i]);
	FOR(i,1,m) scanf("%d",&B[i]),all+=B[i];
	FOR(i,1,n-all+1) {
		// if (check(i)) printf("i=%d ",i);
		if (check(i)) return 0*puts("YES");
	}
	return 0*puts("NO");
	return 0;
}
/*
5 2
1 1 2 2 1
1 3
*/
