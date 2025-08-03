#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j,k;
double a[maxn],b[maxn],l,mid,r,p;  
bool check(double x){//sigma(x*a-b)=x*p
	int i;
	double now=0;
	REP(i,n){
		if (b[i]<x*a[i]) now=now+(x*a[i]-b[i]);
	}
	return now<x*p;
} 
double sum1,sum2;
int main(){
	while(~scanf("%d%lf",&n,&p)){
		int i;
		REP(i,n){
			scanf("%lf%lf",&a[i],&b[i]);
		}	
		l=0;r=INF;
		REP(i,100){
			mid=(l+r)/2;
			if (check(mid)) l=mid;
			else r=mid;
		}
		if (r<1e9) printf("%.3lf\n",r);
		else puts("Great Robot!");
	}
}
/*
*/
