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


LL n,m;
LL i,j,k,t; 
int a[20][4];
int main(){
	REP(i,4)
		FOR(j,1,4) scanf("%d",&a[i][j]);
	rep(i,4,8)
		FOR(j,1,4) a[i][j]=a[i-4][j];
	REP(i,8){
		if (a[i][1]&&a[i][4]) return 0*puts("YES");
		if (a[i][2]&&a[i][4]) return 0*puts("YES");
		if (a[i][3]&&a[i][4]) return 0*puts("YES");
		if (a[i][3]&&a[i+1][4]) return 0*puts("YES");
		if (a[i+1][1]&&a[i][4]) return 0*puts("YES");
		if (a[i][2]&&a[i+2][4]) return 0*puts("YES");
	}
	puts("NO");
}
