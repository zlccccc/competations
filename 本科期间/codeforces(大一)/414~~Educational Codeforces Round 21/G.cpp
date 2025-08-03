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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a*=a) ret=1ll*ret*a%M;return ret;}


char a[maxn],b[maxn],c[maxn];
LL fa[maxn];
LL dp[maxn],choose[maxn];
LL i,j,t,mark;
LL n,m;
LL ans,mx;
int main(){
	scanf("%s%s",a,b);
	n=strlen(a);m=strlen(b);
	fa[0]=-1;
	rep(i,1,n){
		j=fa[i-1];
		while (~j&&b[j+1]!=b[i]) j=fa[j];
		if (b[i]==b[j+1]) j++;
		fa[i]=j;
	}
	j=-1;
	dp[0]=0;
	rep(i,m-1,n){
		if (i>=1) dp[i]=dp[i-1];
		mark=1;
		REP(j,m)
			if (a[i-m+1+j]!='?'&&b[j]!=a[i-m+1+j]) mark=0;
		if (mark){
			j=m-1;
			if (i>=1) choose[i]=dp[i-m];
			while (~j) {choose[i]=max(choose[i],choose[i-m+1+j]);j=fa[j];}
			choose[i]++;
			dp[i]=max(dp[i],choose[i]);
		}
	}
//	REP(i,m) printf("%3d",fa[i]);puts("");
//	REP(i,n) printf("%3d",mark[i]);puts("");
//	REP(i,n) printf("%3d",dp[i]);puts("");
	printf("%I64d",dp[n-1]);
}
