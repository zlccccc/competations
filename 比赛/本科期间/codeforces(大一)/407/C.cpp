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
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

LL n,m;
LL i,j,k;
LL a[maxn];
LL b[maxn];
LL c[maxn];
LL ans;
int main()
{
	scanf("%I64d",&n);
	REP(i,n) scanf("%I64d",&a[i]);
	n--;
	REP(i,n) a[i]=abs(a[i]-a[i+1]);
	rREP(i,n){
		b[i]=a[i]+max(0ll,-c[i+1]);
		c[i]=a[i]+min(0ll,-b[i+1]);
		ans=max(ans,b[i]);
	}
	printf("%I64d",ans);
}
