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
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}


int ans;
LL n,m,k;
int main(){
	scanf("%I64d",&n);
	if (n==0) ans++;
	while (n){
		k=n%16;
		if (k>=10) k=k-10+'A';
//		printf("%d ",n%16);
		if (k==0) ans++;
		if (k==4) ans++;
		if (k==6) ans++;
		if (k==8) ans+=2;
		if (k==9) ans++;
		if (k=='A') ans++;
		if (k=='B') ans+=2;
		if (k=='D') ans++;
		n/=16;
	}
	printf("%d",ans);
}
