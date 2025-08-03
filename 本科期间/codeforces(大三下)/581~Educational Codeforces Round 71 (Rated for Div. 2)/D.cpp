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

LL inv[1000002];//inverse
LL fac[1000002];//Factorial
pair<int,int> P[maxn];
int main() {
	int n,i;
	fac[0]=1;
	FOR(i,1,1000000) fac[i]=i*fac[i-1]%M;
	inv[0]=inv[1]=1;
	FOR(i,2,1000000) inv[i]=(M-M/i)*inv[M%i]%M;
	FOR(i,1,1000000) inv[i]=inv[i]*inv[i-1]%M;// inv(n!)
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d%d",&P[i].first,&P[i].second);
	sort(P+1,P+1+n);
	int ans=fac[n];
	// printf("ans=%d\n",ans);
	int now=0,nowans=1;
	FOR(i,1,n) {
		now++;
		if (P[i].first!=P[i+1].first||i==n) {
			mul_(nowans,fac[now]); now=0;
		}
	} add_(ans,M-nowans);
	// printf("nowans=%d\n",nowans);
	FOR(i,1,n) swap(P[i].first,P[i].second);
	sort(P+1,P+1+n);
	now=0; nowans=1;
	FOR(i,1,n) {
		now++;
		if (P[i].first!=P[i+1].first||i==n) {
			mul_(nowans,fac[now]); now=0;
		}
	} add_(ans,M-nowans);
	// printf("nowans=%d\n",nowans);
	now=0; nowans=1;
	FOR(i,1,n) {
		now++;
		if ((P[i].second!=P[i+1].second||P[i].first!=P[i+1].first)||i==n) {
			mul_(nowans,fac[now]); now=0;
		}
		if (i!=n&&P[i].second>P[i+1].second) nowans=0;
	} add_(ans,nowans);
	// printf("nowans=%d\n",nowans);
	printf("%d\n",ans);
}
/*
*/