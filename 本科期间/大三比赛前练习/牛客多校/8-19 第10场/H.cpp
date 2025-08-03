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
typedef __int128 ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int INF=0x3f3f3f3f;
const LL INFF=0x3f3f3f3f3f3f3f3fll;
const LL M=998244353;
const LL maxn=1e6+7;
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
int n,m,q;
char str[maxn];
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

ll f(ll a,ll b,ll c,ll n) {
	if (a==0) return b/c*(n+1);
	if (a>=c||b>=c) return (a/c)*n*(n+1)/2+(b/c)*(n+1)+f(a%c,b%c,c,n);
	ll m=(a*n+b)/c;
	return n*m-f(c,c-b-1,a,m-1);
}
LL a,b,c,d;
ll get(ll x){
	ll A=f(a,0,b,x-1)-x;//high
	ll B=f(c,0,d,x);//low
	return (B-A)%M+M;
}
int main() {
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
		if (a*d==b*c) puts("-1");
		else{
			if (a*d<b*c) {swap(a,c); swap(b,d);};
			ll l=(a+b)*d/(a*d-b*c);
			// printf("l=%lld ",(LL)l);
			printf("%lld\n",(LL)(get(l)%M));
		}
	}
}
/*
10
1 100 1 99
1 1000000000 1 99999999
1000000000 1 999999999 1
1 1 1 1 1 2 1 1 1 3 2 1 1 100 1 99 12 34 56 78

*/
