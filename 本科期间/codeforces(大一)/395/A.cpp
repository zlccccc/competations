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


LL c[N];
LL num[N];
LL n,m,z;
LL i,k;
LL u[N],v[N];
int main()
{
	scanf("%I64d",&n);
	REP(i,n-1) scanf("%I64d%I64d",u+i,v+i);
	FOR(i,1,n) scanf("%I64d",&c[i]);
	REP(i,n-1) if (c[u[i]]!=c[v[i]]) num[u[i]]++,num[v[i]]++;
	FOR(i,1,n) if (num[i]>0){
		if (num[i]==1&&k!=0) continue;
		if (num[k]>=2){
			printf("NO");
			return 0;
		}
		k=i;
	}
	REP(i,n-1) if (c[u[i]]!=c[v[i]]&&u[i]!=k&&v[i]!=k){
			printf("NO");
			return 0;
	}
	printf("YES\n");
	if (k==0) printf("1");
	else printf("%I64d",k);
}
/*
4
1 2
2 3
3 4
1 2 1 1
3
1 2
2 3
1 2 3
4
1 2
2 3
3 4
1 2 1 2
*/
