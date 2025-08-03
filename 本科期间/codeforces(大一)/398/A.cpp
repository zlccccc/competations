#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
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
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}


LL n,m;
LL i,j,k;
bool a[N];

int main()
{
	scanf("%I64d",&n);
	k=n; 
	REP(i,n){
		scanf("%I64d",&m);
		a[m]=1;
		while (a[k]==1) printf("%I64d ",k--);
		printf("\n");
	}
}
/*
*/
