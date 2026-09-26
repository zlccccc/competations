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
const LL maxn=2e6+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

LL n,m,i,j;
LL cnt[maxn],sum[maxn];
bool mark[maxn];
LL ans;
const int MAX=1e6;
int main(){//(j+i-f)*y>x ==> j+i-f>x/y µÄÓÃx //f<j+i-x/y
	LL x,y;
	while (~scanf("%lld%lld%lld",&n,&x,&y)){
		FOR(i,1,MAX*2) cnt[i]=sum[i]=0;
		LL val;
		FOR(i,1,n) scanf("%lld",&val),cnt[val]++,sum[val]+=val;
		FOR(i,1,MAX*2) cnt[i]+=cnt[i-1],sum[i]+=sum[i-1];
//		FOR(i,1,20) printf("%3d ",i);puts("");
//		FOR(i,1,20) printf("%3d ",cnt[i]);puts("");
//		FOR(i,1,20) printf("%3d ",sum[i]);puts("");
		ans=INFF;
		FOR(i,2,MAX){
			if (mark[i]) continue;
			LL now=0;
			LL t=max(0ll,i-1-x/y);
			for (j=0;j<=MAX;j+=i){
				mark[j]=1;
				now+=((cnt[j+i-1]-cnt[j+t])*(j+i)-(sum[j+i-1]-sum[j+t]))*y+(cnt[j+t]-cnt[j])*x;
//				printf("now+==%d %d %d;%d\n",j,j+t,j+i-1,now);
			}
//			printf("i=%d %d t=%d\n",i,now,t);
			mark[i]=0;
			ans=min(ans,now);
		}
		printf("%lld\n",ans);
	}
}
/*
*/
