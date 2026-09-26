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
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j,k;
LL a[maxn],b[maxn],c[maxn];
int cnt;
double ans;
int main(){
	while (~scanf("%d%d",&n,&m)){
		cnt=n+m;
		FOR(i,1,n) scanf("%lld",&a[i]);
		FOR(i,1,m) scanf("%lld",&b[i]);
		i=j=1;
		FOR(k,1,cnt){
			if (j>m||(i<=n&&a[i]<b[j])) c[k]=a[i++];
			else c[k]=b[j++];
		}
//		FOR(k,1,cnt) printf("%d ",c[k]);puts("");
		ans=0;
		if (cnt!=0){
			if (cnt&1) ans=c[cnt/2+1];
			else ans=(.0+c[cnt/2]+c[cnt/2+1])/2;
		}
		printf("%.1lf\n",ans);
	}
}
/*
1 1
13465128645621
561328465789987
*/
