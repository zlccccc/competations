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
const LL M=1e9+7;
const LL N=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

int n,m;
int a[N];
int i,j,k,t;
int mn,mx;

int main(){
	scanf("%d",&n);
	REP(i,n) scanf("%d",&a[i]);
	sort(a,a+n);
	i=n;
	mn=a[0];j=0;
	while (j<n&&a[j]==mn) j++,i--;
	mx=a[n-1];j=n-1;
	while (j>=0&&a[j]==mx) j--,i--;
	if (i>0) printf("%d",i);
	else printf("0");
}
/*
*/
