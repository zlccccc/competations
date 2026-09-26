#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


LL ans[10];
LL l,r,i;
void add(LL x,LL val){//x
//	printf("x->val::%d %d\n",x,val);
	while (x>9) x/=10;
	ans[x]+=val;
}
void radd(LL x,LL val){//1->x
//	printf("now---l|r->val::%d %d\n",x,val);
	LL t=1,i;
	while (t*10<=x) t*=10;
	FOR(i,1,9) ans[i]+=val*(t-1)/9;
	FOR(i,1,9){
		if (x>=t*(i+1)-1){
			ans[i]+=val*t;
//			printf("%d--->%d\n",i,val*t);
		}
		else if (x>=t*i) {
			ans[i]+=val*(x%t+1);
//			printf("%d--->%d\n",i,val*(x%t+1));
		}
	}
}
const LL DIV=100000;
void solve(LL x,LL sgn){
	LL i;
	if (x<=DIV) FOR(i,1,x) add(i,sgn*x/i);
	else{
		FOR(i,1,DIV) add(i,sgn*x/i);
		/*ÏÂÃæÊÇDIV+1->x*/
		int l,r;
		FOR(i,1,DIV){
			r=x/i;l=x/(i+1)+1;
			if (l<=DIV) l=DIV+1;
			radd(r,sgn*i);radd(l-1,-sgn*i);
			if (l==DIV+1) break;
		}
	}
}
int main(){
	scanf("%lld%lld",&l,&r);
	solve(r,1);solve(l-1,-1);
	FOR(i,1,9) printf("%lld\n",ans[i]);
}
/*
*/
