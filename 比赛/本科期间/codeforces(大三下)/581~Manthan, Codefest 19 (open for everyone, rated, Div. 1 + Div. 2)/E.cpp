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

ll T[maxn*4];
void update(int x,int l,int r,int val,int L,int R) {
	if (l<=L&&R<=r) {
		T[x]+=val;
		return;
	} int mid=(L+R)/2;
	if (l<=mid) update(x<<1,l,r,val,L,mid);
	if (mid<r) update(x<<1|1,l,r,val,mid+1,R);
}
void query(int x,ll val,int L,int R) {
	val+=T[x];
	if (L==R) {
		printf("%lld ",val);
		return;
	} int mid=(L+R)/2;
	query(x<<1,val,L,mid);
	query(x<<1|1,val,mid+1,R);
}
int MAX[maxn*4],A[maxn];
void build(int x,int L,int R) {
	if (L==R) {
		// printf("build: x=%d: %d\n",x,A[L]);
		MAX[x]=A[L];
		return;
	} int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
	MAX[x]=max(MAX[x<<1],MAX[x<<1|1]);
}
int query(int x,int l,int r,int L,int R){
	if (l<=L&&R<=r) {
		// printf("query:x=%d %d %d:%d\n",x,l,r,MAX[x]);
		return MAX[x];
	} int mid=(L+R)/2,ans=-INF;
	if (l<=mid) max_(ans,query(x<<1,l,r,L,mid));
	if (mid<r) max_(ans,query(x<<1|1,l,r,mid+1,R));
	return ans;
}
int main() {
	int n,w,i,_;
	scanf("%d%d",&n,&w);
	FOR(_,1,n) {
		int k;
		scanf("%d",&k);
		FOR(i,1,k) scanf("%d",&A[i]);
		build(1,1,k);
		FOR(i,1,w) {
			int l=i,r=i;
			int val=query(1,max(1,i-(w-k)),min(i,k),1,k);
			if (i-(w-k)<1||k<i) val=max(val,0);//could
			if (i-(w-k)<=1&&k<=i) r=max(r,w-k);
			// printf("update: %d-%d(query=(%d %d)): %d\n",l,r,max(1,i-(w-k)),min(i,k),val);
			update(1,l,r,val,1,w); i=r;
		}
	} query(1,0,1,w);
}
/*
3 3
3 -1 -1 -1
2 -1 -1
2 -1 -1
*/