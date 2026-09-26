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
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a*=a) ret=1ll*ret*a%M;return ret;}


set<LL> S;
LL n;
LL a[maxn];
LL i,t,sum;
bool mark;
int main(){
	scanf("%I64d",&n);
	FOR(i,1,n) scanf("%I64d",&a[i]),t+=a[i];
	if (t&1) return 0*puts("NO");
	t/=2;
	S.clear();sum=0;
	FOR(i,1,n){
		S.insert(a[i]);
		sum+=a[i];
		if (sum==t) mark=1;
		if (sum-t>0&&S.count(sum-t)) mark=1;
	}
	S.clear();sum=0;
	rFOR(i,1,n){
		S.insert(a[i]);
		sum+=a[i];
		if (sum==t) mark=1;
		if (sum-t>0&&S.count(sum-t)) mark=1;
	}
	if (mark) puts("YES");
	else puts("NO");
}
