#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=5e6+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}
LL n,m,T;
int i,j;
LL ans1,ans2,t;
int main(){
	int T;
	scanf("%lld",&T);
	while (T--){
		scanf("%lld%lld",&n,&m);
		t=m;
		ans1=1;ans2=0;
		FOR(i,2,m){
			ans1=ans1*n;
			ans2=ans2*n;
			ans2+=ans1/10000000000;
			ans1=ans1%10000000000;
			if (ans2==0){
				LL g=gcd(t,ans1);
				t/=g;ans1/=g;
			}
		}
		if (ans2!=0) printf("%lld/%lld%010lld\n",t,ans2,ans1);
		else printf("%lld/%lld\n",t,ans1);
	}
}
/*
*/ 
