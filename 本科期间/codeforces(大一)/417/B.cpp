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
const LL maxn=1007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


LL n,m;
LL i,j,k; 
char a[maxn][maxn];
LL t[maxn][3];
LL ans1,ans2;
int main(){
	scanf("%d%d",&n,&m);
	rFOR(i,1,n) scanf("%s",&a[i]);
	t[0][0]=0;t[0][1]=INF;
	FOR(i,1,n){
		t[i][0]=t[i-1][1]+m+1;
		t[i][1]=t[i-1][0]+m+1;
		k=0;
		FOR(j,0,m+1) if (a[i][j]=='1') {k=j;ans1=k+t[i-1][0];}
		t[i][0]=min(t[i][0],t[i-1][0]+k*2);
//		printf("k=%d   \n",k);
		rFOR(j,0,m+1) if (a[i][j]=='1') {k=m-j+1;ans2=k+t[i-1][1];}
		t[i][1]=min(t[i][1],t[i-1][1]+k*2);
//		printf("k=%d   \n",k);
		t[i][0]++;t[i][1]++;
//		printf("lr==%d %d\n",t[i][0],t[i][1]);
//		printf("%d %d\n",ans1,ans2);
	}
	printf("%I64d",min(ans1,ans2));
}
/*
*/
