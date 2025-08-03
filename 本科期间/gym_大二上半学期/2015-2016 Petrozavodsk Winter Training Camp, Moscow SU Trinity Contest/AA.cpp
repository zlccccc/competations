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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//完蛋了。。没板子 
int n,m,i,j,k;
int  a[207][207];
int ans;
int main(){
	scanf("%d%d",&n,&m);
	REP(i,n) REP(j,m) scanf("%d",&a[i][j]);
	REP(i,n){
		int now=i,mark=1;
		while (now<m&&mark){
			rep(j,i,n) if (a[j][now]) mark=0;
			now+=mark;
		}if (now==m) break;
		rep(j,i+1,n){
			int x=i,y=j;
			if (a[x][now]<0) rep(k,now,m) a[x][k]=-a[x][k];
			if (a[y][now]<0) rep(k,now,m) a[y][k]=-a[y][k];
			while (a[y][now]){
				int t=a[x][now]/a[y][now];//负数消不掉... 
				rep(k,now,m) a[x][k]-=a[y][k]*t;
				swap(x,y);
			}if (x!=i){
				rep(k,now,m) swap(a[i][k],a[x][k]);
			}
		}ans++;
	}
	printf("%d",ans);
}
/*
3 3
2 0 -2
0 -2 0
-2 0 2
*/
