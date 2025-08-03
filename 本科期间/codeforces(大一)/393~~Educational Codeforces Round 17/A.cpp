#include <cstdio>
#include <cmath>
#include <cstdlib> 
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,N) for (I=1;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=3e7;
const double eps=0.00000001;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline int min(int a,int b) {return a>b?b:a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline double min(double a,double b) {return a>b?b:a;}
inline int max(int a,int b) {return a<b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline double max(double a,double b) {return a<b?b:a;}
inline int abs(int a,int b) {return a>0?a:-a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a,double b) {return a>0?a:-a;}


LL a[N];
LL n,m;
LL i,j,k;
LL num;
int main()
{
	scanf("%I64d%I64d",&n,&k);
	FOR(i,sqrt(n)) if (n%i==0){
		num++;
		a[num]=i;
	}
	m=num*2;
	i--;
	if (n==i*i) m--;
	if (k<=num) printf("%I64d",a[k]);
	else if (k<=m) printf("%I64d",n/a[m-k+1]);
	else printf("-1");
//	printf("%d",m);
	return 0;
}
/*
1000000000000000 1000000000
100000000000000 225
*/
