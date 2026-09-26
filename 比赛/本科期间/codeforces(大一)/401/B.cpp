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
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=1e9+7;
const LL N=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}

int n,m;
char a[N],b[N],c[N],d[N]; 
int i,j,k;
int x,num1,num2;
int main(){
	cin>>n;
	scanf("%s%s",&a,&b);
	sort(a,a+n);
	sort(b,b+n);
	num1=n;j=0;
	REP(i,n)
		for (;j<n;j++) if (b[j]>=a[i]) {num1--;j++;break;}
	num2=0;j=0;
	REP(i,n)
		for (;j<n;j++) if (b[j]>a[i]) {num2++;j++;break;}
	printf("%d\n%d",num1,num2);
}
/*
*/
