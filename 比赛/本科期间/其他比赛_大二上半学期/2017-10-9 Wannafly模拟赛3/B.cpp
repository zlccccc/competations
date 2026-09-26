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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,i,j;
int a[maxn];
int ans;
int dfs(LL val,int i,int j,int dep){
//	printf("%lld %d %d %d\n",val,i,j,dep);
	if (dep==0) return 1;
	while (i<=n&&((val>>i)&1)) i++;
	val|=1ll<<i;
	while (j<=n){
		while (j<=n&&(((val>>j)&1)||a[i]!=a[j])) j++;
		if (j>n) break;
		if (dfs(val|(1ll<<j),i,j,dep-1)) return 1;
		j++;
	}
	return 0;
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		REP(i,n) scanf("%d",&a[i]);
//		printf("%d\n",ans);
		if (dfs(0ll,0,1,n/2)) puts("Frederica Bernkastel");
		else puts("Furude Rika");
	}
}
/*
*/
