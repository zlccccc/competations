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
const LL maxn=300+7;
const double eps=0.00000001;
LL gcd(LL a,LL b){return b?gcd(b,a%b):a;}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a,T b){T ret=1;for (;b;b>>=1ll,a=a*a%M) if (b&1) ret=1ll*ret*a%M;return ret;}

map<int,int> MP;
int a[maxn];
LL dp[maxn][maxn];//dp[i][j]:0->i groups,linked_num
LL fac[maxn],inv[maxn];
inline LL C(int n,int m){if (n<m) return 0;return fac[n]*inv[m]%M*inv[n-m]%M;}
int tot;
int n,m;
int i,j,s,d;
int main(){
	fac[0]=1;
	FOR(i,1,300) fac[i]=fac[i-1]*i%M;
	inv[0]=inv[1]=1;
	FOR(i,2,300) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,300) inv[i]=inv[i]*inv[i-1]%M;
	scanf("%d",&n);
	REP(i,n){
		int val;
		scanf("%d",&val);
		for (j=2;j*j<=val;j++) while (val%(j*j)==0) val/=j*j;
		MP[val]++;
	}
	for (auto now:MP) a[m++]=now.second;
	dp[0][0]=1;
	REP(i,m){
		FOR(j,0,tot) if (dp[i][j]){
			FOR(s,1,a[i]){
				FOR(d,0,min(j,s)){
					dp[i+1][j-d+a[i]-s]=(dp[i+1][j-d+a[i]-s]+
						dp[i][j]*fac[a[i]]%M*C(a[i]-1,s-1)%M*C(j,d)%M*C(tot+1-j,s-d)%M)%M;
				}
			}
		}
		tot+=a[i];
	}
	printf("%I64d\n",dp[m][0]);
}
/*
*/
