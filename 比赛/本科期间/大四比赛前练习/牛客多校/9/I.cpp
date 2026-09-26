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
inline ll powMM(ll a, ll b, ll mod=M) {
	ll ret=1;
	for (; b; b>>=1ll,a=a*a%mod)
		if (b&1) ret=ret*a%mod;
	return ret;
}
int startTime;
void startTimer() {startTime=clock();}
void printTimer() {debug("/--- Time: %ld milliseconds ---/\n",clock()-startTime);}

const ll inv2=powMM(2,M-2);
//ax+b/c
__int128 f(__int128 a,__int128 b,__int128 c,__int128 n) {
    if (a==0) return b/c%M*(n+1)%M;
    if (a>=c||b>=c) return ((a/c)%M*n%M*(n+1)%M*inv2%M+(b/c)*(n+1)%M+f(a%c,b%c,c,n))%M;
    __int128 m=(a*n+b)/c;
    return (n*m%M-f(c,c-b-1,a,m-1)+M)%M;
}
ll solve(ll n,ll m,int k) {
    __int128 ans=f(m,0,1ll<<k,n);
    ans-=2*f(m,0,1ll<<(k+1),n);
    ans+=10*M;
    ans=(ans%M)*((1ll<<k)%M)%M;
    return ans;
}
ll getans(ll n,ll m) {
	int i=0; ll ans=0;
	REP(i,63) if ((m>>i)&1) ans=(ans+solve(n,m,i))%M;
	return ans;
}
int main(){
	ll n,m;;
	scanf("%lld%lld",&n,&m);
	printf("%lld\n",getans(n,m));
	// ll l,r;
	// scanf("%lld%lld%lld",&l,&r,&m);
	// printf("%lld\n",(getans(r,m)-getans(l-1,m)+M)%M);
}