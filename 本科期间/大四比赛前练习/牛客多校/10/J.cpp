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

pair<int,int> P[maxn];
ll sumwh[maxn],sumw[maxn];
ll pre[maxn],dp[maxn];
struct node{
	int l,r,xl,xr;
};
queue<node> Q;
void solve(int n) {
	int i;
	Q.push(node{1,n,0,n-1});
	while (Q.size()) {
		auto F=Q.front(); Q.pop();
		int l=F.l,r=F.r,L=F.xl,R=F.xr;
		int m=(l+r)/2,M=L;
		ll &now=dp[m];
		FOR(i,L,min(m-1,R)) {
			if (now<pre[i]+(ll)P[i+1].first*(sumw[m]-sumw[i])) {
				now=pre[i]+(ll)P[i+1].first*(sumw[m]-sumw[i]),M=i;
			}
		}
		if (l<m) Q.push(node{l,m-1,L,M});
		if (r>m) Q.push(node{m+1,r,M,R});
	}
}
int main(){
	int n,i,k;
	scanf("%d%d",&n,&k);
	FOR(i,1,n) {
		scanf("%d%d",&P[i].second,&P[i].first);
	} sort(P+1,P+1+n);
	FOR(i,1,n) {
		sumwh[i]=sumwh[i-1]+(ll)P[i].first*P[i].second;
		sumw[i]=sumw[i-1]+P[i].second;
	}
	FOR(i,1,n) dp[i]=-INFF;
	while (k--) {
		FOR(i,0,n) pre[i]=dp[i];
		solve(n);
	}
	printf("%lld\n",sumwh[n]-dp[n]);
}
/*
6 1
1 1
1 2
1 3
1 4
1 5
1 6
*/