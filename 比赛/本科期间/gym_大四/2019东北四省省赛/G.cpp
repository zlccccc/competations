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

priority_queue<int> Q;
int i;
ll sumr,suml,cntl,cntr;
ll check(pii A[],int n,int pos) {
	// printf("check:%d\n",pos);
	while (i<=n&&A[i].first==pos) {
		sumr-=A[i].first; cntr--;
		Q.push(-A[i].second); i++;
	}
	while (Q.size()&&-Q.top()==pos) {
		int x=-Q.top(); Q.pop();
		suml+=x; cntl++;
	}
	return (sumr-pos*cntr)+(pos*cntl-suml);
}
ll solve(pii A[],int n) {
	sort(A+1,A+1+n);
	sumr=0,cntr=0,suml=0,cntl=0;
	FOR(i,1,n) sumr+=A[i].first,cntr++;
	ll ans=INFF;
	int prev=0;
	for (i=1;i<=n||Q.size();) {
		int pos=INF;
		if (i<=n) pos=min(pos,A[i].first);
		if (Q.size()) pos=min(pos,-Q.top());
		if (prev<pos-1) ans=min(ans,check(A,n,pos-1)),prev=pos-1;
		if (prev<pos) ans=min(ans,check(A,n,pos)),prev=pos;
		if (prev<pos+1) ans=min(ans,check(A,n,pos+1)),prev=pos+1;
		// printf("check: %d; i=%d; cnt=%llu  %lld;%lld  %lld;%lld\n",pos,i,Q.size(),suml,cntl,sumr,cntr);
	}
	return ans;
}
pii A[maxn],B[maxn];
int main() {
	int T,_; T=1;
	scanf("%d",&T);
	FOR(_,1,T){
		int n,i; ll ans=0;
		scanf("%d",&n);
		FOR(i,1,n) scanf("%d%d%d%d",&A[i].first,&B[i].first,&A[i].second,&B[i].second);
		ans+=solve(A,n);
		ans+=solve(B,n);
		printf("%lld\n",ans);
	}
}
/*
1
2
2 2 3 3
4 4 5 5

*/