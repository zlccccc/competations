#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3f;
const LL M=1e9+7;
const LL N=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>
inline T abs(T a,T b) {return a>0?a:-a;}
//g(n)=n,f(n)=phi(n)
LL n,k;
LL i;
LL phi(LL n){
	LL ans=n,i;
	for (i=2;i*i<=n;i++)
		if (!(n%i)){
			while (!(n%i)) n/=i;
			ans=ans/i*(i-1);
		}
	if (n>1) ans=ans/n*(n-1);
	return ans;
}
int main(){
	cin>>n>>k;
	k=(k+1)/2;
	REP(i,k){
		n=phi(n);
		if (n==1) break;
	}
	cout<<n%M;
}
/*
549755813888 2

*/
