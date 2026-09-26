#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
#define ULL unsigned long long
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,N) for (I=1;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3fll
#define N 1000000
const int M=1e9+7;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
inline int min(int a,int b) {return a>b?b:a;}

ULL a[102][102];
ULL b[102][102];
ULL n,m;
ULL i,j,k;
ULL ii;
ULL x,y,t;
ULL mx,mn=INFF;
bool mark;
int main()
{
	scanf("%I64d%I64d%I64d%I64d%I64d",&n,&m,&k,&x,&y);
	ULL mod=(n*2-2)*m;
	if (mod==0) mod=m;
	t=k/mod;
	k=k%mod;
	ii=1;
	j=0;
	mark=0;
	REP(i,mod){
		if (!mark) ii+=j/m;
		else ii-=j/m;
		if (ii==n) mark=1;
		j=j%m+1;
		a[ii][j]++;
	}
	ii=1;
	j=0;
	mark=0;
	REP(i,k){
		if (!mark) ii+=j/m;
		else ii-=j/m;
		if (ii==n) mark=1;
		j=j%m+1;
		b[ii][j]++;
	}
	for (i=1;i<=n;i++){
			for (j=1;j<=m;j++){
			if (a[i][j]*t+b[i][j]<mn) mn=a[i][j]*t+b[i][j];
			if (a[i][j]*t+b[i][j]>mx) mx=a[i][j]*t+b[i][j];
//			printf("%lld/%lld ",a[i][j],b[i][j]);
		}
//		printf("\n");
	}
	printf("%I64d %I64d %I64d",mx,mn,a[x][y]*t+b[x][y]);
}
