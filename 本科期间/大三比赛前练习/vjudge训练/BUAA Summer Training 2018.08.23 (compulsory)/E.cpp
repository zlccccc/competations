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
const LL maxn=1e5+7;
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

inline int ask(int x,int y=0,int dep=n) {
	if (dep==1) return y;
	int mid=dep/2;
	// printf("  %d %d   %d %d\n",x,y,dep,n/dep);
	if (x>=mid) x=dep-x-1,y=n/dep*2-y-1;
	return ask(x,y,dep/2);
}
const int T=16;
int inv[1<<T|7],K;
inline int Inv(int x){
	if (K<=T) return inv[x]>>(T-K);
	return (inv[x&((1<<T)-1)]<<(K-T))|(inv[x>>T]>>(T+T-K));
}
inline int ask2(int x){
	if (!(x&1)) return Inv(x/2);
	else return Inv(n-x/2-1);
}
int main() {
	int i;
	for (int i=1,j=1<<(T-1); i<(1<<T)-1; i++) {
		inv[i]=j; inv[j]=i; int k=1<<(T-1);
		while (j>=k) j-=k,k/=2;
		if (j<k) j+=k;
	} inv[(1<<T)-1]=(1<<T)-1;
	// K=7; n=(1<<K); REP(i,n) printf("%d ",ask(i));puts("");
	// REP(i,n) printf("%d ",ask2(i));puts("");
	int l,r,h=0;
	scanf("%d",&K); n=1<<K;
	scanf("%d%d%d",&m,&l,&r);
	int a,b,c;
	scanf("%d%d%d",&a,&b,&c);
	FOR(i,0,m-1) {
		ll ans=0;
		if (l&1) {
			ans=ask2(l);
			ans+=(ll)((r-l)/2)*(n-1);
			if (!(r&1)) ans+=ask2(r);
		} else {
			if (((r-l+1)/2)&1) ans^=n-1;
			if (!(r&1)) ans^=ask2(r);
		}
		// printf("%d - %d : %lld  %d\n",l,r,ans,(r-l+1)/2);
		h=((l^r^h^ans)+c)%M;
		l=(l^a^h)%(n+1)%n;
		r=(r^b^h)%(n-l)+l;
	}
	printf("%d\n",h);
}
/*
3
1 2 5
*/
