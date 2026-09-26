#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=1e4;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a,double b) {return a>0?a:-a;}


char a[N];
LL b[N][60];
LL n,m;
LL i,j;
int main()
{
	scanf("%I64d%I64d",&n,&m);
	REP(i,7) b[0][i]=INF;
	REP(i,n){
		scanf("%s",a);
		b[i][0]=b[i][1]=b[i][2]=INF;
		REP(j,m){
			if (a[j]>='0'&&a[j]<='9') b[i][0]=min(b[i][0],min(j,m-j));
			if (a[j]>='a'&&a[j]<='z') b[i][1]=min(b[i][1],min(j,m-j));
			if (a[j]=='#'||a[j]=='*'||a[j]=='&') b[i][2]=min(b[i][2],min(j,m-j));
		} 
		if (i>0){
			b[i][3]=min(b[i-1][3],min(b[i-1][0]+b[i][1],b[i-1][1]+b[i][0]));
			b[i][4]=min(b[i-1][4],min(b[i-1][1]+b[i][2],b[i-1][2]+b[i][1]));
			b[i][5]=min(b[i-1][5],min(b[i-1][0]+b[i][2],b[i-1][2]+b[i][0]));
			b[i][6]=min(b[i-1][6],min(min(b[i-1][3]+b[i][2],b[i-1][4]+b[i][0]),b[i-1][5]+b[i][1]));
			b[i][0]=min(b[i][0],b[i-1][0]);
			b[i][1]=min(b[i][1],b[i-1][1]);
			b[i][2]=min(b[i][2],b[i-1][2]);
		} 
//		REP(j,7) printf("%8I64d  ",b[i][j]);
//		printf("\n");
	}
	printf("%I64d",b[n-1][6]);
}
/*
3 4
1**2
a3*0
c4**
*/
