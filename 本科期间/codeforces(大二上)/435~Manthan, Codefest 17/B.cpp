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

LL a[maxn],ans,p,q,r;
int n,m,i;
LL ans1,ans2,ans3;
int main(){
	scanf("%d%I64d%I64d%I64d",&n,&p,&q,&r);
	ans1=-INFF,ans2=-INFF,ans3=-INFF;
	FOR(i,1,n){
		scanf("%I64d",&a[i]);
		ans1=max(ans1,p*a[i]);
		ans2=max(ans2,ans1+q*a[i]);
		ans3=max(ans3,ans2+r*a[i]);
	}
	printf("%I64d\n",ans3);
}
/*
1 1000000000 1000000000 1000000000
-1000000000 
*/
