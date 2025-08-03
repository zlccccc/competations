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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1,a*=a) ret=1ll*ret*a%M;return ret;}


int n,m;
char a[maxn],b[maxn],c[maxn];
int i,j,ei,ej,f,e,k;
bool cmp(char a,char b){
	return a>b;
}
int main(){
	scanf("%s",a);
	scanf("%s",b);
	n=strlen(a);
	sort(a,a+n);
	sort(b,b+n,cmp);
	i=j=f=0;ei=n-n/2-1;ej=n/2-1;e=n-1;
	REP(k,n){
		if (a[i]<b[j]){
			if ((k&1)==0) c[f++]=a[i++];
			else c[f++]=b[j++];
		}
		else{
			if ((k&1)==0) c[e--]=a[ei--];
			else c[e--]=b[ej--];
		}
	}
	printf("%s",c);
//	printf("%d",mark1);
}
/*
*/
