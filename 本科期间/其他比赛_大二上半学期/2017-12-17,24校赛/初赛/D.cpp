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
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=2e6+7;
const double eps=0.000000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//1/p¿É¼Ó 
LL f[maxn];
LL inv[maxn];
int main(){
	int i;
	int T;
	inv[0]=inv[1]=1;
	FOR(i,2,2000000) inv[i]=(M-M/i)*inv[M%i]%M;
	scanf("%d",&T);
	while (T--){
		int n,a1;
		LL ans=0;
		scanf("%d%d",&n,&a1);ans=a1;
		FOR(i,1,1000000) f[i]=(f[i-1]+1ll*i*i%M*inv[i+a1])%M;
		FOR(i,2,n){
			int l,r;
			scanf("%d%d",&l,&r);
			(ans+=(f[r]-f[l-1]+M)*inv[r-l+1])%=M;
		}printf("%lld\n",ans);
	} 
}
/*
*/
