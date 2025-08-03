#include <cstdio>
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
const LL N=1e6;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a,double b) {return a>0?a:-a;}


LL a[N+2],b[N+2];
LL c[N+2],d[N+2];
LL n,l;
LL i,j;
bool mark;
int main()
{
	scanf("%I64d%I64d",&n,&l);
	FOR(i,n) scanf("%I64d",a+i);
	rep(i,1,n)
		c[i]=a[i+1]-a[i];
	c[0]=a[1]+l-a[n];
	FOR(i,n) scanf("%I64d",b+i);
	rep(i,1,n)
		d[i]=b[i+1]-b[i];
	d[0]=b[1]+l-b[n];
//	REP(i,n) printf("%I64d  ",d[i]); 
	REP(i,n){
		mark=1;
		REP(j,n) if (c[j]!=d[(j+i)%n]) mark=0;
		if (mark) {
			printf("YES");
			return 0;
		}
	}
	printf("NO");
}
/*
3 8
2 4 6
1 5 7
*/
