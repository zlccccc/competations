#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=3e5+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
LL n,m;
LL i,j,k,K;
LL t;
LL powMM(LL a,LL b){
	LL ret=1;
//	if (b==0) return 1;
//	if (a==0) return 0;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}
LL ans;
LL F[maxn],T[maxn];//t表示%==0的个数 
LL inv[maxn],fac[maxn];
vector<LL> E[maxn];
LL C(LL m,LL n){
	return fac[n]*inv[m]%M*inv[n-m]%M;
}
int main(){
	fac[0]=1;
	FOR(i,1,300000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,300000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,300000) inv[i]=inv[i]*inv[i-1]%M;
	FOR(i,1,300000){
		for (j=i;j<=300000;j+=i) E[j].push_back(i);
	}
	while (~scanf("%lld%lld%lld",&n,&m,&K)){
		FOR(i,1,m) T[i]=0;
		FOR(i,1,n){
			scanf("%lld",&k);
			for (LL j:E[k]) T[j]++;
		}
		FOR(i,1,m){
//			F[i]=powMM(m/i,n-T[i])*powMM(m/i-1,T[i]);
			if (n-K<=T[i]){
//				printf("%d %d %d %d\n",i,T[i],K,n);
				F[i]=(C(n-K,T[i])*powMM(m/i,n-T[i])%M*powMM(m/i-1,T[i]-(n-K))%M+M)%M;
			}else F[i]=0;
//			F[i]=F[i]*powMM(2,M-2)%M;
		}
		rFOR(i,1,m){
			for (j=i+i;j<=m;j+=i) F[i]=(F[i]-F[j]+M)%M;
		}
		FOR(i,1,m){
			printf("%lld",F[i]);
			if (i!=m) printf(" ");
		}
		puts("");
	}
}
/*
3 3 1
3 3 3
3 5 3
1 2 3
*/
