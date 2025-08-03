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

// 为啥我永远在载入啊QAQ
int ids[maxn];
pair<ll,int> A[maxn],B[maxn];
ll sum[maxn*2];
int n;
void addvalue(int l,int r,int val){
	if (l<1) l+=n,r+=n;
	if (l>r) return;
	// printf("add: %d %d %d\n",l,r,val);
	sum[l]+=val; sum[r+1]-=val;
}
int main() {
	int i,m;
	scanf("%d%d",&m,&n);
	FOR(i,1,n) scanf("%lld",&A[i].first),A[i].second=i;
	FOR(i,1,n) scanf("%lld",&B[i].first),B[i].second=i;
	sort(A+1,A+1+n); sort(B+1,B+1+n);
	// FOR(i,1,n+1) A[i+n].first=A[i].first+m,A[i+n].second=i+n;
	// A-m<B<=A-m/2:	B-A+m
	// A-m/2<B<=A:		A-B
	// A<B<=A+m/2:		B-A
	// A+m/2<=B<=A+m:	A+m-B
	// for B
	int pos1,pos2,pos3;
	pos1=pos2=pos3=1;
	//B[i]<=>A[pos]
	// FOR(i,1,n) {
	// 	int j;
	// 	FOR(j,1,n) {
	// 		if (B[i].first*2<=A[j].first*2-m) addvalue(j-i,j-i,-A[j].first);
	// 		else if (B[i].first<=A[j].first) addvalue(j-i,j-i,A[j].first);
	// 		else if (B[i].first*2<=A[j].first*2+m) addvalue(j-i,j-i,-A[j].first);
	// 		else if (B[i].first<=A[j].first+m) addvalue(j-i,j-i,A[j].first);
	// 		if (B[i].first*2<=A[j].first*2-m) addvalue(j-i,j-i,B[i].first+m);
	// 		else if (B[i].first<=A[j].first) addvalue(j-i,j-i,-B[i].first);
	// 		else if (B[i].first*2<=A[j].first*2+m) addvalue(j-i,j-i,B[i].first);
	// 		else if (B[i].first<=A[j].first+m) addvalue(j-i,j-i,-B[i].first+m);
	// 	}
	// }
	FOR(i,1,n) {
		int pos0=1,pos4=n+1;
		while (pos1<=n&&B[i].first*2>A[pos1].first*2+m) pos1++;
		while (pos2<=n&&B[i].first*2>A[pos2].first*2) pos2++;
		while (pos3<=n&&B[i].first*2>A[pos3].first*2-m) pos3++;
		//B[i]对应A[i+k=pos]时, B会产生val的贡献; k=pos-i
		// printf("solve: %d  (%d %d %d %d %d)\n",B[i].first,pos0,pos1,pos2,pos3,pos4);
		addvalue(pos0-i,pos1-i-1,-B[i].first+m);
		addvalue(pos1-i,pos2-i-1,B[i].first);
		addvalue(pos2-i,pos3-i-1,-B[i].first);
		addvalue(pos3-i,pos4-i-1,B[i].first+m);
	} // for A
	pos1=pos2=pos3=1;
	FOR(i,1,n) {
		int pos0=1,pos4=n+1;
		while (pos1<=n&&B[pos1].first*2<=A[i].first*2-m) pos1++;
		while (pos2<=n&&B[pos2].first*2<=A[i].first*2) pos2++;
		while (pos3<=n&&B[pos3].first*2<=A[i].first*2+m) pos3++;
		//B[i-k=pos]对应A[i]时, A会产生val的贡献; k=i-pos
		// printf("solve A: %d  (%d %d %d %d %d)\n",A[i].first,pos0,pos1,pos2,pos3,pos4);
		addvalue(i-pos4+1,i-pos3,A[i].first);
		addvalue(i-pos3+1,i-pos2,-A[i].first);
		addvalue(i-pos2+1,i-pos1,A[i].first);
		addvalue(i-pos1+1,i-pos0,-A[i].first);
	}
	FOR(i,1,n+n) sum[i]+=sum[i-1];
	FOR(i,1,n) sum[i]+=sum[i+n];
	pair<ll,int> ans=make_pair(INFF,0);
	// FOR(i,1,n) printf("(%lld,%d)",sum[i],i);
	FOR(i,1,n) ans=min(ans,make_pair(sum[i],i));
	FOR(i,1,n) ids[A[(i+ans.second-1)%n+1].second]=B[i].second;
	printf("%lld\n",ans.first);
	FOR(i,1,n) printf("%d ",ids[i]);
}
/*
add: 3 3 4
add: 1 1 -4
add: 2 2 -4
add: 2 2 6
add: 3 3 6
add: 1 1 6
add: 1 1 0
add: 2 2 10
add: 3 3 10
*/