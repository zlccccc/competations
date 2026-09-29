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


int main(){
	int n,i;
	LL T,C;
	scanf("%d%lld%lld",&n,&T,&C);
	LL minTemp=INFF,maxTemp=-1,sumVolume=0,sumHeat=0;
	REP(i,n){
		LL t,c;
		scanf("%lld%lld",&t,&c);
		minTemp=min(minTemp,t);
		maxTemp=max(maxTemp,t);
		sumVolume+=c;
		sumHeat+=t*c;
	}
	if (C==0){
		if (minTemp!=maxTemp) puts("Impossible");
		else printf("Possible\n%lld.0000\n",minTemp);
		return 0;
	}
	if (minTemp==T&&maxTemp==T){
		printf("Possible\n%lld.0000\n",T);
		return 0;
	}
	if (minTemp<=T&&T<=maxTemp){
		puts("Impossible");
		return 0;
	}
	LL totalHeat=sumHeat+T*C,totalVolume=sumVolume+C;
	if (maxTemp<T){
		if (totalHeat<maxTemp*totalVolume) puts("Impossible");
		else printf("Possible\n%.4f\n",(double)totalHeat/totalVolume);
	}else{
		if (totalHeat>minTemp*totalVolume) puts("Impossible");
		else printf("Possible\n%lld.0000\n",minTemp);
	}
	return 0;
}
/*
3
10 2
5 1
4 1
6 1
*/
