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
const LL M=998244353;
const LL maxn=2e3+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k;
char c[maxn][maxn];
int LU[maxn][maxn],LD[maxn][maxn],RU[maxn][maxn],RD[maxn][maxn];
int U1[maxn][maxn],U2[maxn][maxn],A[maxn][maxn],MAX1[maxn][maxn],MAX2[maxn][maxn];
int ans;
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%s",c[i]+1);
	bool mark=1;
	FOR(i,1,n) FOR(j,1,m){
		if (c[i][j]=='X') {LU[i][j]=LU[i-1][j-1]+1;U1[i][j]=U1[i-1][j]+1;mark=0;MAX1[i][j]=U1[i][j];}
		if (c[i][j]=='O') {U2[i][j]=U2[i-1][j]+1;MAX2[i][j]=U2[i][j];}
	}
	rFOR(i,1,n)FOR(j,1,m) if (c[i][j]=='X') {LD[i][j]=LD[i+1][j-1]+1;}
	FOR(i,1,n) rFOR(j,1,m)if (c[i][j]=='O') {RU[i][j]=RU[i-1][j+1]+1;}
	rFOR(i,1,n)rFOR(j,1,m)if (c[i][j]=='O') {RD[i][j]=RD[i+1][j+1]+1;}
	rFOR(i,1,n)FOR(j,1,m) if (c[i][j]=='X') MAX1[i][j]=max(MAX1[i][j],MAX1[i+1][j-1]);
	rFOR(i,1,n)rFOR(j,1,m)if (c[i][j]=='O') MAX2[i][j]=max(MAX2[i][j],MAX2[i+1][j+1]);
	FOR(i,1,n) FOR(j,1,m)
		A[i][j]=min(min(MAX1[i][j],MAX2[i+1][j+1]),min(min(LU[i][j],LD[i][j]),min(RU[i-1][j+1],RD[i+1][j+1])+1));
	if (mark) return 0*puts("0");
//	FOR(i,1,n){
//		FOR(j,1,n) printf("%d ",RU[i][j]);puts("");
//	}
	ans=0;
	FOR(i,1,n) FOR(j,1,m) FOR(k,ans,A[i][j]) if (U1[i+k][j-k]>=k*2+1&&U2[i+k][j+k]>=k*2+1) ans=k;
	printf("%d\n",ans*2+1);
}
/*
4 4
XOXO
XXOO
XXOO
XOXO
*/
