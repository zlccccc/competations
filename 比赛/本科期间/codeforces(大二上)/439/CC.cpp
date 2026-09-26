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
const LL M=998244353;
const LL maxn=4e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

LL a,b,c,ans;
LL i,j,k;
LL dp[107][107][107];
int main(){
	FOR(i,1,n)
		FOR(j,1,n)
			FOR(k,1,n)
				dp[i][j][k]=dp[i-1][j-1][k-1]+dp[i-1][j-1][k]+
	scanf("%I64d%I64d%I64d",&a,&b,&c);
	ans=powMM(1,a+b+c);
	if (b-a>100) return 0*puts("0");
	ans=1;
	FOR(i,a+1,b) ans=(ans*i%10)%10;
	printf("%I64d",ans);
}
/*
hh
1
hs
*/
