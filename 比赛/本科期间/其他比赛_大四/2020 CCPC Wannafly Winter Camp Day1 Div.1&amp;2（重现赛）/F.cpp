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
const LL maxn=2e5+107;
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

int n,m; ll k;
ll A[maxn],B[maxn];
ll getans(ll now) {
	int i; ll ans=0;
	FOR(i,1,m) {//bigger than now_count
		// printf("i=%d\n",i);
		if (B[i]==0) {// A*B>=n
			if (now<=0) ans+=n;
		} else if (B[i]<0) {//A<=n/B
			ans+=upper_bound(A+1,A+1+n,(now+B[i]*INF)/B[i]-INF)-1-A;//same op
			// printf("%lld",(now-1-B[i]*INF)/B[i]+INF);
		} else {//A>=n/B
			ans+=A+n+1-upper_bound(A+1,A+1+n,(now-1+B[i]*INF)/B[i]-INF);//same op
		}
	} 
	// printf("now=%lld; %lld\n",now,ans);
	return ans;
}
int main() {
	int i;
	// printf("%d\n",3/-2);
	scanf("%d%d%lld",&n,&m,&k);
	FOR(i,1,n) scanf("%lld",&A[i]);
	FOR(i,1,m) scanf("%lld",&B[i]);
	sort(A+1,A+1+n);
	sort(B+1,B+1+m);
	ll MIN=-1e15,MAX=1e15;
	while (MIN+1<MAX) {
		ll MID=(MAX-MIN)/2+MIN;
		// printf("MAX=%lld MIN=%lld; MID=%lld\n",MAX,MIN,MID);
		if (getans(MID)<k) MAX=MID;
		else MIN=MID;
	} printf("%lld\n",MIN);
}
/*
3 3 3
-2 -3 -4
-4 -5 -6

3 3 3
0 0 0
0 0 0
*/