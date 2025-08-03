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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


int n,m;
int i,j,k;
int a[107][107];
int b[107][107];
int ans1[maxn];
int ans2[maxn];
int mark,tot,mm;
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n)
		FOR(j,1,m) scanf("%d",&a[i][j]);
	if (n>m){
		mm=1;
		FOR(i,1,n)
			FOR(j,1,m) b[i][j]=a[i][j];
		FOR(i,1,n)
			FOR(j,1,m) a[j][i]=b[i][j];
		swap(n,m);
	}
	FOR(i,1,n){
		mark=INF;
		while (mark){
			mark=INF;
			FOR(j,1,m) mark=min(mark,a[i][j]);
			if (mark){
				FOR(j,1,m) a[i][j]-=mark;
				while (mark--) ans1[tot]=1,ans2[tot]=i,tot++;//1=row
			}
		}
	}
	FOR(j,1,m){
		mark=INF;
		while (mark){
			mark=INF;
			FOR(i,1,n) mark=min(mark,a[i][j]);
			if (mark){
				FOR(i,1,n) a[i][j]-=mark;
				while (mark--) ans1[tot]=2,ans2[tot]=j,tot++;//1=row
			}
		}
	}
	FOR(i,1,n)
		FOR(j,1,m) if (a[i][j]) return 0*puts("-1");
	printf("%d\n",tot);
	REP(i,tot){
		if (ans1[i]==1&&mm==0||ans1[i]==2&&mm==1) printf("row %d\n",ans2[i]);
		if (ans1[i]==2&&mm==0||ans1[i]==1&&mm==1) printf("col %d\n",ans2[i]);
	}
}
/*
*/
