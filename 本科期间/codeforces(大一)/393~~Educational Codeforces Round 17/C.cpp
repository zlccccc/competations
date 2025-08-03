#include <cstdio>
#include <cmath>
#include <cstdlib> 
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,N) for (I=1;I<=N;I++)
#define INF 0x3f3f3f3f
#define INFF 0x3f3f3f3f3f3f3f3f
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL N=1e5;
const double eps=0.00000001;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline int min(int a,int b) {return a>b?b:a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline double min(double a,double b) {return a>b?b:a;}
inline int max(int a,int b) {return a<b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline double max(double a,double b) {return a<b?b:a;}
inline int abs(int a,int b) {return a>0?a:-a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a,double b) {return a>0?a:-a;}


string a,b;
vector<int> e[256];
LL le[N+3];
LL ri[N+3];
LL n,m;
LL i,j,k;
LL num=0;
LL l,r;
int main()
{
	cin>>a>>b;
	n=a.length();
	m=b.length();
	i=0;
	REP(j,n){
		if (a[j]==b[i]) le[j]=le[j-1]+1,i++;
		else le[j]=le[j-1];
	}
	i=m-1;
	for (j=n-1;j>=0;j--){
		if (a[j]==b[i]) ri[j]=ri[j+1]+1,i--;
		else ri[j]=ri[j+1];
	}
	r=ri[0];
	for (i=0;i<n;i++) if (le[i]+ri[i+1]>l+r) l=le[i],r=ri[i+1];
	if (l+r>m) cout<<b;
	else if (l+r==0) printf("-");
	else {
		REP(i,l) printf("%c",b[i]);
		for (i=m-r;i<m;i++) printf("%c",b[i]);
	}
	return 0;
}
/*
abacaba
aa
abc
ksdksdsdsnabc
*/
