#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


LL n,m;
LL i,j,k,t; 
LL a[maxn],b[maxn],l,r,mid,ans;
bool judge(LL x){
	LL i,tot=0;
	FOR(i,1,n) b[i]=a[i]+i*x;
	sort(b+1,b+n+1);
	ans=0;
	FOR(i,1,x) ans+=b[i];
	return ans<=k;
}
int main(){
	scanf("%I64d%I64d",&n,&k);
	FOR(i,1,n) scanf("%I64d",&a[i]);
	l=0;r=n+1;ans=0;
	while (l+1<r){
		mid=(l+r)/2;
		if (judge(mid)) l=mid;
		else r=mid;
	}
	judge(l);
	printf("%I64d %I64d",l,ans);
}
/*
3 6
2 3 5
*/
