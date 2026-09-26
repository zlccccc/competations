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

double p[57][57];
double d[57][57][57];
int l[57];
double ans;
void solve(){
	int i,j,u,v,uu,vv;
	int n,m,k;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) FOR(j,1,n) scanf("%lf",&p[i][j]);
	scanf("%d",&k);
	FOR(i,1,n) scanf("%d",&l[i]);
	FOR(i,1,m) FOR(u,1,n) FOR(v,1,n) d[i][u][v]=0;
	d[1][1][1]=1;
	FOR(i,2,m){
		FOR(u,1,n) FOR(v,1,n) if (l[u]==l[v])
		FOR(uu,1,n) FOR(vv,1,n) if (l[uu]==l[vv])
		if (abs(l[u]-l[uu])<=2) d[i][uu][vv]+=d[i-1][u][v]*p[u][uu]*p[v][vv];
	}
	ans=0;
	FOR(u,1,n) FOR(v,1,n) if (l[u]==l[v]) ans+=d[m][u][v];
	printf("%.10lf\n",ans);
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}
/*
1
3 2
0.2 0.4 0.4
1 0 0
1 0 0
2
0 1 1
*/
