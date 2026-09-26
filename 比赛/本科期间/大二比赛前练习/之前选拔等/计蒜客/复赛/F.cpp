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
#define rep(I,pos,N) for (I=pos;I<N;I++)
#define rrep(I,pos,N) for (I=N-1;I>=pos;I--)
#define FOR(I,pos,N) for (I=pos;I<=N;I++)
#define rFOR(I,pos,N) for (I=N;I>=pos;I--)
typedef unsigned long long ULL;
typedef long long LL;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) ret=1ll*ret*a%M;return ret;}


int n,m;
int i,j,k,t;
LL dp[(1<<19)+7][20];//Âú×ã...´ÎÊý 
bool mark[20];
int a[20],l;
LL ans,num[20];
int now;
int main(){
	scanf("%d%d",&n,&m);
	REP(i,n) scanf("%d",&a[i]);
	dp[0][0]=1;
	FOR(i,0,(1<<n)-1){
//		printf("i=%d ",i);
		REP(j,n) if ((i&(1<<j))==0){
//			printf("%d %d  ",j,i&(1<<j));
			now=a[j];t=0;
			rep(k,j,n){
				if (i&(1<<k)) continue;
				now=gcd(now,a[k]);
				t|=1<<k;
//				printf("t=%d ",t);
				if (now>=m)
					FOR(l,1,n) dp[i|t][l]=(dp[i|t][l]+dp[i][l-1])%M;
				else break;
			}
		}
//		puts("");
	}
	FOR(i,1,n) ans=(ans+dp[(1<<n)-1][i]*i)%M;
	printf("%lld",ans);
}
/*
18 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
*/
