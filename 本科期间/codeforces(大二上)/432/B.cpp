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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
 
int n,k;
int i,j;
LL cnt[maxn*2],sum[maxn*2];
LL now,ans; 
int main(){
	int x,y;
	scanf("%d%d%d",&n,&x,&y);
	FOR(i,1,n) scanf("%d",&k),cnt[k]++,sum[k]+=k;
	FOR(i,1,2000000) cnt[i]+=cnt[i-1],sum[i]+=sum[i-1];
	ans=INFF;
	FOR(i,2,1000000){
		now=0;
		int t=min(i,x/y+1);
		for(j=i;j<=2000000;j+=i) now+=(cnt[j-t]-cnt[j-i])*x+((cnt[j]-cnt[j-t])*j-(sum[j]-sum[j-t]))*y;
		ans=min(ans,now);
	}
	printf("%I64d\n",ans);
}
/*
*/
