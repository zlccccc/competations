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
int n,k;
LL D[maxn];
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m){
	return fac[n]*inv[m]%M*inv[n-m]%M; 
}
int main() {
	int i;
	D[1]=0;D[2]=1;
	FOR(i,3,1000000) D[i]=(i-1)*(D[i-1]+D[i-2])%M;
	// FOR(i,1,100) printf("%lld ",D[i]);
	fac[0]=1; 
	FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
	while (~scanf("%d%d",&n,&k)){
		LL ans=0;
		FOR(i,0,min(k,n-1)) {
			// printf("%lld %lld %lld\n",C(n-1,i),D[n-i],D[n-i-1]);
			(ans+=C(n-1,i)*(D[n-i]+D[n-i-1])%M)%=M;
			if (i==n-1) (ans+=1)%=M;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
/*
3 1
10 9
10 8
*/
