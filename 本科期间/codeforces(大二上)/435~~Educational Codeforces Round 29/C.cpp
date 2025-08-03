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

int A[5][5],B[5][5];
LL cnt1,cnt2,ans1,ans2;
int a,b,prea,preb;
LL n;
int main(){
	int i,j;
	scanf("%I64d%d%d",&n,&a,&b);
	FOR(i,1,3)
		FOR(j,1,3) scanf("%d",&A[i][j]);
	FOR(i,1,3)
		FOR(j,1,3) scanf("%d",&B[i][j]);
	FOR(i,1,10000){
		if (!n) break;
		n--;
		if (a==3&&b==2) ans1++;
		if (a==2&&b==1) ans1++;
		if (a==1&&b==3) ans1++;
		if (b==3&&a==2) ans2++;
		if (b==2&&a==1) ans2++;
		if (b==1&&a==3) ans2++;
		int a1=A[a][b],b1=B[a][b];a=a1,b=b1;
	}
	prea=a;preb=b;
	FOR(i,1,10000){
		if (a==3&&b==2) cnt1++;
		if (a==2&&b==1) cnt1++;
		if (a==1&&b==3) cnt1++;
		if (b==3&&a==2) cnt2++;
		if (b==2&&a==1) cnt2++;
		if (b==1&&a==3) cnt2++;
		int a1=A[a][b],b1=B[a][b];a=a1,b=b1;
		if (a==prea&&b==preb) break;
	}
	ans1+=(n/i)*cnt1;ans2+=(n/i)*cnt2;n%=i;
	FOR(i,1,10000){
		if (!n) break;
		n--;
		if (a==3&&b==2) ans1++;
		if (a==2&&b==1) ans1++;
		if (a==1&&b==3) ans1++;
		if (b==3&&a==2) ans2++;
		if (b==2&&a==1) ans2++;
		if (b==1&&a==3) ans2++;
		int a1=A[a][b],b1=B[a][b];a=a1,b=b1;
	}
	printf("%I64d %I64d",ans1,ans2);
}
/*
*/
