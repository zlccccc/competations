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
#include <bitset>
#include <utility>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef unsigned long long ULL;
typedef unsigned long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=19260817;
const LL maxn=1007;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
inline LL poww(LL a,LL b){
	LL ret=1;
	for (;b;b>>=1,a=a*a%M)
		if (b&1) ret=ret*a%M;
	return ret;
}

int a[1007][1007];
int vx=1,vy=1;
int n,m;
int main(){
	int T;
	int i,j,x,y,ans;
	FOR(n,2,20) FOR(m,2,20){{
			FOR(i,1,n) FOR(j,1,m) a[i][j]=0;
			vx=vy=1;x=y=1;a[1][1]=1;
			while (1){
	//			printf("%d %d\n",x,y);
				x=x+vx;y=y+vy;
				a[x][y]++;
				if (x==1||x==n) vx=-vx;
				if (y==1||y==m) vy=-vy;
				if ((x==n&&y==m)||(x==1&&y==m)||(x==n&&y==1)||(x==1&&y==1)) break;
			}
			ans=0;
	//		FOR(i,1,n){
	//			FOR(j,1,m) printf("%d",a[i][j]);
	//			puts("");
	//		}
			FOR(i,1,n) FOR(j,1,m) if (a[i][j]==1) ans++;
			if (n<m) printf("n,m=%d %d,ans:%d\n",n,m,ans);
		}
	}
}
/*
*/
