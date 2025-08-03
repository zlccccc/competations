#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cstring>
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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}
 
inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}
int n,m,T;
int i,j;
LL ans;
LL h,f;
void print(LL x){
	if (x==0) printf("0");
	LL i=1;
	while (x>=i) i<<=1ll;
	i>>=1ll;
	while (i){
		if (x&i) printf("1");
		else printf("0");
		i>>=1;
	}
	puts("");
}
bool check(LL x){
	LL now=0;
	LL i,t=0;
	while (x>=(1<<t)) t++;
	REP(i,t){
		if (x&(1<<i)) now=now^(f<<i);
	}
	t=0;
	while (now>=(1<<t)) t++;
	for(i=t-1;i-m+1>=0;i--){
		if (now&(1<<i)) now=now^(h<<(i-m+1));
	}
	return (now==1);
}
char a[50],b[50];
int main(){
	while (~scanf("%s",&a)){
		if (a[0]=='0'&&a[1]=='\0') break;
		scanf("%s",b);
		n=strlen(a);
		m=strlen(b);
		ans=0;h=0;f=0;
		REP(i,n){
			f<<=1;
			if (a[i]=='1') f++;
		}
		REP(i,m){
			h<<=1;
			if (b[i]=='1') h++;
		}
		ans=0;
		while (!check(ans)) ans++;
		print(ans);
		a[1]=100;
	}
}
/*
*/ 
