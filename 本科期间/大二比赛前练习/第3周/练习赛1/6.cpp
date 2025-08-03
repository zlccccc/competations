#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rep(I,S,N) for (I=S;I<N;I++)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const LL M=1e9+7;
const LL maxn=3e5+7;
const double eps=0.00000001;
const LL INF=0x3f3f3f3f;
const LL INFF=0x1f3f3f3f3f3f3f3fll;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
inline LL min(LL a,LL b) {return a>b?b:a;}
inline LL max(LL a,LL b) {return a<b?b:a;}
inline LL abs(LL a,LL b) {return a>0?a:-a;}
inline double abs(double a) {return a>0?a:-a;}
inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}
int n,m,T;
int i,j;
int f[207][207];
char s[207],a[207];
int ans;
int main(){
	scanf("%d",&T);
	while (T--){
		scanf("%s%s",s+1,a+1);
		n=strlen(s+1);
		m=strlen(a+1);
		int x,y;
		FOR(x,0,n){
			f[0][0]=0;
			FOR(y,1,m) f[x][y]=-3*y-4;
		}
		FOR(x,1,n){
			FOR(y,1,m){
				FOR(i,0,x-1){
					FOR(j,0,y-1){
						int now;
						if (s[x]==a[y]) now=f[i][j]-3*(x-i-1)-3*(y-j-1)+8;
						else now=f[i][j]-3*(x-i-1)-3*(y-j-1)-5;
						if (i!=x-1) now-=4;
						if (j!=y-1) now-=4;
						f[x][y]=max(f[x][y],now);
					}
				}
			}
		}
		ans=-INF;
		FOR(i,0,n) ans=max(ans,f[i][m]);
		FOR(i,1,m) ans=max(ans,f[n][i]-3*(m-i)-4);
		printf("%d\n",ans);
	}
}
/*
2
acc abbc
*/ 
