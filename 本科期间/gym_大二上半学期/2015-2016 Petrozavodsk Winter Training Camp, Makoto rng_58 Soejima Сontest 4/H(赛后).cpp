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
const LL maxn=5000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

#define MP make_pair
int n;
int i,j,k;
LL C[maxn][maxn],m;
LL f[maxn],p[maxn],g[maxn],ans;
void change(LL &x){
	while (x<0) x+=m;
	while (x>=m) x-=m;
}
int main(){
	scanf("%d%I64d",&n,&m);
	C[0][0]=1;
	FOR(i,1,n) FOR(j,0,i){
		if (j==0) C[i][j]=1;
		else C[i][j]=C[i-1][j]+C[i-1][j-1];
		change(C[i][j]);
	}
//	FOR(i,1,n) FOR(j,1,n) printf("C(%d %d)=%d\n",i,j,C[i][j]);
	p[0]=1;FOR(i,1,n) p[i]=p[i-1]*4%m;
	FOR(i,0,n) if (!(i&1))
		FOR(j,0,i) if (!(j&1))
			f[i]=(f[i]+C[i][j]*C[j][j/2]%m*C[i-j][(i-j)/2])%m;
	FOR(i,0,n){
		g[i]=f[i];
		FOR(j,1,i-1) g[i]=g[i]-g[j]*f[i-j]%m,change(g[i]);
	}
	FOR(i,0,n)printf("%d ",g[i]);puts("");
	ans=(n+1)*p[n]%m;
	FOR(i,1,n) ans=ans-g[i]*p[n-i]%m*(n-i+1)%m,change(ans);
	printf("%I64d\n",ans);
}
/*
100 1000000007
*/
