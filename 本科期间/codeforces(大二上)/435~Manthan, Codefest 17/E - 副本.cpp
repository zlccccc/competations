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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

LL m,val,k;
vector<int> edge[maxn];
LL dp[10][1024][70],DP[1024][70];
int n;
int a[70];
int cnt;
LL solve(LL k,LL x){
	cnt=0;
	while (x){
		a[++cnt]=x%k;
		x/=k;
	}
	LL ret=0;
	int i;
	FOR(i,1,cnt-1)  ret+=dp[k][0][i];
	FOR(i,0,(1<<(cnt+1))-1) DP[i][cnt+1]=0;
	DP[0][cnt+1]=1;
	rFOR(i,1,cnt){
		
		FOR(i,0,(1<<i)-1) dp[i]
	}
	
	return ret;
}
int main(){
	int i,j,k,t;
	dp[0][0]=1;
	FOR(t,1,70){
		FOR(k,2,10){
			rFOR(i,0,(1<<k)-1){
				FOR(j,0,k-1) dp[k][i^(1<<j)][t]+=dp[k][i][t-1];
			}
		}
	}
	int T;
	scanf("%d",&T);
	while (T--) {
		scanf("%d%I64d%I64d",&k,&l,&r);
		printf("%I64d\n",solve(k,r)-solve(k,l-1));
	}
}
/*
1 1
1 0
*/
