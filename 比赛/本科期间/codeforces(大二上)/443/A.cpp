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
const LL maxn=2000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int a,b,n;
int i;
int x1,x2,x3,x4,x5;
int main(){
	a=1023;b=0;
	scanf("%d",&n);
	FOR(i,1,n){
		char c;int x;
		cin>>c>>x;
		if (c=='|') a|=x,b|=x;
		if (c=='^') a^=x,b^=x;
		if (c=='&') a&=x,b&=x;
	}
	REP(i,10){
		if (((a>>i)&1)&&((b>>i)&1)){
			x1^=1<<i;x2^=1<<i;
			x4^=1<<i;x5^=1<<i;
		}else if (!((a>>i)&1)&&!((b>>i)&1)){
		}else if (!((a>>i)&1)&&((b>>i)&1)){
			x2^=1<<i;
			x3^=1<<i;
			x5^=1<<i;
		}else if (((a>>i)&1)&&!((b>>i)&1)){
			x2^=1<<i;
			x5^=1<<i;
		}
	}
	puts("5");
	printf("| %d\n",x1);
	printf("& %d\n",x2);
	printf("^ %d\n",x3);
	printf("| %d\n",x4);
	printf("& %d\n",x5);
}
/*
*/
