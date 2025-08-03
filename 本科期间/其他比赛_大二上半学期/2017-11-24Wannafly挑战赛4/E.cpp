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
const LL M=1e9+7;
const LL MAX=1e6+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

inline LL poww(LL a,LL b,LL p){
	LL ret=1;
	for (;b;b>>=1,a=a*a%p)
		if (b&1) ret=ret*a%p;
	return ret;
}
LL a,b,p;
int T;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld",&a,&b,&p);
		if (p==2){
			if (!b) puts("Yes");
			else if ((1+a)&1) puts("Yes");
			else puts("No");
		}else{
			LL c=-b+a*a%p*poww(4,p-2,p);
			c%=p;c+=p;c%=p;
			if (!c||poww(c,(p-1)/2,p)==1) puts("Yes");
			else puts("No");
		}
	}
}
/*
*/
