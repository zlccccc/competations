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
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int a[maxn],ans;
int check(int x){
	int i;
	FOR(i,1,200) if (a[i]&&a[i]!=(i-1+x)/x) return 0; 
	return 1;
}
int main(){
	int n,k,ans=0,i,t;
	scanf("%d%d",&n,&k);
	REP(i,k) scanf("%d",&t),scanf("%d",&a[t]);
	FOR(i,1,200){
		if (check(i)){
			if (!ans) ans=(n-1+i)/i;
			else if (ans!=(n-1+i)/i)
				return 0*puts("-1");
		}
	}
	printf("%d\n",ans);
}
/*
*/
