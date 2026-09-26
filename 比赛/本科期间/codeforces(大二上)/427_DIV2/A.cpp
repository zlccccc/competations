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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int X[maxn],Y[maxn],S[maxn];
int sum[17][107][107];
int main(){
	int n,q,c;
	int i,j,k;
	scanf("%d%d%d",&n,&q,&c);
	REP(i,n) scanf("%d%d%d",&X[i],&Y[i],&S[i]);
	FOR(k,0,10){
		REP(i,n) sum[k][X[i]][Y[i]]+=S[i];
		FOR(i,1,100)FOR(j,1,100)
			sum[k][i][j]=sum[k][i][j]+sum[k][i-1][j]+sum[k][i][j-1]-sum[k][i-1][j-1];
		REP(i,n)
			if (S[i]+1<=c) S[i]++;
			else S[i]=0;
	}
	REP(i,q){
		int t,x1,x2,y1,y2;
		scanf("%d%d%d%d%d",&t,&x1,&y1,&x2,&y2);
		t%=c+1;
		printf("%d\n",sum[t][x2][y2]-sum[t][x1-1][y2]-sum[t][x2][y1-1]+sum[t][x1-1][y1-1]);
	}
}
/*
*/
