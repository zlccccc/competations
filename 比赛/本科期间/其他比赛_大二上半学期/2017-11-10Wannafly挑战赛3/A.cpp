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
const LL M=998244353;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m;
int i,j,k,t;
int val;
double p[maxn];
int a[maxn];
int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&a[i]);
	reverse(a+1,a+n+1);
	FOR(i,1,n) a[i]+=a[i-1];
	FOR(j,1,m){
		int x;
		scanf("%d",&x);
		int pre=0;
		FOR(i,1,n){
			while (a[i]-a[pre]>x) pre++;
			if (i==pre) break;
//			printf("%d %d\n",i,pre);
			p[i]=(p[i-1]-p[pre-1])/(i-pre)+1;
			if (i!=n) p[i]+=p[i-1];
		}
//		FOR(i,1,n) printf("%.2lf ",p[i]);puts("");
		if (i<=n) puts("YNOI is good OI!");
		else printf("%.2lf\n",p[n]);
	} 
}
/*
*/
