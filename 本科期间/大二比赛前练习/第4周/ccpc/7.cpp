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
        a=a*a%M;
        b>>=1;
    }
    return ret;
}
LL sum1[107][107],sum2[107][107];
LL a[maxn];
LL calc(LL t,LL k){
	LL n=0,pre=0,i,j,kk=k;
	while (k){
		a[++n]=k%t;
		k/=t;
	}
	rFOR(i,n/2+1,n) pre=pre*t+a[i];
	rFOR(i,1,n/2) if (a[i]!=a[n-i+1]){
		if (a[i]<a[n-i+1]) pre--;
		break;
	}
//	printf("%lld:%lld,",t,pre);
	pre=pre-sum1[t][(n+1)/2]+sum2[t][n]+1+1;
//	printf("%lld\n",pre);
	return t*pre+kk-pre;
}
int n,m;
int i,j,k;
int main(){
	FOR(i,2,40) sum1[i][0]=1;
	FOR(i,2,40)
		FOR(j,1,40) sum1[i][j]=sum1[i][j-1]*i;
	FOR(i,2,40)
		FOR(j,1,40) sum2[i][j]=sum2[i][j-1]+sum1[i][(j+1)/2-1]*(i-1);
//	FOR(i,10,10){
//		FOR(j,2,10) printf("%lld-%lld  ",sum1[i][j],sum2[i][j]);puts("");
//	}
	int T,x=0;
	scanf("%d",&T);
	while (T--){
		LL L,R,l,r,ans=0;
		scanf("%lld%lld%lld%lld",&L,&R,&l,&r);
		FOR(i,l,r) ans+=calc(i,R)-calc(i,L-1);
		printf("Case #%d: %lld\n",++x,ans);
	}
}
/*
3
1 1 2 36
1 982180 10 10
496690841 524639270 5 20
*/

