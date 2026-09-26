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

int n,k;
LL fac[maxn],inv[maxn];
LL f[maxn],g[maxn],sum[maxn];
int main(){
	int i;
	fac[0]=1;
	FOR(i,1,1000000) fac[i]=fac[i-1]*i%M;
	inv[0]=inv[1]=1;
	FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,2,1000000) inv[i]=inv[i]*inv[i-1]%M;
	scanf("%d%d",&n,&k);
	f[1]=sum[1]=1;LL ans=fac[n-1];
	FOR(i,2,n){
		f[i]=(sum[i-1]-sum[max(0,i-k-1)]+M)*fac[i-2]%M;
		sum[i]=(sum[i-1]+f[i]*inv[i-1])%M;
		(ans+=f[i]*fac[n-1]%M*inv[i-1])%=M;
	}printf("%I64d",(fac[n]-ans+M)%M);
}
/*
*/
