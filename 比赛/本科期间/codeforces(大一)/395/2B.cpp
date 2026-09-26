#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=1e6;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline double abs(double a,double b) {return a>0?a:-a;}


LL a[N];
LL n,m,z;
LL i;
LL ans;
int main()
{
	scanf("%I64d",&n);
	FOR(i,1,n) scanf("%I64d",a+i); 
	for (i=1;i<=n-i+1;i+=2) if (i!=n-i+1) a[i]^=a[n-i+1]^=a[i]^=a[n-i+1];
	FOR(i,1,n) printf("%I64d ",a[i]);
}
/*
7
4 3 7 6 9 1 2
8
6 1 4 2 5 6 9 2
*/
