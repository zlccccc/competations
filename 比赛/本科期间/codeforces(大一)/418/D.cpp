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
const LL maxn=1007;
const double PI=acos(-1.0);
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


#define x x_x
#define y y_y
int n,m;
int i,j,k,t;
double x[maxn],y[maxn],r[maxn];
double len(double l,double r){
	return sqrt(l*l+r*r);
}
int cnt;
double ans;
int main(){
	scanf("%d",&n);
	REP(i,n) scanf("%lf%lf%lf",&x[i],&y[i],&r[i]);
//	REP(i,n) ans+=r[i]*r[i];
	REP(i,n){
		cnt=0;
		REP(j,n){
			if (r[j]>0.000001+r[i]&&r[j]>0.000001+len(x[j]-x[i],y[j]-y[i])) cnt++;
		}
//		printf("%d %d\n",i,cnt);
		if (cnt%2==1||cnt==0) ans+=r[i]*r[i];
		else ans-=r[i]*r[i];
	}
//	printf("%.15lf",ans);
	ans*=PI;
	printf("%.15lf",ans);
}
