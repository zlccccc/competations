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
const LL maxn=5000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}
inline LL powMM(LL a,LL b){
	LL ret=1;
	while (b){
		if (b&1) ret=ret*a%M;
		a=a*a%M;
		b>>=1;
	}
	return ret;
}
int n,m;
char a[maxn];
char b[maxn];
int dp[maxn];
int ans;
int i,j,k;
int s,t;
int main()
{
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d",&m);
		scanf("%s",a+1); 
		n=strlen(a+1);
		FOR(i,1,n) b[n+1-i]=a[i];
		ans=0;
		i=1;
		FOR(j,1,n){
			dp[0]=0;
			s=t=0;
			for (t=1;j+t<=n&&i+t<=n;t++){//len
				dp[t]=dp[t-1]+abs(a[i+t-1]-b[j+t-1]);
				while (s<t&&((!(i+j+s*2-2>=n||n>=i+j+t*2-2))||dp[t]-dp[s]>m)) s++;
//				printf("s,t=%d %d  %d-%d %d-%d,dp=%d %d\n",s,t,i+s,j+s,i+t,j+t,dp[s],dp[t]);
				ans=max(ans,t-s);
			}
			dp[0]=0;
			s=t=0;
			for (t=1;j+t<=n&&i+t<=n;t++){//len
				dp[t]=dp[t-1]+abs(a[j+t-1]-b[i+t-1]);
				while (s<t&&((!(i+j+s*2-2>=n||n>=i+j+t*2-2))||dp[t]-dp[s]>m)) s++;
//				printf("s,t=%d %d  %d-%d %d-%d,dp=%d %d\n",s,t,i+s,j+s,i+t,j+t,dp[s],dp[t]);
				ans=max(ans,t-s);
			}
//			FOR(k,0,t) printf("%d ",dp[k]);puts("");
		}
		printf("%d\n",ans);
	}
}
/*
*/
