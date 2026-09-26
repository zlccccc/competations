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
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=1e5;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline double abs(double a,double b) {return a>0?a:-a;}

LL x1,x2;
LL y1,y2;
LL num[N];
LL n,m,z;
LL i,k;
LL u[N],v[N];

int main()
{
	scanf("%I64d",&n);
	printf("YES\n");
	REP(i,n){
		scanf("%I64d%I64d%I64d%I64d",&x1,&y1,&x2,&y2);
		if ((x1&1)&&(y1&1)) printf("1\n");
		if (!(x1&1)&&(y1&1)) printf("2\n");
		if ((x1&1)&&!(y1&1)) printf("3\n");
		if (!(x1&1)&&!(y1&1)) printf("4\n");
	}
}
/*
8
0 0 5 3
2 -1 5 0
-3 -4 2 -1
-1 -1 2 0
-3 0 0 5
5 2 10 3
7 -3 10 2
4 -2 7 -1
*/
