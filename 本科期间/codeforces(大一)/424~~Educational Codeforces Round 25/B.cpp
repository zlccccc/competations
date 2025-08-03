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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}

LL n,m;
LL i,j,k;
LL cnt,ans;
char a[11][11];
bool judge(){
	int i,j;
	int jj,ii;
	REP(i,10)
		REP(j,10){
			REP(ii,2)
				REP(jj,2) if (ii!=0||jj!=0)
				if (a[i][j]=='X'&&
					a[i+ii][j+jj]=='X'&&
					a[i+ii*2][j+jj*2]=='X'&&
					a[i+ii*3][j+jj*3]=='X'&&
					a[i+ii*4][j+jj*4]=='X') return 1;
	}
	rREP(i,10)
		rREP(j,10){
			if (i+4>=0&&j-4>=0)
				if (a[i][j]=='X'&&
					a[i+1][j-1]=='X'&&
					a[i+1*2][j-1*2]=='X'&&
					a[i+1*3][j-1*3]=='X'&&
					a[i+1*4][j-1*4]=='X') return 1;
	}
	return 0;
}
int main(){
	scanf("%d",&n);
	REP(i,10) scanf("%s",a[i]);
	REP(i,10)
		REP(j,10){
			if (a[i][j]=='.'){
				a[i][j]='X';
				if (judge()) return 0*puts("YES");
				a[i][j]='.';
			}
		}
	return 0*puts("NO");
}
/*
....X.....
...X......
..........
.X........
X.........
..........
..........
..........
..........
......OOOO
*/
