#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=1e9+7;
const LL N=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

LL n,m;
LL i,j,k,t;
LL l,r;
int num(LL n,LL k){
	LL t=0;
	LL n0=n;
	LL sm=0;
	while (n0) n0/=2,t++;
	while (k!=0){
		if ((1ll<<t-1)<=k) {sm+=n/2+n%2;k-=(1ll<<t-1);}
		if ((1ll<<t-1)-1<=k) {sm+=n/2;k-=(1ll<<t-1)-1;}
//		printf("%d %d    %d  k=%d\n",n,(1<<t-1),sm,k);
		n/=2;t--;
	}
	return sm;
}
int main(){
	scanf("%I64d%I64d%I64d",&n,&l,&r);
	printf("%I64d",num(n,r)-num(n,l-1));
}
/*
*/
