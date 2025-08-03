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
const LL maxn=5000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//只有一个点:X=P*F+S*(S+X);
//也就是说,最优选择是time过高直接会回到初始点(X) 
//DP[i][j]表示i,time=j时的期望时间 
int n,m;
int F[57],S[57],R;
double P[57];
double DP[57][maxn];
double l,r,mid;
bool judge(double x){
	int i,j;
	FOR(i,1,n+1) FOR(j,0,6000) DP[i][j]=INF;
	FOR(i,1,R) DP[n+1][i]=0;
	rFOR(i,1,n){
		FOR(j,0,R)
			DP[i][j]=P[i]*(F[i]+min(DP[i+1][j+F[i]],x))+
				(1.-P[i])*(S[i]+min(DP[i+1][j+S[i]],x));
	}
	return x<DP[1][0];
}
int main(){
	scanf("%d%d",&n,&R);
	int i;
	FOR(i,1,n) scanf("%d%d%lf",&F[i],&S[i],&P[i]),P[i]/=100;
	l=0;r=1e9;
	REP(i,100){
		mid=(l+r)/2;
		if (judge(mid)) l=mid;
		else r=mid;
	}
	printf("%.16lf",l);
}
/*
*/
