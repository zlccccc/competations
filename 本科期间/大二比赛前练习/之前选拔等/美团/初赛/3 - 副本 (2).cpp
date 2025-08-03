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
#include <ctime>
#include <utility>
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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


LL n,m;
double T,C;
LL i,j,k;
double t[maxn],c[maxn],cc,tt;
double l,r,mid,mark1,mark2;
bool judge(double x){
	double ret=0;
	REP(i,n) ret+=c[i]*(x-t[i])/(T-x);
//	printf("%lf %lf %lf\n",x,ret,C);
	return (ret<=C+eps);
}
int main(){
	scanf("%d",&n);
	scanf("%lf%lf",&T,&C);
	l=INFF;
	REP(i,n){
		scanf("%lf%lf",&t[i],&c[i]);
		if (t[i]>T+eps) mark1=1;
		if (t[i]<T-eps) mark2=1;
		l=min(l,t[i]);
	}
	if (mark1&&mark2) return 0*puts("Impossible");
	if (l<T+eps){
		tt=T*C;cc=C;
		REP(i,n) tt+=t[i]*c[i],cc+=c[i];
		tt/=cc;
	//	printf("%lf %lf   ",tt,cc);
		REP(i,n) if (tt+eps<t[i]) return 0*puts("Impossible");
		puts("Possible");
		printf("%.4lf",tt);
		return 0;
	}else if (judge(l+eps)){
		puts("Possible");
		printf("%.4lf",l);
		return 0;
	}else return 0*puts("Impossible");
}
/*
3
10 2
5 1
4 1
6 1
*/
