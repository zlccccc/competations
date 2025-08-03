#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <stack>
#include <queue>
#include <cmath>
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
const LL maxn=3e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}

int n,m;
int ans,i,t;
int a[maxn];
int pos,k;
int main()
{
	scanf("%d",&n);
	REP(i,n) scanf("%lld",&a[i]);
	t=a[0];
	REP(i,n) t=gcd(t,a[i]);
	if (t>1){
		puts("YES");
		printf("0");
		return 0;
	}
	k=0;
	REP(i,n){
		if (a[i]&1){
			if (a[i+1]&1) ans++,i++;
			else ans+=2;
		}
	}
	if (k) puts("NO");
	else {
		puts("YES");
		printf("%d",ans);
	}
}
