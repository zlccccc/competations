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

int ans; ll remain;//remain
int MIN[maxn<<2],A[maxn];
void build(int x,int L,int R){
	if (L==R) {
		MIN[x]=A[L]; return;
	} int mid=(L+R)/2;
	build(x<<1,L,mid);
	build(x<<1|1,mid+1,R);
	MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
}
void update(int x,int L,int R){
	if (L==R){
		remain-=MIN[x]; ans++; MIN[x]=INF; return;
	} int mid=(L+R)/2;
	if (MIN[x<<1]<=remain) update(x<<1,L,mid);
	if (MIN[x<<1|1]<=remain) update(x<<1|1,mid+1,R);
	MIN[x]=min(MIN[x<<1],MIN[x<<1|1]);
}
int CNT[maxn],REM[maxn];
int main() {
	int i;
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",&A[i]);
	build(1,1,n);
	FOR(i,1,100000){
		if (ans!=n) remain+=m;
		if (ans!=n) update(1,1,n);
		CNT[i]=ans; REM[i]=remain;
	} scanf("%d",&q);
	while (q--){
		int x;
		scanf("%d",&x);
		printf("%d %d\n",CNT[x],REM[x]);
	}
}
/*
002 1
1 2 3 4 5
100
100000000000000000000 1
0 0 0 1 1
4095
100000000000000000000 1
1 0 0 1 1
4095
*/
