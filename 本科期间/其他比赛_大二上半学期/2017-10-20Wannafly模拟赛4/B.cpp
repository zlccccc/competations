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

LL a[maxn];
LL A00,A01,A10,A11;
LL ans;
LL i,n;
int main(){
	scanf("%d",&n);
//	printf("%lld\n",INFF);
	FOR(i,1,n) scanf("%lld",&a[i]);
	A00=A01=A10=A11=INFF;ans=-INFF;
	FOR(i,1,n){
		A00=min(A00,a[i]*a[i]+i*i);
		A01=min(A01,a[i]*a[i]-i*i);
		A10=min(A10,-a[i]*a[i]+i*i);
		A11=min(A11,-a[i]*a[i]-i*i);
	}
	FOR(i,1,n){
		ans=max(ans,a[i]*a[i]+i*i-A00);
		ans=max(ans,a[i]*a[i]-i*i-A01);
		ans=max(ans,-a[i]*a[i]+i*i-A10);
		ans=max(ans,-a[i]*a[i]-i*i-A11);
	}
	printf("%lld\n",ans);
}
/*
2
1 -1000000000
*/
