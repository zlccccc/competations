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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

LL n,T;
int i,j;
LL dp1[maxn],dp2[maxn];
LL ans;
int main(){
//	printf("%d\n",powMM(2,10));
	dp1[0]=1;dp2[0]=1;
	dp1[1]=2;dp2[1]=2;
	FOR(i,2,100000){
		dp1[i]=(dp1[i-1]*2+dp1[i-2]*4+dp2[i-1]*2)%M;
		dp2[i]=dp2[i-1]*2%M;
	}
//	FOR(i,1,10) printf("%d ",dp1[i]);puts("");
//	FOR(i,1,10) printf("%d ",dp2[i]);puts("");
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
//		if (n==1) puts("2");
//		else if (n==2) puts("24");
//		else{
		ans=0;
		FOR(i,1,n) {
			if (i==1||i==n) ans=(ans+dp1[n])%M;
			else ans=(ans+dp2[i]*dp1[n-i]%M+dp2[n-i+1]*dp1[i-1]%M)%M;
//			printf("%d:%d\n",i,ans);
		}
		printf("%I64d\n",ans);
//		}
	}
}
/*
5
1
2
3
4
5
*/
