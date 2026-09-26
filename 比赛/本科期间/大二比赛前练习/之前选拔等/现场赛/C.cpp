#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)
typedef long long LL;
typedef unsigned long long ULL;
const LL maxn=1e6+7;
const LL M=1e9+7;
const LL INF=0x3f3f3f3fll;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const double eps=0.000000001;
const double pi=acos(-1);
LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b){return a>0?a:-a;}

LL n;
LL a[maxn*2];
LL l[maxn*2],r[maxn*2];
LL ans;
void solve(){
	int i,j;
	scanf("%lld",&n);
	FOR(i,1,n) scanf("%lld",&a[i]);
	FOR(i,n+1,2*n) a[i]=a[i-n];
	j=1;
	FOR(i,2,n) if (a[i]>a[j]) j=i;
	FOR(i,1,n) a[i]=a[j-1+i];
	FOR(i,n+1,n*2) a[i]=a[i-n];
//	FOR(i,1,2*n) printf("%d ",a[i]);puts("");
	stack<LL> S,T;
	LL ans=0,cnt;
	FOR(i,1,n){
		while (S.size()&&a[S.top()]<a[i]){
//			printf("%d ",T.top());
			ans-=T.top()*(T.top()+1)/2;
			S.pop();T.pop();
		}
		cnt=0;
		while (S.size()&&a[S.top()]==a[i]) S.pop(),cnt+=T.top()+1,T.pop();
		if (S.size()) l[i]=S.top()+1;
		else l[i]=1;
		S.push(i);T.push(cnt);
	}
	while (S.size()){
//			printf("%d ",T.top());
			ans-=T.top()*(T.top()+1)/2; 
			S.pop();T.pop();
	}
	rFOR(i,1,2*n){
		while (S.size()&&a[S.top()]<=a[i]) S.pop();
		if (S.size()) r[i]=S.top()-1;
		else r[i]=i+n;
		S.push(i);
	}
//	puts("!!!");
//	FOR(i,1,n*2) printf("%d ",l[i]);puts("");
//	FOR(i,1,n*2) printf("%d ",r[i]);puts("");
	FOR(i,1,n) {
//		printf("%d ",r[i]-l[i]);
		ans+=min(r[i]-l[i],n-1);
	}
	printf("%lld\n",ans);
}
int T;
int main(){
	scanf("%d",&T);
	while (T--) solve();
}
/*
5
5
1 2 1 2 1
5
1 1 1 1 1
*/
