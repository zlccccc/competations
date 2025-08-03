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
#include <cassert>
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
const double eps=0.000000001;
const double pi=acos(-1.0);
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j,pre,k;
LL a[maxn],b[maxn];
LL A[maxn],now,ans;//sum
int main(){
	int n;
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		FOR(i,1,n) scanf("%lld",&a[i]);
		sort(a+1,a+1+n);
		FOR(i,1,n) A[i]=A[i-1]+a[i];
		FOR(k,2,n){
			j=1;m=0;
			i=(n-1)%(k-1);
			if (i) b[++m]=ans=A[++i];
			else ans=0;
			while (i+j<n+m){
				pre=i;i+=k;//i(pre):selected,j:next to select
				now=0;
				while (j<=m&&(n<i||b[j]<a[i])) now=now+b[j],i--,j++;
				now+=A[i]-A[pre];
				b[++m]=now;
				ans+=now;
			}printf("%lld ",ans);
		}puts("");
	}
}
