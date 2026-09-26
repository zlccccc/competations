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

int i,j,k,n,t;
LL a[maxn];
LL ans;
int main(){
	int n,x,k;
	scanf("%d%d%d",&n,&x,&k);
	REP(i,n) scanf("%d",&a[i]);
	sort(a,a+n);
	REP(i,n){
		LL EDPOS=lower_bound(a,a+n,((a[i]-1)/x+k+1)*x)-a;
		LL STPOS=lower_bound(a,a+n,max(a[i],((a[i]-1)/x+k)*x))-a;
//		printf("%d->%d\n",((a[i]-1)/x+k)*x,((a[i]-1)/x+k+1)*x);
		ans+=EDPOS-STPOS;
	}printf("%I64d\n",ans);
}
/*
*/
