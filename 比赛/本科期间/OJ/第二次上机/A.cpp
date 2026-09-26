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
const LL maxn=2e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i; 
int pos[maxn];
LL a[maxn],r[maxn],b[maxn],c[maxn];
LL ans;
int main(){
	while (~scanf("%d",&n)){
		REP(i,n) scanf("%lld%lld",&a[i],&r[i]),b[i]=a[i]-r[i],c[i]=a[i]+r[i];
		sort(c,c+n);
		sort(b,b+n);
		ans=0;
		REP(i,n){//大于等于到小于等于 
			int now=n,pos1,pos2;
			pos1=upper_bound(b,b+n,a[i]+r[i])-b;
			if (pos1&&b[pos1-1]<=a[i]+r[i]) pos1--;
			now-=pos1;
			pos2=lower_bound(c,c+n,a[i]-r[i])-c;
			now+=pos2;
			ans+=now-1;
//			printf("%d %d-%d %d\n",ans,pos2,pos1,now);
		}
		printf("%lld\n",ans/2);
	}
}
/*
upper_bound->lower_bound
*/
