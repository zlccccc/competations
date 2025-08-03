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
#include <cassert>
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
const LL M=1000000007;
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}


int T,i,n,q;
LL a[maxn],b[maxn],c[maxn];
LL l[maxn],r[maxn];
LL getr(int x,int y){
//	if (x==y) return 0;
	LL ret=(r[y]-r[x]-b[x-1]*(a[y]-a[x]))%M;
//	printf("get R : %d - %d ,ret=%d\n",x,y,ret);
	return ret;
}
LL getl(int x,int y){
//	if (x==y) return 0;
	LL ret=(l[x]-l[y]-c[y+1]*(a[y]-a[x]))%M;
//	printf("get L : %d - %d ,ret=%d\n",x,y,ret);
	return ret;
}
int main(){
	scanf("%d%d",&n,&q);
	FOR(i,2,n) scanf("%lld",&a[i]);
	FOR(i,1,n) scanf("%lld",&b[i]),c[i]=b[i];
	FOR(i,2,n) (a[i]+=a[i-1])%=M;
	FOR(i,1,n){
		(b[i]+=b[i-1])%=M;
		(r[i]=r[i-1]+(a[i]-a[i-1])*b[i-1])%=M; 
	}
	rFOR(i,1,n){
		(c[i]+=c[i+1])%=M;
		(l[i]=l[i+1]+(a[i+1]-a[i])*c[i+1])%=M;
	}
//	FOR(i,1,n) printf("%d ",a[i]);puts("<a");
//	FOR(i,1,n) printf("%d ",b[i]);puts("<b");
//	FOR(i,1,n) printf("%d ",r[i]);puts("<r");
//	FOR(i,1,n) printf("%d ",c[i]);puts("<c");
//	FOR(i,1,n) printf("%d ",l[i]);puts("<l");
	FOR(i,1,q){
		int x,l,r;
		scanf("%d%d%d",&x,&l,&r);
		LL ans;
		if (x<l) ans=getl(x,r)-getl(x,l-1);
		else if (l<=x&&x<=r) ans=getr(l,x)+getl(x,r);
		else if (r<x) ans=getr(l,x)-getr(r+1,x);
		else assert(0);
		printf("%lld\n",(ans%M+M)%M);
	}
}
/*
5 100
2 3 4 5
1 2 3 4 5
1 1 5
3 1 5
2 3 3
3 3 3
1 5 5
5 1 5
*/
