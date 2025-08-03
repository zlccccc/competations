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

int n,m,i,j; 
int a[maxn],b[maxn],val;
int main(){
	while (~scanf("%d",&n)){
		REP(i,n) scanf("%d",&a[i]);
		REP(i,n) scanf("%d",&b[i]);
		scanf("%d",&val);
		sort(a,a+n);
		sort(b,b+n);
		bool mark=0;
		REP(i,n){
			int pos=lower_bound(b,b+n,val-a[i])-b;
			if (pos<n&&b[pos]+a[i]==val&&a[i]!=a[i+1]){
				printf("%d %d\n",a[i],b[pos]);
				mark=1;
			}
		}
		if (!mark) puts("OTZ");
		puts("");
	}
}
/*
*/
