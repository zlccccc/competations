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
const LL maxn=1e6+107;
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

int f[5007],g[5007],val[5007],mul[5007];
//x^2+(1-x)^2 = 1-2x+2x^2
LL inv[1000002];//inverse
LL Inv[1000002];//inverse
LL fac[1000002];//Factorial
LL C(int n,int m) {
	return fac[n]*inv[m]%M*inv[n-m]%M;
}
int main() {
	int N,K,L,i,k;
	scanf("%d%d%d",&N,&K,&L);
	fac[0]=1;
	FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,1000000) Inv[i]=inv[i],inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
	f[0]=1;//1,zero
	FOR(i,1,N) {
		FOR(k,0,N*2) g[k]=f[k],f[k]=0;
		FOR(k,0,N*2) {
			add_(f[k+1],(ll)2*g[k]%M);
			add_(f[k+2],M-(ll)2*g[k]%M);
		}//one
	} int ans=0;
	rFOR(i,K,N){
		int now=0;
		// printf("%d :\n",i);
		// FOR(k,0,N*2) printf("%d%c",f[k]," \n"[k==i*2]);
		FOR(k,0,N*2) add_(now,(ll)f[k]*Inv[k+1]%M);
		add_(ans,(ll)C(N,i)*now%M);//least k times(多算)

		FOR(k,0,N*2) add_(f[k+1],f[k]);
		FOR(k,0,N*2) f[k]=(ll)f[k+1]*Inv[2]%M;
		FOR(k,0,N*2) g[k]=f[k],f[k]=0;
		FOR(k,0,N*2) {//one
			add_(f[k  ],g[k]);
			add_(f[k+1],M-(ll)2*g[k]%M);
			add_(f[k+2],(ll)2*g[k]%M);
		}//one
	} mul_(ans,L);
	printf("%d\n",ans);
}
/*
2
1 0 0 0
*/