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
const LL maxn=2000+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

int m;
double now[107],pre[107];
double C[107][107],P[107];
int main(){
	int T,i,j,t,k,n,m;
	FOR(i,0,100) C[0][i]=1;
	FOR(i,1,100) FOR(j,1,i) C[j][i]=C[j-1][i-1]+C[j][i-1];
	P[0]=1;
	FOR(i,1,100) P[i]=P[i-1]*2;
//	printf("%lf %lf\n",C[2][5],P[3]);
	scanf("%d",&T);
	while (T--){
		scanf("%d%d%d",&n,&m,&k);
		now[0]=1;FOR(i,1,n) now[i]=0;
		FOR(t,0,m-1){
			FOR(i,0,n) pre[i]=now[i],now[i]=0;
			FOR(i,0,n){
				if (pre[i]<eps) continue;
				if (i+k<=n){
					FOR(j,0,k) now[i+j]+=pre[i]*C[j][k]/P[k];
				}else{
					FOR(j,n-k,n) now[j]+=pre[i]*C[n-j][k]/P[k];
				}
			}
//			FOR(i,0,n) printf("%lf ",now[i]);puts("");
		}
		double ans=0;
		FOR(i,0,n) ans+=now[i]*i;
		printf("%.3lf\n",ans);
	}
}
/*
*/
