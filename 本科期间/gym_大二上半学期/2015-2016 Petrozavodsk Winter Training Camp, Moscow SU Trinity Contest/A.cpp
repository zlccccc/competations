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
const double eps=2e-3;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}
//完蛋了。。没板子 
int n,m,i,j,k;
long double a[207][207];
int ans;
int main(){
	scanf("%d%d",&n,&m);
	REP(i,n) REP(j,m) cin>>a[i][j];
	REP(i,n){
		int now=i,mark=-1;
		while (now<m&&mark==-1){
			rep(j,i,n) if (abs(a[j][now])>eps) mark=j;
			if (mark==-1) now++;
		}if (now==m) break;
		rep(k,now,m) swap(a[i][k],a[mark][k]);
		int ii,jj;
//		REP(ii,n) {REP(jj,m) cout<<a[ii][jj]<<" ";puts("");}puts("");
		rep(j,i+1,n){
			rrep(k,now,m) a[j][k]-=a[i][k]*a[j][now]/a[i][now];
		}ans++;
//		int ii,jj;
//		REP(ii,n) {REP(jj,m) cout<<a[ii][jj]<<" ";puts("");}puts("");
	}
	printf("%d",ans);
}
/*
3 3
2 0 -2
0 -2 0
-2 0 2
*/
