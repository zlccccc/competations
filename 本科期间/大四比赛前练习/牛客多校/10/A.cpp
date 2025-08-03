#include <sstream>
#include <fstream>
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
#include <bitset>
using namespace std;
#define REP(I,N) for (I=0;I<N;I++)
#define rREP(I,N) for (I=N-1;I>=0;I--)
#define rep(I,S,N) for (I=S;I<N;I++)
#define rrep(I,S,N) for (I=N-1;I>=S;I--)
#define FOR(I,S,N) for (I=S;I<=N;I++)
#define rFOR(I,S,N) for (I=N;I>=S;I--)

#define DEBUG
#ifdef DEBUG
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define deputs(str) fprintf(stderr, "%s\n",str)
#else
#define debug(...)
#define deputs(str)
#endif // DEBUG
typedef unsigned long long ULL;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long long LL;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=1e9+7;
const LL maxn=1e5+107;
const double pi=acos(-1.0);
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

int A[507];
double dp[507][1007],ini[507][1007];
int main(){
	int n,a,b,_,i,j;
	scanf("%d%d%d",&n,&a,&b);
	FOR(i,1,n) scanf("%d",&A[i]);
	// sort(A+1,A+1+n,[&](int i,int j){
	// 	return i>j;
	// }); //no use
	dp[0][0]=1;
	double ans=0;
	FOR(_,1,n) {//pos
		int k=A[_];
		rFOR(i,0,_-1) {//背包
			FOR(j,0,a) {
				// printf("j=%d; i=%d\n",j,i);
				if (i==0) dp[i+1][j+k]+=dp[i][j]/(n-i);
				else dp[i+1][j+k]+=dp[i][j]*i/(n-i);
			}
		}
		rFOR(i,1,_) FOR(j,a+1,b) {//this is last
			dp[i][j]=0;
		}
	}
	FOR(i,0,n) //remove
		FOR(j,0,a+b) ini[i][j]=dp[i][j];
	FOR(_,1,n) {//pos
		FOR(i,0,n) //remove
			FOR(j,0,a+b) dp[i][j]=ini[i][j];
		int k=A[_],i,j;
		FOR(i,0,n-1) {//remove
			FOR(j,0,a) {//remove_this
				// printf("j=%d; i=%d\n",j,i);
				if (i==0) dp[i+1][j+k]-=dp[i][j]/(n-i);
				else dp[i+1][j+k]-=dp[i][j]*i/(n-i);
			}
		}
		rFOR(i,1,n) FOR(j,a+1,b) {//this is last
			dp[i][j]=0;
		}
		// FOR(i,0,n-1) {//remove
		// 	FOR(j,0,a+b) printf("%f ",dp[i][j]); puts("");
		// } puts("");
		// printf("%d:\n",_);
		// FOR(i,0,n-1) {//remove
		// 	FOR(j,0,a+b) printf("%f ",dp[i][j]); puts("");
		// } puts("");
		rFOR(i,0,n-1) {//背包
			FOR(j,0,a) {
				// printf("j=%d; i=%d\n",j,i);
				if (i==0) dp[i+1][j+k]+=dp[i][j]/(n-i);
				else dp[i+1][j+k]+=dp[i][j]*i/(n-i);
			}
		}
		FOR(i,1,n) FOR(j,a+1,b) {//this is last
			// if (abs(dp[i][j])>eps){
			// 	printf("_=%d; %d %d; %f\n",_,i,j,(double)dp[i][j]);
			// }
			ans+=dp[i][j];
		}
	}
	printf("%.10f\n",(double)ans);
}
/*
5 1 2
1 1 1 1 1
*/