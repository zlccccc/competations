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
const LL maxn=1.5e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k,t;
LL a[1007][107];
int val;
int main(){
	scanf("%d%d",&n,&m);
	FOR(k,1,50) FOR(i,2,n) FOR(j,1,i-1) FOR(t,1,k){
		if (a[i][k]<a[i-j][t-1]+a[j][k-t]+(i-j)*j) a[i][k]=a[i-j][t-1]+a[j][k-t]+(i-j)*j;
	}
//	FOR(i,1,50){
//		FOR(j,1,50) printf("%d ",a[i][j]);puts("");
//	}
	int k=49;
	FOR(i,1,100) printf("%d ",a[n][i]);
	if (a[n][50]<m) return 0*puts("-1");
	else while (k&&a[n][k-1]>=m) k--;
	printf("%d\n",k);
}
/*
100 484372 
1000 484372 
*/
