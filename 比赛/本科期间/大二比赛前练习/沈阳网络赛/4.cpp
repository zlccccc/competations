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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,k,i;
int a[maxn],b[maxn],c[maxn];
int cnt1,cnt2;
int now;
int solve(){
	scanf("%d%d",&n,&k);
	FOR(i,1,n) scanf("%d",&a[i]);
	cnt1=cnt2=0;
	FOR(i,1,n){
		now=upper_bound(b,b+cnt1,a[i])-b;
		if (now==cnt1) cnt1++;b[now]=a[i];
		now=upper_bound(c,c+cnt2,-a[i])-c;
		if (now==cnt2) cnt2++;c[now]=-a[i];
	}
//	printf("%d %d\n",cnt1,cnt2);
	if (max(cnt1,cnt2)>=n-k) return 0*puts("A is a magic array.");
	else  return 0*puts("A is not a magic array.");
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
*/
