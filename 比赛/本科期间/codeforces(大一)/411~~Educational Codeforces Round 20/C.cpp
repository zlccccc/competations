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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


LL n,m;
LL i,j,k;
LL t;
int main(){
	scanf("%I64d%I64d",&n,&k);
	if (k>1e8) return 0*puts("-1");
	if (n<k*(k+1)/2) return 0*puts("-1");
	FOR(i,1,n){
		if (i*i>n) break;
		if (n%i==0){
			if (n/i*k<n&&n>=n/i*k*(k+1)/2&&t<n/i) t=n/i;
			if (n>=i*k*(k+1)/2&&t<i) t=i;
		}
	}
	FOR(i,1,k-1){
		n-=i*t;
		printf("%I64d ",i*t);
	}
	printf("%I64d",n);
}
/*
10000000000 130000
*/
