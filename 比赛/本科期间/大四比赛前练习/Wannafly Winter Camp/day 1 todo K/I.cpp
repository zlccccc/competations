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

int SUMA[maxn*4],LAZY[maxn*4],SUMV[maxn*4];//V:value=sigma{...}
void change(int x,int val) {
	add_(LAZY[x],val);
	add_(SUMV[x],(ll)val*SUMA[x]%M);
}
void pushup(int x) {
	SUMA[x]=(SUMA[x<<1]+SUMA[x<<1|1])%M;
	SUMV[x]=(SUMV[x<<1]+SUMV[x<<1|1])%M;
	assert(!LAZY[x]);
}
void pushdown(int x) {
	if (LAZY[x]) {
		change(x<<1,LAZY[x]);
		change(x<<1|1,LAZY[x]);
		LAZY[x]=0;
	}
}
void update1(int x,int l,int r,int L,int R) {
	if (l<=L&&R<=r) {change(x,1); return;}
	int mid=(L+R)/2;
	pushdown(x);
	if (l<=mid) update1(x<<1,l,r,L,mid);
	if (mid<r) update1(x<<1|1,l,r,mid+1,R);
	pushup(x);
	// printf("update1 : %d->%d , SUMA=%d; SUMV=%d LAZY=%d\n",L,R,SUMA[x],SUMV[x],LAZY[x]);
}
void updateA(int x,int pos,int val,int L,int R) {
	// printf("query %d: %d %d %d %d\n",x,pos,val,L,R);
	if (L==R) {add_(SUMA[x],val); return;}
	int mid=(L+R)/2;
	pushdown(x);
	if (pos<=mid) updateA(x<<1,pos,val,L,mid);
	if (mid<pos) updateA(x<<1|1,pos,val,mid+1,R);
	pushup(x);
	// printf("updateA : %d->%d , SUMA=%d; SUMV=%d LAZY=%d\n",L,R,SUMA[x],SUMV[x],LAZY[x]);
}
int query(int x,int l,int r,int L,int R) {
	// printf("query: %d %d %d %d %d\n",x,l,r,L,R);
	if (l>r) return 0;
	if (l<=L&&R<=r)	return SUMV[x];
	int mid=(L+R)/2,ret=0;
	pushdown(x);
	if (l<=mid) add_(ret,query(x<<1,l,r,L,mid));
	if (mid<r) add_(ret,query(x<<1|1,l,r,mid+1,R));
	pushup(x);
	// printf("Query : %d->%d , SUMA=%d; SUMV=%d LAZY=%d\n",L,R,SUMA[x],SUMV[x],LAZY[x]);
	return ret;
}
int A[maxn];
int main() {
	int n,ans=0,i;
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",&A[i]);
	rFOR(i,1,n) {
		int now=query(1,1,A[i]-1,1,n);
		// printf("%d : now=%d\n",i,now);
		add_(ans,now); add_(now,1);
		update1(1,A[i]+1,n,1,n);
		updateA(1,A[i],now,1,n);
	}
	printf("%d\n",ans);
}
/*
100
2 3 2
2 4 2
2 5 2
2 6 2
*/