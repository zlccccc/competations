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
#include <cassert>
#include <iomanip>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
#define dbg(x) cout <<#x<<" = "<<x<<" ;  "
#define dbgln(x) cout <<#x<<" = "<<x<<endl
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL Mod=1e9+7;
const LL maxn=1000+7;
const double eps=0.000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%Mod)
		if (b&1) ret=(LL)ret*a%Mod;
	return ret;
}

int T;
int OK[1000007];
int okay[1000007];
double pre[1000007];
double now[1000007];
int solve(){
	static int x=0;
	int i,j;
	int n,p;
	int MAX=0;
	OK[0]=1;
	scanf("%d%d",&n,&p);
	while (n--){
		int w,h;
		int u=0;double v;
		scanf("%d%d",&w,&h);
		u=w+w+h+h;
		FOR(j,0,MAX) if (OK[j]){
			MAX=max(MAX,j+u);
			okay[j+u]=1;
			now[j+u]=max(now[j+u],pre[j]);
		}
		v=2*sqrt(w*w+h*h)-min(2*w,2*h);
		u=w+w+h+h+min(2*w,2*h);
		FOR(j,0,MAX) if (OK[j]){
			MAX=max(MAX,j+u);
			okay[j+u]=1;
			now[j+u]=max(now[j+u],pre[j]+v);
		}
		FOR(j,0,MAX){
			pre[j]=now[j],OK[j]=okay[j];
			now[j]=0;okay[j]=0;
		}
	}double ans=0;
	FOR(i,0,MAX) if (OK[i]){
		// printf("%d : %f\n",i,pre[i]);
		if (i<=p&&ans<=i) ans=i;
		if (i+pre[i]<=p+eps&&ans<=i+pre[i]) ans=i+pre[i];
		if (i<=p&&p<=i+pre[i]+eps) ans=p;
	}
	printf("Case #%d: %.10f\n",++x,ans-eps);
	FOR(i,0,MAX) OK[i]=0,pre[i]=0,okay[i]=0,now[i]=0;
	return 0;
}
int main() {
	int T;
	scanf("%d",&T);
	while (T--) solve();
	return 0;
}
/*
10
1 7
1 1
2 920
50 120
50 120
1 32
7 4
3 240
10 20
20 30
30 10
1 24
3 4
1 6
1 1
*/
