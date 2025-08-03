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
const LL maxn=1007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


int n,m;
int i,j,k;
char a[maxn];
char b[maxn][maxn*2];
int from[maxn][maxn];
int main(){
	scanf("%d%d",&n,&k);
	scanf("%s",a);
	m=strlen(a);
	b[0][1000]=1;
	FOR(i,1,m){
		if (a[i-1]=='W') FOR(j,1000-k+1,1000+k-1)
			if (b[i-1][j-1]) {b[i][j]='W';from[i][j]=j-1;}
		if (a[i-1]=='L') FOR(j,1000-k+1,1000+k-1)
			if (b[i-1][j+1]) {b[i][j]='L';from[i][j]=j+1;}
		if (a[i-1]=='D') FOR(j,1000-k+1,1000+k-1)
			if (b[i-1][j]) {b[i][j]='D';from[i][j]=j;}
		if (a[i-1]=='?') FOR(j,1000-k+1,1000+k-1){
			if (b[i-1][j-1]) {b[i][j]='W';from[i][j]=j-1;}
			if (b[i-1][j+1]) {b[i][j]='L';from[i][j]=j+1;}
			if (b[i-1][j]) {b[i][j]='D';from[i][j]=j;}
		}
		if (i==m&&(a[i-1]=='W'||a[i-1]=='?')){
			j=1000+k;
			if (b[i-1][j-1]) {b[i][j]='W';from[i][j]=j-1;}
		}
		if (i==m&&(a[i-1]=='L'||a[i-1]=='?')){
			j=1000-k;
			if (b[i-1][j+1]) {b[i][j]='L';from[i][j]=j+1;}
		}
//		FOR(j,985,1015) printf("%4d",j);
//		puts("");
//		FOR(j,985,1015) printf("%4d",from[i][j]);
//		puts("");
//		FOR(j,985,1015) printf("%4c",b[i][j]);
//		puts("");
	}
	if (b[m][1000+k]){
		j=1000+k;
		rFOR(i,1,m) a[i-1]=b[i][j],j=from[i][j];
		printf("%s",a);
	}
	else if (b[m][1000-k]){
		j=1000-k;
		rFOR(i,1,m) a[i-1]=b[i][j],j=from[i][j];
		printf("%s",a);
	}
	else return 0*puts("NO");
}
/*
*/
