#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
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
const LL MOD=1e9+7;
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%MOD) ret=1ll*ret*a%MOD;return ret;}


LL n,q;
LL i,j,k;
LL a[maxn],pos[maxn],b[maxn];
LL ans,all;
int main(){
	scanf("%I64d%I64d",&n,&q);
	FOR(i,1,n) scanf("%I64d",&a[i]);
	FOR(i,n+1,2*n) a[i]=a[i-n];
	FOR(i,1,2*n) a[i]+=a[i-1];
	while(q--){
		scanf("%I64d",&k);
		j=1;ans=n;
		FOR(i,1,n*2) pos[i]=i;
		FOR(i,n,n*2){
			while (a[i]-a[j]>k) j++;
			b[i]=b[j]+1;pos[i]=pos[j];
			if (i-pos[i]>=n) ans=min(ans,b[i]);
		}
		printf("%I64d\n",ans);
	}
}
/*
*/
