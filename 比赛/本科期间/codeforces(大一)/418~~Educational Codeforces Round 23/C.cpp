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
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}



bool solve(LL x,LL s){
	LL t=0,i=x;
	while (i){t+=i%10;i/=10;}
//	printf("%d\n",x);
	return abs(t-x)>=s;
}
LL n,s;
LL i,j,k;
LL ans;
int main(){
	scanf("%I64d%I64d",&n,&s);
	if (n<=s+250){FOR(i,s,n) if (solve(i,s)) ans++;}
	else{
		FOR(i,s,s+250) if (solve(i,s)) ans++;
		ans+=n-s-250;
	}
	printf("%I64d",ans);//251~n
}
/*
s+250   mark//180+
*/
