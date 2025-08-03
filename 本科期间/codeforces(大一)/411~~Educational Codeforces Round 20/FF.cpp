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
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

#define N 100000
int n,m;
int i,j,k;
LL dp[maxn],a[maxn];
int p[maxn];//1<<n-1(×Ü¸öÊý)
LL tot,t,ans;
int main(){
	scanf("%d",&n);
	FOR(i,1,N) p[i]=(p[i-1]*2+1)%MOD;
	FOR(i,1,n) scanf("%d",&t),a[t]++;
	rFOR(i,1,N){
		tot=0;
		for (j=i;j<=N;j+=i) tot=(tot+a[j])%MOD;
		t=p[tot];
		for (j=i*2;j<=N;j+=i) t=(t-dp[j]+MOD)%MOD;
		dp[i]=t;
//		printf("%d %d   %d %d\n",i,tot,t,dp[i]);
	}
	printf("%d",dp[1]);
}
/*
*/
