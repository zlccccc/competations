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

int n,m,k;
char A[maxn];
int main() {
	int i;
	scanf("%s",A);
	n=strlen(A);
	LL ans=1;
	REP(i,n){
		if (A[i]=='i'||A[i]=='I'||A[i]=='l'||A[i]=='L')
			ans=ans*4%M;
		else if (A[i]=='o'||A[i]=='O'||A[i]=='0')
			ans=ans*3%M;
		else if ('a'<=A[i]&&A[i]<='z')
			ans=ans*2%M;
		else if ('A'<=A[i]&&A[i]<='Z')
			ans=ans*2%M;
	}
	printf("%lld\n",ans);
	return 0;
}
/*
*/
