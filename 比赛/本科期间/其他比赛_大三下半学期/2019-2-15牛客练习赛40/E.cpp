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
const double eps=0.0000000001;
LL gcd(LL a, LL b) {return b?gcd(b,a%b):a;}
template<typename T>inline void pr2(T x,int k=64) {ll i; REP(i,k) debug("%d",(x>>i)&1); putchar(' ');}
template<typename T>inline void add_(T &A,int B,ll MOD=M) {A+=B; (A>=MOD) &&(A-=MOD);}
template<typename T>inline void mul_(T &A,ll B,ll MOD=M) {A=(A*B)%MOD;}
template<typename T>inline void mod_(T &A,ll MOD=M) {A%=MOD; A+=MOD; A%=MOD;}
template<typename T>inline void max_(T &A,T B) {(A<B) &&(A=B);}
template<typename T>inline void min_(T &A,T B) {(A>B) &&(A=B);}
template<typename T>inline T abs(T a) {return a>0?a:-a;}
template<typename T>inline T powMM(T a, T b) {
	T ret=1;
	for (; b; b>>=1ll,a=(LL)a*a%M)
		if (b&1) ret=(LL)ret*a%M;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}
int n,m,q;
// char str[maxn];

ll okay[maxn],inv[maxn];
int main() {
	int i; okay[1]=1;
	FOR(i,2,250000) {
		if (!okay[i])
			for (ll j=i; j<=250000; j*=i)
				for (ll k=j; k<=250000; k+=j)
					okay[k]++;
	} FOR(i,1,250000) {
		inv[i]=powMM((ll)okay[i],M-2);
		for (ll j=i+i;j<=250000;j+=i)
			okay[j]=okay[j]*inv[i]%M;
	} inv[0]=okay[0]=1;
	FOR(i,1,250000) okay[i]=okay[i]*okay[i-1]%M;
	FOR(i,1,250000) inv[i]=inv[i]*inv[i-1]%M;
	int T,_; scanf("%d",&T);
	FOR(_,1,T) {
		ll ans=1; map<int,ll> MP;
		scanf("%d%d",&n,&m);
		FOR(i,1,min(n,m)){
			int nxti=min(n/(n/i),m/(m/i));
			ans=ans*powMM(okay[nxti]*inv[i-1]%M,(ll)(n/i)*(m/i))%M;
			i=nxti;
		} printf("%lld\n",ans);
	}
}
/*
10
4 5
*/