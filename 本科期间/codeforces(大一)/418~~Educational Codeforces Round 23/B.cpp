#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


int n,m;
int i,j,k;
int a[maxn];
LL num1,num2,num3;
int main(){
	scanf("%d",&n);
	REP(i,n) scanf("%d",&a[i]);
	sort(a,a+n);
	i=1;num1=1;
	while (i<n&&a[i]==a[i-1]) i++,num1++;
	if (num1>=3) printf("%lld",num1*(num1-1)*(num1-2)/3/2/1);
	else if (num1==1){
		num2=1;i++;
		while (i<n&&a[i]==a[i-1]) i++,num2++;
		if (num2!=1) printf("%lld",num2*(num2-1)/2);
		else{
			num3=1;i++;
			while (i<n&&a[i]==a[i-1]) i++,num3++;
			printf("%lld",num3);
		}
	}else if (num1==2){
		num2=1;i++;
		while (i<n&&a[i]==a[i-1]) i++,num2++;
		printf("%lld",num2);
	}
//	puts("");
//	printf("%d %d %d\n",num1,num2,num3);
}
/*
6
1 2 3 3 3 3
*/
