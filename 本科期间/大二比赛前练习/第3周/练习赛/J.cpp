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
LL i,j;
LL a[maxn],b[maxn],c[maxn];
LL l,r,mid,ans;
bool check(LL x){
	LL ans=0,i;
	FOR(i,1,n){
		if (a[i]<=x) ans+=((min(b[i],x)-a[i])/c[i]+1)%2;
	}
//	printf("x=%lld,ans=%lld,%lld\n",x,ans,ans%2);
	if (ans&1) return 1;
	else return 0;
}
int main(){
	while (~scanf("%d",&n)){
		FOR(i,1,n) scanf("%lld%lld%lld",&a[i],&b[i],&c[i]);
		l=-1;r=1ll<<32;
		while (l+1<r){
			mid=(l+r)/2;
//			printf("%d %d\n",mid,check(mid));
			if (!check(mid)) l=mid;
			else r=mid;
		}
		ans=0;r=l+1;
		FOR(i,1,n){
			if (r>=a[i]&&r<=b[i]&&(r-a[i])%c[i]==0) ans++;
		}
		if (ans&1) printf("%lld %lld\n",r,ans);
		else puts("DC Qiang is unhappy.");
	}
}
/*
3
0 10 1
0 10 2
1 10 2
*/ 
