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
const LL M=1e6;
const LL N=1e6;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

LL f[N],g[N],h[M],ff[N];
LL n,m;
LL i,j,k;


int main()
{
	cin>>n;
	FOR(i,1,n) cin>>f[i];
	m=0;
	FOR(i,1,n){
		if (ff[f[i]]==0){
			m++;
			h[m]=f[i];
			ff[f[i]]=m;
		}
		g[i]=ff[f[i]];
	}
	FOR(i,1,m) if (g[h[i]]!=i){
		printf("-1");
		return 0;
	}
	printf("%I64d\n",m);
	FOR(i,1,n) printf("%I64d ",g[i]);
	printf("\n");
	FOR(i,1,m) printf("%I64d ",h[i]);
	return 0;
}
/*
*/
