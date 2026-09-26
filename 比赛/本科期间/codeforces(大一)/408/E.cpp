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
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,p,k,m;
int i,j,k1,k2;
bool a[1007],b[1007];
int dp[2][1007][51][51];//pos,maxn,p1,p2 
int ans,t;
int main()
{
	scanf("%d%d%d",&n,&p,&k);
	scanf("%d",&m);
	REP(i,m) scanf("%d",&j),a[j]=1;
	scanf("%d",&m);
	REP(i,m) scanf("%d",&j),b[j]=1;
	p=min(p,n/k*2+2);
	rFOR(i,1,n)
		FOR(j,0,p){
			FOR(k1,0,k)
				FOR(k2,0,k){
					t=dp[(i&1)^1][j][max(0,k1-1)][max(0,k2-1)]+((k1&&a[i])||(k2&&b[i]));
					if (j&&!k1) t=max(t,dp[i&1][j-1][k][k2]);
					if (j&&!k2) t=max(t,dp[i&1][j-1][k1][k]);
					dp[i&1][j][k1][k2]=t;
				}
		}
	printf("%d",dp[1][p][0][0]);
}
