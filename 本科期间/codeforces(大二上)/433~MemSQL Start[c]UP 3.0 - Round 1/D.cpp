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

double P[107][107],have[10][107],ans[10][107];
void dfs(int l,int r,int n){
	if (l==r) {have[n][l]=1;return;}
	int mid=(l+r)/2;
	dfs(l,mid,n-1);
	dfs(mid+1,r,n-1);
	int i,j;
	FOR(i,l,mid) FOR(j,mid+1,r){
		have[n][i]+=have[n-1][i]*have[n-1][j]*P[i][j];
		have[n][j]+=have[n-1][i]*have[n-1][j]*P[j][i];
	}
	FOR(i,l,mid) FOR(j,mid+1,r){
		ans[n][i]=max(ans[n][i],ans[n-1][i]+ans[n-1][j]+have[n][i]*(1<<(n-1)));
		ans[n][j]=max(ans[n][j],ans[n-1][i]+ans[n-1][j]+have[n][j]*(1<<(n-1)));
	}
}
double ANS;
int main(){
	int n,i,j;
	scanf("%d",&n);
	FOR(i,1,1<<n)
		FOR(j,1,1<<n) scanf("%lf",&P[i][j]),P[i][j]*=0.01;
	dfs(1,1<<n,n);
	FOR(i,1,1<<n) ANS=max(ANS,ans[n][i]);
	printf("%.18lf\n",ANS);
}
/*
*/
