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

int cmp(int a,int b){
	return a>b;
}
int a[maxn];
int dp[52][maxn];
int pos[4];
int n,m,c,d;
int i,j,t;
LL all;
int main(){
	scanf("%d%d%d%d%d",&A,&B,&h,&w,&n);
	REP(i,n) scanf("%d",a[i]);
	sort(a,a+n,cmp);
	REP(i,min(n,50)){
		all*=a[i];
		REP(j,n) dp[i][min(j*a[j],n)]=dp[i-1][j]+1;
		rREP(j,n) dp[i][j]=min(dp[i][j],dp[i][j+1]);
		if (all*h*w>A*B) 
	}
	all=1;
	REP(i,n) 

}
/*
2 4 5
2 2 C
2 2 C
*/
