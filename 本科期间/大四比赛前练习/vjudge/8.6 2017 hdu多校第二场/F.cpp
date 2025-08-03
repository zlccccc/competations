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
const LL M=998244353;
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

// int A[maxn];
ll base[107][107];//base
ll inv[10007],fac[10007];
ll C(int n,int m) {
	return fac[n]*inv[m]%M*inv[n-m]%M;
}
void calculatebase(int n,int A) {
	int i,j,k;
	FOR(i,1,n) FOR(j,1,n) base[i][j]=0;
	rFOR(i,1,n) {//C(n->i)
		base[i][i]=1;
		FOR(j,i+1,n) {
			FOR(k,1,n) { //C(j,i)
				base[i][k]-=base[j][k]*C(j,i);
			}
		}
	}
	FOR(A,1,n) {
		printf("%-2d : ",A);
		FOR(i,1,n) printf("%-4lld ",base[A][i]); puts("<-base");
	}
}
int pw2[10000007];
int Cn[3007],Cm[3007];
int main() {
	int i,j;
	fac[0]=1;
	FOR(i,1,10000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,10000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,10000) inv[i]=inv[i]*inv[i-1]%M;
	pw2[0]=1;
	FOR(i,1,3000*3000) {pw2[i]=pw2[i-1]; add_(pw2[i],pw2[i-1]);}
	// printf("%lld\n",C(10,2));
	int n,m,a,b;
	while (~scanf("%d%d%d%d",&n,&m,&a,&b)) {
		// calculatebase(n,a);
		// calculatebase(m,b);
		ll base1=1;
		int ans=0;
		// startTimer();
		FOR(i,a,n) Cn[i]=C(i-1,a-1)*C(n,i)%M;
		FOR(j,b,m) Cm[j]=C(j-1,b-1)*C(m,j)%M;
		FOR(i,a,n) {
			ll base2=base1;
			FOR(j,b,m) {
				add_(ans,Cn[i]%M*Cm[j]%M*base2%M*pw2[(n-i)*(m-j)]%M);
				// printf("(%d %d): %lld %lld; C=%d\n",i,j,C(i,a)*base1%M,C(j,b)*base2%M,pw2[(n-i)*(m-j)]);
				base2=M-base2;
			} base1=M-base1;
		}
		// printTimer();
		printf("%d\n",ans);
	}
}
/*
3000 3000 1 1
3000 3000 1 1
3000 3000 1 1
3000 3000 1 1
3000 3000 1 1
*/