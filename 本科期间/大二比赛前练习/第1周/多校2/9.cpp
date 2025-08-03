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
inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		b>>=1;
		a=a*a%M;
	}
	return ret;
}

int n;
LL i,j;
LL ans;
LL a[maxn],F[maxn];
LL l,r;
LL solve(){
	scanf("%d",&n);
	REP(i,n) scanf("%lld",&a[i]);
	sort(a,a+n);
	LL D=sqrt(a[0]);//这个不用分块，算错时间复杂度了 
	memset(F,0,sizeof(F));
	FOR(i,2,a[0]) F[i]=1;
	FOR(i,2,a[0]){
		if (i<D){
			REP(j,n) F[i]=(F[i]*(a[j]/i))%M;
		}else{
			r=l=lower_bound(a,a+n,2*i)-a-1;//不满足
			j=2;
			while(r<n-1){
				r=lower_bound(a+l,a+n,(j+1)*i)-a-1;
//				printf("i=%d F[i]=%d j=%d l,r=%d %d %d\n",i,F[i],j,l,r,r-l);
				F[i]=F[i]*powMM(j,r-l)%M;
//				printf("i=%d F[i]=%d j=%d l,r=%d %d %d\n",i,F[i],j,l,r,(j+1)*i-1);
				l=r;
				j++;
			}
		}
	}
	ans=0;
//	printf("OK\n");
//	FOR(i,1,10) printf("%d ",F[i]);puts("");
	rFOR(i,2,a[0]){
		for (j=i+i;j<=a[0];j+=i) F[i]=(F[i]-F[j]+M)%M;
		ans=(ans+F[i])%M;
	}
//	FOR(i,1,10) printf("%d ",F[i]);puts("");
//	printf("OK\n");
	return ans;
}
int main(){
	int T,x=0;
	scanf("%d",&T);
	while (T--){
		printf("Case #%d: %lld\n",++x,solve());
	}
}
/*
1
3
100000 100000 100000
*/
