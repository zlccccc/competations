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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

int n,m,k,t;
int i;
int num1,num2,num3;
int main(){
	scanf("%d%d",&n,&m);
	num1=n;num2=n*2;
	FOR(i,1,m){
		scanf("%d",&k);
		t=min(num1,k/4);
		k-=t*4;
		num1-=t;
		if (k==3&&num1){
			num1--;k=0;
			continue;
		}else{
			t=min(num2,k/2);
			k-=t*2;num2-=t;
		}
		if (k==2&&num1) num1--,num3++,k=0;
		if (k==1&&num3) num3--,k=0;
		if (k==1&&num1) num1--,num2++,k=0;
		if (k==1&&num2) num2--,k=0;
		if (num3>=k) num3-=k,k=0;
		if (k) return 0*puts("NO");
	}
	puts("YES");
}
/*
2 7
2 2 2 2 2 2 2
*/
