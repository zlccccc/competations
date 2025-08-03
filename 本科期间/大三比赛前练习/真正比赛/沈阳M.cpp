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
const LL maxn=1e7+107;
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

int A[10007][1007],B[10007][1007];
inline void all(int A[],int x,int rev){
	int i;
	if (rev==1) FOR(i,x,1000) add_(A[i],A[i-x]);
	else FOR(i,x,1000) add_(A[i],M-A[i-x]);
}
inline void one(int A[],int x,int rev){
	int i;
	if (rev==1) rFOR(i,x,1000) add_(A[i],A[i-x]);
	else rFOR(i,x,1000) add_(A[i],M-A[i-x]);
}
int main() {
	int _,T; scanf("%d",&T);
	FOR(_,1,T) {
		int i,k;
		printf("Case #%d:\n",_);
		scanf("%d%d",&n,&m);
		A[0][0]=1; B[0][0]=1;
		FOR(k,1,1000) A[0][k]=B[0][k]=0;
		FOR(i,1,n) {
			int a,b;
			FOR(k,0,1000) A[i][k]=A[i-1][k];
			FOR(k,0,1000) B[i][k]=B[i-1][k];
			scanf("%d%d",&a,&b);
			one(A[i],(a+1)*b,-1); all(A[i],b,1);
			all(B[i],(a+1)*b,1); one(B[i],b,-1);
		} FOR(i,0,n) {
			FOR(k,0,1000) add_(A[i][k],A[i][k-1]);
		} int lastans=0;
		FOR(i,1,m){
			int l,r,k,i;
			scanf("%d%d%d",&l,&r,&k);
			l=(l+lastans)%n+1; r=(r+lastans)%n+1;
			if (l>r) swap(l,r); lastans=0;
			FOR(i,0,k) add_(lastans,(ll)A[r][i]*B[l-1][k-i]%M);
			printf("%d\n",lastans);
		}
	}
}
/*
*/
