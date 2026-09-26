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
#include <cstring>
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
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


char s[maxn];
int a[maxn],b[maxn];
LL ans,t,n,m;
int i,j,k;
LL inv[1000002];//inverse
LL fac[1000002];//Factorial
void init(){
	int i;
	fac[0]=1; 
	FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;
}
int C(int n,int m){
	return fac[n]*inv[m]%M*inv[n-m]%M;
}
int main(){
	init(); 
	scanf("%s",s);
	n=strlen(s);
	REP(i,n){
		a[i]=(s[i]=='(');
		if (i>0) a[i]+=a[i-1];
	}
	rREP(i,n){
		b[i]=(s[i]==')');
		b[i]+=b[i+1];
	} 
//	REP(i,n) printf("%d ",a[i]);
//	puts("");
//	REP(i,n) printf("%d ",b[i]);
//	puts("");
//sigma( C(a[i]-1,0 to a[i]-1)*C(b[i],1 to a[i]) )=sigma(C(a[i]-1,a[i]-1 to 0)*C(b[i],1 to a[i]))=sigma(C(a[i]+b[i]-1,a[i]));
	REP(i,n-1) if (s[i]=='(') ans=(ans+C(a[i]+b[i+1]-1,a[i]))%M; 
	printf("%I64d",ans); 
}
/*
*/
