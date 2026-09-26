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

int n,m;
int i,j,k,t;
int a[maxn],pre[maxn],suf[maxn];
LL ans;
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]);
	ans=1ll*n*(n-1)/2;
	FOR(i,1,n){
		pre[i]=i-1;
		while (pre[i]!=0&&(a[pre[i]]|a[i])==a[i]) pre[i]=pre[pre[i]];
	}
	rFOR(i,1,n){
		suf[i]=i+1;
		while (suf[i]!=n+1&&a[suf[i]]!=a[i]&&(a[suf[i]]|a[i])==a[i]) suf[i]=suf[suf[i]];
	}
	FOR(i,1,n) ans-=1ll*(i-pre[i])*(suf[i]-i)-1;
	printf("%I64d\n",ans);
}
/*
5
3 2 1 6 5

*/
