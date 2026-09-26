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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=1ll*a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

//刚刚vp才发现当时口胡做掉了..坑爹 
//关键是我TM还记得怎么做 
int i,j,k,n;
int a[maxn];
int minlen,all;
int main(){
	minlen=INF;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]);
	FOR(i,1,n){
		int pre=i,x=a[i];
		if (a[i]!=1) all++;
		while (x!=1&&pre!=0){
			pre--;x=gcd(x,a[pre]);
		}if (x==1) minlen=min(minlen,i-pre);
	}if (minlen==INF) return 0*puts("-1");
//	printf("%d\n",minlen);
	if (!minlen) minlen++;
	printf("%d\n",minlen+all-1);
}
/*
*/
