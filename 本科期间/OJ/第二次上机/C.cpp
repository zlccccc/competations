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
const LL maxn=1e3+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int n,m,i,j; 
LL a[maxn][maxn],pos[maxn];
LL now,MAX=0,MIN=INFF,ans,cnt;
int main(){
	while (~scanf("%d%d",&n,&m)){
		MAX=0,MIN=INFF;
		FOR(i,1,n){
			pos[i]=1;
			FOR(j,1,m){
				scanf("%lld",&a[i][j]);
				a[i][j]+=a[i][j-1];
				MAX=max(MAX,a[i][j]);
				if (a[i][j]) MIN=min(MIN,a[i][j]);
			}
		}
		ans=n;now=MIN;
		while (now!=MAX){
			cnt=0;MIN=MAX;
			FOR(i,1,n){
				while(pos[i]<=m&&a[i][pos[i]]<now) pos[i]++;
				if (pos[i]<=m&&now==a[i][pos[i]]) cnt++;
				else if (pos[i]<=m) MIN=min(MIN,a[i][pos[i]]);
			}
//			printf("%d %d %d\n",now,cnt,MIN);
			now=MIN;
			ans=min(ans,n-cnt);
		}
		printf("%d\n",ans);
	}
}
/*
*/
