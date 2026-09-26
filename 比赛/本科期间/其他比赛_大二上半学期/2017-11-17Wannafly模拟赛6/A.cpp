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

int n;
int i,j,k;
int val;
LL ans,t;
int a[maxn];
int main(){
	scanf("%d%lld",&n,&t);
	FOR(i,1,n){
		LL x,y,z;
		LL l,r,mid,now=0;
		scanf("%lld%lld%lld",&x,&y,&z);
		l=0;r=t+1;if (z) r=t/z+1;
		while(l+1<r){
			mid=(l+r)/2;
			if (mid*(x+y)+mid*(mid-1)/2*z<=t) l=mid;
			else r=mid;
		}now+=y*l+l*(l-1)/2*z;
		now+=max(0ll,t-((x+y)*l+l*(l-1)/2*z)-x);
//		printf("%lld\n",now);
		ans+=now;
	}
	printf("%lld\n",ans);
}
/*
*/
