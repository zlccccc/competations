#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=10000;
const LL N=1000;
const double eps=1e-7;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

int n,m;
double P[M+2][N+2];
int i,j;
int k,q;
double p;

int main(){
	scanf("%d%d",&k,&q);
	P[0][0]=1;
	FOR(i,1,M)
		FOR(j,1,k) P[i][j]=P[i-1][j]*j/k+P[i-1][j-1]*(k-j+1)/k;
	REP(i,q){
		scanf("%lf",&p);
		for (j=0;P[j][k]<(p-eps)/2000;j++);
		printf("%d\n",j);
	}
}
/*
*/
