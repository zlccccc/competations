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
const LL maxn=1e6+107;
const double pi=acos(-1.0);
const double eps=1e-10;
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

ll inv2[maxn];
LL inv[maxn];//inverse
LL fac[maxn];//Factorial
inline int C(int n,int m) {
	return fac[n]*inv[m]%M*inv[n-m]%M;
}
ll A[maxn];
int main() {
	int n; ll T;
	int i;
	scanf("%d%lld",&n,&T);
	fac[0]=1;
	FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
	inv2[0]=1; inv2[1]=inv[2];
	FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
	FOR(i,2,1000000) inv2[i]=inv2[i-1]*inv2[1]%M;
	FOR(i,1,n) scanf("%lld",&A[i]);
	ll ans=0;
	ll PreT=0,nowProb=1;//C(1,0)=1;
	FOR(i,1,n) {
		A[i]+=A[i-1];
		if (A[i]<=T) {
			if (T-A[i]>i) add_(ans,1);
			else {
				ll nowt=T-A[i]; //i-t -> i
				//这个超过:C(i,0)+...+C(i,T-A[i])
				while (PreT<nowt) {PreT++; add_(nowProb,C(i,PreT));}
				while (PreT>nowt) {add_(nowProb,M-C(i,PreT)); PreT--;}
				// printf("C(%d,%d) : %lld\n",i,PreT,nowProb);
				add_(ans,nowProb*inv2[i]%M);
			}
		}
		//C(2,0)
		nowProb=(nowProb*2+M-C(i,PreT))%M;
		// printf("C(%d,%d) : %lld\n",i,PreT,nowProb);
	}
	printf("%lld\n",ans);
}
/*
*/