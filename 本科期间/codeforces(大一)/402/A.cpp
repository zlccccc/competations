#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue> 
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
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
LL a[6];
LL b[6];
LL i,j,k; 
LL ans;
int main(){
	scanf("%d",&n);
	REP(i,n) {scanf("%d",&j);a[j]++;b[j]++;}
	REP(i,n) {scanf("%d",&j);b[j]++;}
	FOR(i,1,5)
		if (b[i]&1) {
			printf("-1");
			return 0;
		}
	else b[i]>>=1;
	FOR(i,1,5) ans+=abs(a[i]-b[i]);
	printf("%d",ans/2);
}
/*
*/
