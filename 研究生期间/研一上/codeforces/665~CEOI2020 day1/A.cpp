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
const LL maxn=2e6+107;
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

//f(lx to ly)*(f(hmax)-f(hlower-1))
const ll inv2=powMM(2,M-2)%M;
inline ll f(ll x) {//for h
	x%=M;
	return x*(x+1)%M*inv2%M;
}
ll h[maxn],w[maxn];
int S[maxn],top;
int main() {
	int n,i;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%lld",&h[i]);
	FOR(i,1,n) scanf("%lld",&w[i]);
	FOR(i,1,n+1) w[i]+=w[i-1];
	ll ans=0;
	FOR(i,1,n+1) {
		ll R=w[S[top]];
		while (top&&h[S[top]]>h[i]) {
			int r=S[top],l=S[top-1]; top--;
			// printf("%d: add f(%lld)-f(%lld) * g(%lld)  ;l=%d; ans=%lld\n",i,h[r],max(h[l],h[i]),R-w[l],l,ans);
			add_(ans,(f(h[r])+M-f(max(h[l],h[i])))*f(R-w[l])%M);
		} S[++top]=i;
	}
	printf("%lld\n",ans);
}
/*
2
2 1
2 1
*/