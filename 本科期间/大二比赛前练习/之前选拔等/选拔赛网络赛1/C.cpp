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
const LL MOD=1e9+7;
const LL maxn=1e6+7;
const double eps=1e-8;
const double PI=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%MOD) ret=1ll*ret*a%MOD;return ret;}

#define x x_x
#define y y_y
int n,T;
int i,j,k;
double t;
double l,l1,r1,r;
double x[maxn],y[maxn],ans;
inline double len(double x,double y){
	return sqrt(x*x+y*y);
}
double judge(double t){
	double ret=0;
	int i;
	REP(i,n){
		ret+=t*t;
		t=len(x[i+1]-x[i],y[i+1]-y[i])-t;
	}
	return ret;
}
double solve(double l,double r){
	double l1,r1;
	while (r-l>eps){
		l1=(l*2+r)/3;
		r1=(l+r*2)/3;
		if (judge(l1)>=judge(r1)) l=l1;
		else r=r1;
	}
	return l;
}
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		REP(i,n) scanf("%lf%lf",&x[i],&y[i]);
		x[n]=x[0];y[n]=y[0];
		t=0;r=INFF;l=0;
		REP(i,n){
			t=len(x[i+1]-x[i],y[i+1]-y[i])-t;
			if (i&1) l=max(l,-t);
			else r=min(r,t);
		}
		if ((l>r)||(n%2==0&&fabs(t)>eps)) printf("IMPOSSIBLE\n");
		else{
			if (n&1) ans=t/2;
			else ans=solve(l,r);
			printf("%.2lf\n",judge(ans)*PI);
			REP(i,n){
				printf("%.2lf\n",ans);
				ans=len(x[i+1]-x[i],y[i+1]-y[i])-ans;
			}
		}
	}
}
/*
*/
