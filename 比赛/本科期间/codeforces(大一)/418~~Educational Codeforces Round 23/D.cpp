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
const LL maxn=1e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


LL n,s;
LL i,j,k;
LL ans;
LL a[maxn];
LL le[maxn],ri[maxn];
stack<LL> S;
int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&a[i]);
	while (S.size()) S.pop();
	FOR(i,1,n){
		while (S.size()&&a[S.top()]<a[i]){
			ri[S.top()]=i-1;
			S.pop();
		}
		S.push(i);
	}
	while (S.size()) {ri[S.top()]=n;S.pop();}
	rFOR(i,1,n){
		while (S.size()&&a[S.top()]<=a[i]){
			le[S.top()]=i+1;
			S.pop();
		}
		S.push(i);
	}
	while (S.size()) {le[S.top()]=1;S.pop();}
	FOR(i,1,n) ans+=((i-le[i]+1)*(ri[i]-i+1))*a[i];
	
	FOR(i,1,n){
		while (S.size()&&a[S.top()]>a[i]){
			ri[S.top()]=i-1;
			S.pop();
		}
		S.push(i);
	}
	while (S.size()) {ri[S.top()]=n;S.pop();}
	rFOR(i,1,n){
		while (S.size()&&a[S.top()]>=a[i]){
			le[S.top()]=i+1;
			S.pop();
		}
		S.push(i);
	}
	while (S.size()) {le[S.top()]=1;S.pop();}
	FOR(i,1,n) ans-=((i-le[i]+1)*(ri[i]-i+1))*a[i];
	printf("%I64d",ans);
}
/*
*/
