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
const LL MOD=1e9+7;
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%MOD) ret=1ll*ret*a%MOD;return ret;}

#define next nxt
int n,m,w;
int i,j,k;
int a[maxn],b[maxn],next[maxn];
int ans;
int main(){
	scanf("%d%d",&n,&w);
	if (w==1) return 0*printf("%d",n);
	REP(i,n) scanf("%d",&a[i]);
	REP(i,w) scanf("%d",&b[i]);
	n--;w--;
	REP(i,n) a[i]=a[i+1]-a[i];
	REP(i,w) b[i]=b[i+1]-b[i];
	next[0]=-1;
	rep(i,1,w){
		j=next[i-1];
		while (j>=0&&b[j+1]!=b[i]) j=next[j];
		if (b[i]==b[j+1]) j++;
		next[i]=j;
	}
	j=-1;
	ans=0;
	REP(i,n){
		while (j>=0&&b[j+1]!=a[i]) j=next[j];
		if (a[i]==b[j+1]) j++;
		if (j==w-1) ans++;
	}
	printf("%d",ans);
}
/*
13 1
2 4 5 5 4 3 2 2 2 3 3 2 1
3
*/
