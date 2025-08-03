#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


int n,m;
int i,j,k,tot;
int u,v;
char a[50];
char A[50];
bool c[1000];
bool d[1000];
char b[50];
char B[50];
int main(){
	a[0]='a';
	A[0]='A';
	scanf("%d%d",&n,&m);
	FOR(i,1,n-m+1){
		scanf("%s",&b);
		if (b[0]=='N') d[i]=1;
	}
//	FOR(i,1,n) printf("%d ",d[i]);
	FOR(i,1,n){
		a[i]=a[i-1]+1;
		A[i]=A[i-1];
		if (a[i]>='z'){
			a[i]='a';
			A[i]++;
		}
		B[i]=A[i]; b[i]=a[i];
		if (i>=m){
			if (d[i-m+1]) {B[i]=B[i-m+1]; b[i]=b[i-m+1];}
		}
		printf("%c%c ",B[i],b[i]);
	}
}
/*
*/
