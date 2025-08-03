#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n;
long double l,r,mid;//time
long double a[maxn],b[maxn],p;
int i,j;
bool judge(long double t){
	int i;
	long double tt=0;
	REP(i,n){
		if (b[i]>=a[i]*t) continue;
		tt+=(t*a[i]-b[i])/p;
	}
//	printf("%lf %lf\n",t,tt);
	return tt<t;
}
int main()
{
	scanf("%d",&n);
	cin>>p;
	REP(i,n) cin>>a[i]>>b[i];
	l=0;r=5e12;
	REP(i,100){
		mid=(l+r)/2;
		if (judge(mid)) l=mid;
		else r=mid;
	}
	if (l>1e12)
	else printf("%.12Lf",l);
}
